import cv2
import numpy as np

# 주행 영상 읽기
video = cv2.VideoCapture('drive.webm')


while True:
    ret, frame = video.read()
    if not ret:
        break
    
    # 이미지 전처리
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    
    # 가우시안 블러 적용 (노이즈 제거)
    blur = cv2.GaussianBlur(gray, (5, 5), 0)
    
    # 적응적 이진화 적용
    _, thresh = cv2.threshold(blur, 190, 255, cv2.THRESH_BINARY)
    
    # 엣지 감지
    edges = cv2.Canny(thresh, 50, 150)
    
    # 차선 검출
    lines = cv2.HoughLinesP(edges, 1, np.pi/180, 100, minLineLength=100, maxLineGap=50)
    
    if lines is not None:
        for line in lines:
            x1, y1, x2, y2 = line[0]
            cv2.line(frame, (x1, y1), (x2, y2), (0, 255, 0), 2)

    # 결과 표시
    cv2.imshow('Lane Detection', frame)
    
    # 종료 조건
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# 자원 해제 및 창 닫기
video.release()
cv2.destroyAllWindows()