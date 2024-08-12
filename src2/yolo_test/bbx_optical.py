import cv2
import numpy as np

# YOLOv8 모델을 초기화하고 가중치 및 구성 파일을 로드합니다.
net = cv2.dnn.readNet("yolov8.weights", "yolov8.cfg")
layer_names = net.getLayerNames()
output_layers = [layer_names[i[0] - 1] for i in net.getUnconnectedOutLayers()]

# 이전 프레임을 저장하기 위한 변수 초기화
prev_frame = None

# 비디오 스트림 또는 웹캠을 초기화합니다.
cap = cv2.VideoCapture("video.mp4")  # 비디오 파일 이름 또는 웹캠 디바이스 번호로 변경 가능

# 옵티컬 플로우 파라미터 설정
lk_params = dict(winSize=(15, 15),
                 maxLevel=2,
                 criteria=(cv2.TERM_CRITERIA_EPS | cv2.TERM_CRITERIA_COUNT, 10, 0.03))

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

    # 감지된 바운딩 박스에 대한 옵티컬 플로우를 계산합니다.
    if prev_frame is not None:
        for out in outs:
            for detection in out:
                scores = detection[5:]
                class_id = np.argmax(scores)
                confidence = scores[class_id]
                if confidence > 0.5 and class_id == 0:  # 차선 클래스에 대한 검사
                    center_x = int(detection[0] * width)
                    center_y = int(detection[1] * height)
                    w = int(detection[2] * width)
                    h = int(detection[3] * height)
                    x = int(center_x - w / 2)
                    y = int(center_y - h / 2)

                    # 현재 프레임에서 바운딩 박스를 그립니다.
                    cv2.rectangle(frame, (x, y), (x + w, y + h), (255, 0, 0), 2)

                    # 이전 프레임과 현재 프레임에서 관심 영역 설정
                    prev_roi = prev_frame[y:y+h, x:x+w]
                    curr_roi = frame[y:y+h, x:x+w]

                    # 옵티컬 플로우를 계산하여 바운딩 박스의 이동 벡터를 추출합니다.
                    prev_gray = cv2.cvtColor(prev_roi, cv2.COLOR_BGR2GRAY)
                    curr_gray = cv2.cvtColor(curr_roi, cv2.COLOR_BGR2GRAY)
                    p0 = cv2.goodFeaturesToTrack(prev_gray, mask=None, maxCorners=100, qualityLevel=0.3, minDistance=7, blockSize=7)
                    p1, st, err = cv2.calcOpticalFlowPyrLK(prev_gray, curr_gray, p0, None, **lk_params)

                    # 이동 벡터를 시각화합니다.
                    for i, (new, old) in enumerate(zip(p1, p0)):
                        a, b = new.ravel()
                        c, d = old.ravel()
                        frame = cv2.arrowedLine(frame, (int(c + x), int(d + y)), (int(a + x), int(b + y)), (0, 255, 0), 2)

    # 현재 프레임을 이전 프레임으로 업데이트합니다.
    prev_frame = frame.copy()

    # 결과를 화면에 출력합니다.
    cv2.imshow("Frame", frame)
    key = cv2.waitKey(1)
    if key == 27:  # 'ESC' 키를 누르면 종료합니다.
        break

cap.release()
cv2.destroyAllWindows()
