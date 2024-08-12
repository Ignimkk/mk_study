# import cv2
# import numpy as np

# img = np.ones((512,512,3), np.uint8)

# def draw_circle(event, x, y, flags, param):
#     if event == cv2.EVENT_LBUTTONDOWN:
#         cv2.circle(img, (x,y), 30, (50,50,200),-1)

#     if event == cv2.EVENT_RBUTTONDOWN:
#         cv2.circle(img, (x,y), 30, (50,50,200),-1)
    

# cv2.namedWindow(winname= 'zz')
# cv2.setMouseCallback('zz', draw_circle, img)

# while True:
#     cv2.imshow('zz', img)

#     if cv2.waitKey() == ord('q'):
#         break

# cv2.destroyAllWindows()

import cv2
import numpy as np

img = np.ones((512, 512, 3), np.uint8)

def draw_circle(event, x, y, flags, param):
    if event == cv2.EVENT_LBUTTONDOWN:
        cv2.circle(img, (x, y), 30, (50, 50, 200), -1)
    elif event == cv2.EVENT_RBUTTONDOWN:
        cv2.circle(img, (x, y), 30, (200, 50, 50), -1)

cv2.namedWindow(winname='zz')
cv2.setMouseCallback('zz', draw_circle)

while True:
    cv2.imshow('zz', img)
    key = cv2.waitKey(1) & 0xFF
    if key == ord('q'):
        break

cv2.destroyAllWindows()
