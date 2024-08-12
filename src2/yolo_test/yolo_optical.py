import numpy as np
import cv2 as cv
import argparse
import time
from ultralytics import YOLO


# Argument parser for input video file
parser = argparse.ArgumentParser(description='This sample demonstrates YOLOv8 object detection with Lucas-Kanade Optical Flow calculation.')
parser.add_argument('video', type=str, help='path to video file')
args = parser.parse_args()

# Load YOLOv8 model
model = YOLO('/home/addinedu/dev_ws/src/YOLO/yolov8n.pt')

# Open video file
cap = cv.VideoCapture(args.video)

# Parameters for lucas kanade optical flow
lk_params = dict(winSize=(15, 15),
                 maxLevel=2,
                 criteria=(cv.TERM_CRITERIA_EPS | cv.TERM_CRITERIA_COUNT, 10, 0.03))

# Create some random colors
color = np.random.randint(0, 255, (100, 3))

# Initialize variables for speed calculation
prev_time = time.time()
distances = []

# Create a mask image for drawing purposes
mask = None

# Track points from previous frame
p0 = None
old_gray = None

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
        car_frame = frame[y1:y2, x1:x2]
        
        if old_gray is None:
            old_gray = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)
            mask = np.zeros_like(frame)
        
        # Initialize points for optical flow
        p0 = cv.goodFeaturesToTrack(old_gray, mask=None, **{'maxCorners': 100, 'qualityLevel': 0.3, 'minDistance': 7, 'blockSize': 7})

        if p0 is not None:
            frame_gray = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)

            # Calculate optical flow
            p1, st, err = cv.calcOpticalFlowPyrLK(old_gray, frame_gray, p0, None, **lk_params)

            # Select good points
            if p1 is not None:
                good_new = p1[st == 1]
                good_old = p0[st == 1]

                # Calculate distance and speed
                current_time = time.time()
                time_elapsed = current_time - prev_time
                prev_time = current_time

                for i, (new, old) in enumerate(zip(good_new, good_old)):
                    a, b = new.ravel()
                    c, d = old.ravel()
                    distance = np.sqrt((a - c) ** 2 + (b - d) ** 2)
                    speed_pixels_per_sec = distance / time_elapsed
                    speed_kmh = speed_pixels_per_sec * 0.036 * 1000 / 3600  # Convert to km/h
                    distances.append(speed_kmh)

                    mask = cv.line(mask, (int(a), int(b)), (int(c), int(d)), color[i].tolist(), 2)
                    frame = cv.circle(frame, (int(a), int(b)), 5, color[i].tolist(), -1)

                img = cv.add(frame, mask)

                cv.imshow('frame', img)
                k = cv.waitKey(30) & 0xff
                if k == 27:
                    break

                # Now update the previous frame and previous points
                old_gray = frame_gray.copy()
                p0 = good_new.reshape(-1, 1, 2)
    else:
        print('No car detected!')

cap.release()
cv.destroyAllWindows()

# Print the average speed
if distances:
    avg_speed_kmh = sum(distances) / len(distances)
    print(f'Average speed of car: {avg_speed_kmh:.2f} km/h')
else:
    print('No movement detected.')
