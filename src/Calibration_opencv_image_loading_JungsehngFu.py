__author__ = "Mingu Kim"
__email__ = "mingu216@gmail.com"
__date__ = "August 2018"
'''
# A (Intrinsic Parameters) [fc, skew_c * fx, cx], [0, fy, cy], [0, 0, 1]
cameraMatrix = np.array([[fx, skew_c * fx, cx],
                         [0, fy, cy],
                         [0, 0, 1]])

# Distortion Coefficients(kc) - 1st(k1), 2nd(k2), 3rd(p1), 4th(p2), 5th(k3)
distCoeffs = np.array([k1, k2, p1, p2, k3])  # just use first two terms
'''

from Calibration_opencv_image_saving_JunshengFu import undistort_image, load_calibration
import numpy as np
import cv2

image_name = 'image/Grandeur/color/image_8_color.jpg'            # <-------------------------- 수정
# loading
img = cv2.imread(image_name) #<- 비교할거
calib_file = 'image/Grandeur/color/calibration_pickle.p'            # <-------------------------- 수정

mtx, dist = load_calibration(calib_file)
print('CameraMatrix (mtx)', mtx)
print('Distortion Coefficiont (dist)', dist)
fx = mtx[0][0]; fy = mtx[1][1]; cx = mtx[0][2]; cy = mtx[1][2]
k1 = dist[0][0]; k2 = dist[0][1]; p1 = dist[0][2]; p2 = dist[0][3]; k3 = dist[0][4]
print('fx, fy, cx, cy :', fx, fy, cx, cy)
#print('k1, k2, p1, p2, k3 :', k1, k2, p1, p2, k3)

# saving as .txt
f = open('image/Grandeur/color/intrinsic_parameter.txt', 'w')              # <-------------------------- 수정
matrix_undistort = "%0.40f\n%0.40lf\n%0.40lf\n%0.40lf\n%0.40lf\n%0.40lf\n%0.40lf\n%0.40lf\n%0.40lf" % (fx, fy, cx, cy, k1, k2, p1, p2, k3)
f.write(matrix_undistort)
f.close()

# saving 2 images for comparison
img_undist = cv2.undistort(img, mtx, dist, None, mtx)
cv2.imwrite('image/Grandeur/color/comparison/image_8_color_calibresult.jpg', img_undist) #undistorted             # <-------------------------- 수정
cv2.imwrite('image/Grandeur/color//comparison/image_8_color_original.jpg', img) #original            # <-------------------------- 수정
print("saving images and parameters are successfully done")