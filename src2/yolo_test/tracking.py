import cv2 as cv
import argparse
import time
from ultralytics import YOLO

# Argument parser for input video file
parser = argparse.ArgumentParser(description='This sample demonstrates YOLOv8 object detection with real-time speed calculation for cars using object tracking.')
parser.add_argument('video', type=str, help='path to video file')
args = parser.parse_args()

# Load YOLOv8 model
model = YOLO('/home/addinedu/dev_ws/src/YOLO/yolov8n.pt')

# Create a KCF tracker
tracker = cv.TrackerKCF_create()

# Open video file
cap = cv.VideoCapture(args.video)

# Initialize variables for speed calculation
prev_time = time.time()
prev_frame_time = time.time()
prev_distance = None

while True:
    ret, frame = cap.read()
    if not ret:
        print('No frames grabbed!')
        break

    # Object detection using YOLOv8
    results = model(frame)
    detections = results[0].boxes.data.cpu().numpy()
    
    # Filter out only 'car' label (label 2 in COCO dataset)
    cars = [detection for detection in detections if int(detection[5]) == 2]

    if cars:
        # Take first detected car
        car = cars[0]
        x1, y1, x2, y2 = map(int, car[:4])
        bbox = (x1, y1, x2 - x1, y2 - y1)
        
        # Initialize the tracker with the bounding box
        ok = tracker.init(frame, bbox)
        if ok:
            # Start tracking
            ok, bbox = tracker.update(frame)
            if ok:
                # Calculate speed
                if prev_distance is not None:
                    distance = ((bbox[0] - prev_bbox[0]) ** 2 + (bbox[1] - prev_bbox[1]) ** 2) ** 0.5
                    current_frame_time = time.time()
                    time_elapsed = current_frame_time - prev_frame_time
                    speed_pixels_per_sec = distance / time_elapsed
                    speed_kmh = speed_pixels_per_sec * 0.036 * 1000 / 3600  # Convert to km/h
                    print(f'Real-time speed of car: {speed_kmh:.2f} km/h')
                    prev_frame_time = current_frame_time
                
                prev_distance = distance
                prev_bbox = bbox

    else:
        print('No car detected!')

cap.release()
