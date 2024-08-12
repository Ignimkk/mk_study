from flask import Flask, request, jsonify, send_file
from werkzeug.utils import secure_filename
import os
import cv2
from ultralytics import YOLO
from flask_socketio import SocketIO, emit
from io import BytesIO

app = Flask(__name__)
app.config['UPLOAD_FOLDER'] = 'uploads'
socketio = SocketIO(app)

UPLOAD_FOLDER = 'uploads'
os.makedirs(UPLOAD_FOLDER, exist_ok=True)

# Load the YOLOv8 model
model = YOLO('/home/addinedu/dev_ws/src/YOLO/yolov8n.pt')

@app.route('/api/upload', methods=['POST'])
def upload_video():
    if 'video' not in request.files:
        return jsonify({'error': 'No video file provided'}), 400 

    file = request.files['video']
    if file.filename == '':
        return jsonify({'error': 'No selected file'}), 400

    filename = secure_filename(file.filename)
    filepath = os.path.join(UPLOAD_FOLDER, filename)
    file.save(filepath)

    return jsonify({'message': 'File uploaded successfully', 'filepath': filename}), 200

@socketio.on('connect')
def handle_connect():
    print('Client connected')

@socketio.on('disconnect')
def handle_disconnect():
    print('Client disconnected')

@socketio.on('request_stream')
def handle_stream(video_path):
    video_path = os.path.join(UPLOAD_FOLDER, video_path)
    cap = cv2.VideoCapture(video_path)

    while cap.isOpened():
        success, frame = cap.read()
        if not success:
            break

        results = model.track(frame, persist=True)
        annotated_frame = results[0].plot()
        cv2.imshow("YOLOv8 Tracking", annotated_frame)

        
        # Encode the frame in JPEG format
        _, buffer = cv2.imencode('.jpg', annotated_frame)
        frame_bytes = buffer.tobytes()

        # Send frame to client
        emit('stream_frame', {'frame': frame_bytes})
        
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    cap.release()

if __name__ == '__main__':
    socketio.run(app, host='0.0.0.0', port=5000, debug=True)
