import cv2
import numpy as np

# YOLOv8 모델을 초기화하고 가중치 및 구성 파일을 로드합니다.
net = cv2.dnn.readNet("yolov8.weights", "yolov8.cfg")
layer_names = net.getLayerNames()
output_layers = [layer_names[i[0] - 1] for i in net.getUnconnectedOutLayers()]

# 차량의 이전 프레임 위치를 추적하기 위한 변수 초기화
prev_position = None

# 비디오 스트림 또는 웹캠을 초기화합니다.
cap = cv2.VideoCapture("video.mp4")  # 비디오 파일 이름 또는 웹캠 디바이스 번호로 변경 가능

# 옵티컬 플로우 파라미터 설정
lk_params = dict(winSize=(15, 15),
                 maxLevel=2,
                 criteria=(cv2.TERM_CRITERIA_EPS | cv2.TERM_CRITERIA_COUNT, 10, 0.03))

# 처음 프레임 읽기
ret, old_frame = cap.read()
old_gray = cv2.cvtColor(old_frame, cv2.COLOR_BGR2GRAY)
p0 = cv2.goodFeaturesToTrack(old_gray, mask=None, maxCorners=100, qualityLevel=0.3, minDistance=7, blockSize=7)

mask = np.zeros_like(old_frame)

while True:
    ret, frame = cap.read()
    if not ret:
        break

    # 프레임 크기를 변경합니다. (옵션)
    # frame = cv2.resize(frame, None, fx=0.5, fy=0.5)

    height, width, _ = frame.shape

    # YOLOv8를 사용하여 객체를 감지합니다.
    blob = cv2.dnn.blobFromImage(frame, 0.00392, (416, 416), (0, 0, 0), True, crop=False)
    net.setInput(blob)
    outs = net.forward(output_layers)

    # 차선을 세그멘테이션하는 로직을 추가할 수 있습니다.

    # 현재 프레임에 대해 옵티컬 플로우를 계산합니다.
    frame_gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    p1, st, err = cv2.calcOpticalFlowPyrLK(old_gray, frame_gray, p0, None, **lk_params)

    # 이전 프레임에서 현재 프레임으로 유효한 포인트만 선택합니다.
    good_new = p1[st == 1]
    good_old = p0[st == 1]

    # 이동 벡터를 그립니다.
    for i, (new, old) in enumerate(zip(good_new, good_old)):
        a, b = new.ravel()
        c, d = old.ravel()
        mask = cv2.line(mask, (a, b), (c, d), (0, 255, 0), 2)
        frame = cv2.circle(frame, (a, b), 5, (0, 0, 255), -1)

    img = cv2.add(frame, mask)

    # 다음 프레임을 위해 이전 프레임 및 포인트 업데이트
    old_gray = frame_gray.copy()
    p0 = good_new.reshape(-1, 1, 2)

    # 결과를 화면에 출력합니다.
    cv2.imshow("Frame", img)
    key = cv2.waitKey(1)
    if key == 27:  # 'ESC' 키를 누르면 종료합니다.
        break

cap.release()
cv2.destroyAllWindows()
