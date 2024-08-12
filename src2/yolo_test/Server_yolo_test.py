from flask import Flask, request, jsonify
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

    # Process the video
    process_video(filepath)

    return jsonify({'message': 'File uploaded and processed successfully'}), 200

def process_video(video_path):
    cap = cv2.VideoCapture(video_path)

    cap.set(cv2.CAP_PROP_FRAME_WIDTH, 1280)
    cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 720)

    while cap.isOpened():
        success, frame = cap.read()
        if not success:
            break

        results = model.track(frame, persist=True)
        annotated_frame = results[0].plot()

        # Here, you could save the annotated frame to a file or database, or stream it back to the client
        # For demonstration, we'll just display it
        cv2.imshow("YOLOv8 Tracking", annotated_frame)

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    cap.release()
    cv2.destroyAllWindows()

if __name__ == '__main__':
    app.run(host='0.0.0.0',port=5000 , debug=True)

