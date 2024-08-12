from collections import defaultdict
import cv2
import numpy as np
from ultralytics import YOLO

# YOLO 모델을 불러옵니다.
model = YOLO('yolov8n.pt')

# 비디오 파일 경로를 지정합니다.
video_path = "/home/addinedu/drive.webm"

# 비디오 파일을 읽어옵니다.
cap = cv2.VideoCapture(video_path)
f = open('./segment_log.txt', 'w+')
track_history = defaultdict(lambda: [])

while cap.isOpened():
    # 비디오 프레임을 읽어옵니다.
    success, frame = cap.read()
    if success:
        # YOLO 모델을 사용하여 프레임에서 객체를 추적합니다.
        results = model.track(frame, persist=True)
        
        # 객체가 있는 경우에만 실행합니다.
        if results and results[0].boxes:
            boxes = results[0].boxes.xywh.cpu()
            track_ids = [box.id for box in results[0].boxes]  # 객체의 ID 목록을 가져옵니다.
            track_ids = [int(id) if id is not None else None for id in track_ids]  # None일 경우 None으로 변환합니다.
            f.write('boxes : ' + str(boxes))
            f.write('track_ids :' + str(track_ids))

            annotated_frame = results[0].plot()

            for box, track_id in zip(boxes, track_ids):
                x, y, w, h = box
                track = track_history[track_id]
                track.append((float(x), float(y)))
                if len(track) > 30:
                    track.pop(0)
                
                points = np.hstack(track).astype(np.int32).reshape((-1, 1, 2))
                cv2.polylines(annotated_frame, [points], isClosed=False, color=(230,230,230), thickness=10)
                
                # Calculate speed
                if len(track) > 1:
                    prev_x, prev_y = track[-2]
                    current_x, current_y = track[-1]
                    distance_pixels = np.sqrt((current_x - prev_x) ** 2 + (current_y - prev_y) ** 2)
                    
                    # Convert distance to kilometers (assuming 1 pixel = 0.01 meters)
                    distance_km = distance_pixels * 0.01 / 1000
                    
                    # Calculate time interval (assuming 30 frames per second)
                    time_interval = 1 / 30
                    
                    # Calculate speed in kilometers per hour
                    speed_kmh = distance_km / time_interval * 3600
                    print(f'Track ID {track_id}: {speed_kmh:.2f} km/h')

            cv2.imshow("YOLOv8 Tracking", annotated_frame)

            if cv2.waitKey(1) & 0xff == ord("q"):
                break
    else:
        break

f.close()
cap.release()
cv2.destroyAllWindows()
