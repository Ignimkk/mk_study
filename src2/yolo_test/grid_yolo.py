import cv2
import numpy as np
from ultralytics import YOLO
import torch

# 도로 분할을 위한 모델 로드 (예: DeepLabV3)
road_segmentation_model = torch.hub.load('pytorch/vision:v0.10.0', 'deeplabv3_resnet50', pretrained=True)
road_segmentation_model.eval()

# 카메라 설정
cap = cv2.VideoCapture('drive.webm')

# 격자 크기 설정
grid_size = 20

# 차량 속도 계산을 위한 변수 초기화
prev_frame_time = 0  # 추가된 부분
new_frame_time = 0
prev_gray = None
prev_road_mask = None

# 도로 분할 함수
def segment_road(frame):
    input_image = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    input_tensor = torch.from_numpy(input_image).permute(2, 0, 1).unsqueeze(0).float() / 255.0
    with torch.no_grad():
        output = road_segmentation_model(input_tensor)['out'][0]
    road_mask = output.argmax(0).byte().cpu().numpy()
    return road_mask

# 격자 생성 함수
def create_grid_on_road(frame, road_mask, grid_size):
    road_frame = frame.copy()
    height, width = frame.shape[:2]
    for i in range(0, width, grid_size):
        for j in range(0, height, grid_size):
            if road_mask[j, i]:
                cv2.rectangle(road_frame, (i, j), (i + grid_size, j + grid_size), (255, 255, 255), 1)
    return road_frame

# 차량 속도 계산 함수
def calculate_vehicle_speed(prev_gray, gray, prev_road_mask, road_mask, time_elapsed):
    if prev_gray is None or prev_road_mask is None:
        return 0.0

    # Optical flow를 사용하여 격자의 이동 계산
    flow = cv2.calcOpticalFlowFarneback(prev_gray, gray, None, 0.5, 3, 15, 3, 5, 1.2, 0)
    
    # 도로 영역에서만 이동량을 계산
    road_flow = flow * np.expand_dims(road_mask, axis=2)
    magnitudes = np.sqrt(road_flow[..., 0]**2 + road_flow[..., 1]**2)
    average_movement = np.mean(magnitudes)

    # 속도 계산 (픽셀 이동량을 실제 속도로 변환 필요)
    speed = average_movement / time_elapsed
    return speed

while True:
    ret, frame = cap.read()
    if not ret:
        break

    # 현재 프레임을 그레이스케일로 변환
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # 도로 분할
    road_mask = segment_road(frame)

    # 격자 생성
    grid_frame = create_grid_on_road(frame, road_mask, grid_size)

    # 현재 프레임 시간 계산
    new_frame_time = cv2.getTickCount()
    time_elapsed = (new_frame_time - prev_frame_time) / cv2.getTickFrequency() if prev_frame_time != 0 else 1
    prev_frame_time = new_frame_time

    # 차량 속도 계산
    speed = calculate_vehicle_speed(prev_gray, gray, prev_road_mask, road_mask, time_elapsed)

    # 속도 표시
    cv2.putText(grid_frame, f"Speed: {speed:.2f} px/s", (50, 50), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)

    # 결과 영상 표시
    cv2.imshow("Frame", grid_frame)

    # 이전 프레임 및 마스크 업데이트
    prev_gray = gray
    prev_road_mask = road_mask

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
