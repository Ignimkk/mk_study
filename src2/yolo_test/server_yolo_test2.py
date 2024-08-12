from flask import Flask, request, jsonify, Response
from werkzeug.utils import secure_filename
import os
import cv2
from ultralytics import YOLO

app = Flask(__name__)
UPLOAD_FOLDER = 'uploads'
os.makedirs(UPLOAD_FOLDER, exist_ok=True)

# Load the YOLOv8 model
# model = YOLO('/home/addinedu/dev_ws/src/YOLO/runs/detect/train24/weights/best.pt')
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

@app.route('/api/stream/<path:video_path>')
def stream_video(video_path):
    video_path = os.path.join(UPLOAD_FOLDER, video_path)
    return Response(process_video(video_path), mimetype='multipart/x-mixed-replace; boundary=frame')

def process_video(video_path):
    cap = cv2.VideoCapture(video_path)

    while cap.isOpened():
        success, frame = cap.read()
        if not success:
            break

        results = model.track(frame, persist=True)
        annotated_frame = results[0].plot()

        # Show the frame with tracking on the server's screen
        cv2.imshow("YOLOv8 Tracking", annotated_frame)

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

        # Encode the frame in JPEG format
        ret, buffer = cv2.imencode('.jpg', annotated_frame)
        frame = buffer.tobytes()

        yield (b'--frame\r\n'
               b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n')

    cap.release()
    cv2.destroyAllWindows()

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)
