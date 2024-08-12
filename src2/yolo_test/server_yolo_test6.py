from flask import Flask, request, jsonify, Response, send_file
from werkzeug.utils import secure_filename
import os
import cv2
from ultralytics import YOLO

app = Flask(__name__)
UPLOAD_FOLDER = 'uploads'
os.makedirs(UPLOAD_FOLDER, exist_ok=True)

# Load the YOLOv8 model
model = YOLO('/home/addinedu/dev_ws/src/YOLO/yolov8n.pt')

@app.route('/api/upload', methods=['POST'])
def upload_video():
    if 'videos' not in request.files:
        return jsonify({'error': 'No video files provided'}), 400

    videos = request.files.getlist('videos')
    if not videos:
        return jsonify({'error': 'No selected files'}), 400

    # List to store processed video paths
    processed_videos = []

    for video in videos:
        if video.filename == '':
            continue

        filename = secure_filename(video.filename)
        filepath = os.path.join(UPLOAD_FOLDER, filename)
        video.save(filepath)

        # Process the video and save the annotated video
        processed_video_path = process_video(filepath)
        processed_videos.append(processed_video_path)

    return jsonify({'message': 'Files uploaded and processed successfully', 'processed_videos': processed_videos}), 201

def process_video(video_path):
    cap = cv2.VideoCapture(video_path)

    cap.set(cv2.CAP_PROP_FRAME_WIDTH, 1280)
    cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 720)

    # Get the frame dimensions
    frame_width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
    frame_height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))

    # Define the codec and create VideoWriter object
    out = cv2.VideoWriter('annotated_' + os.path.basename(video_path), cv2.VideoWriter_fourcc(*'mp4v'), 30, (frame_width, frame_height))

    while cap.isOpened():
        success, frame = cap.read()
        if not success:
            break

        # Perform object detection and annotation
        results = model.track(frame, persist=True)
        annotated_frame = results[0].plot()

        # Write the annotated frame to the output video
        out.write(annotated_frame)

    # Release everything when job is finished
    cap.release()
    out.release()
    cv2.destroyAllWindows()

    return 'annotated_' + os.path.basename(video_path)

@app.route('/api/download/<video_name>', methods=['GET'])
def download_video(video_name):
    video_path = os.path.join(UPLOAD_FOLDER, video_name)
    return send_file(video_path, as_attachment=True), 201

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)
