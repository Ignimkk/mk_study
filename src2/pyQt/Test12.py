import sys
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5 import uic
import cv2, imutils
from Camera import Camera
from_class = uic.loadUiType("Test12.ui")[0]
import time
import datetime
from PyQt5.QtCore import *


class VideoThread(QThread):
    frame_processed = pyqtSignal(object)

    def __init__(self, filename):
        super().__init__()
        self.filename = filename

    def run(self):
        video = cv2.VideoCapture(self.filename)
        fps = video.get(cv2.CAP_PROP_FPS)
        if fps == 0:
            fps = 30
        while video.isOpened():
            ret, frame = video.read()
            if not ret:
                break
            self.frame_processed.emit(frame)
            self.msleep(int(1000 // fps))
            time.sleep(0.05)
        video.release()



class WindowClass(QMainWindow, from_class): 
    def __init__(self):
        super().__init__()

        self.setupUi(self)
        self.setWindowTitle("Test12")

        self.isCameraOn = False
        self.isRecStart = False

        self.btnRecord.hide()

        self.camera = Camera(self)
        self.pixmap = QPixmap()
        self.camera.daemon = True
        self.count = 0

        self.record = Camera(self)
        self.record.daemon = True

        self.btnOpen.clicked.connect(self.openFile)
        self.btnCamera.clicked.connect(self.clickCamera)
        self.camera.update.connect(self.updateCamera)
        self.btnRecord.clicked.connect(self.clickRecord)
        self.record.update.connect(self.updateRecording)
        self.btnCapture.clicked.connect(self.capture)

        self.count = 0

    def capture(self):
        self.now = datetime.datetime.now().strftime('%Y%m%d_%H%M%S')
        filename = self.now + '.png'

        cv2.imwrite(filename, cv2.cvtColor(self.cap, cv2.COLOR_RGB2BGR))


    def updateRecording(self):
        self.writer.write(self.cap)

    def clickRecord(self):
        if self.isRecStart == False:
            self.btnRecord.setText('Rec Stop')
            self.isRecStart = True

            self.recordingStart()
        else:
            self.btnRecord.setText('Rec Start')
            self.isRecStart = False

            self.recordingStop()

    def recordingStart(self):
        self.record.running = True
        self.record.start()

        self.now = datetime.datetime.now().strftime('%Y%m%d_%H%M%S')
        filename = self.now + '.avi'
        self.fourcc = cv2.VideoWriter_fourcc(*'XVID')

        w = int(self.video.get(cv2.CAP_PROP_FRAME_WIDTH))
        h = int(self.video.get(cv2.CAP_PROP_FRAME_HEIGHT))

        self.writer = cv2.VideoWriter(filename, self.fourcc, 20.0, (w,h))

    def recordingStop(self):
        self.record.running = False

        if self.isRecStart == True:
            self.writer.release()

    def clickCamera(self):
        if self.isCameraOn == False:
            self.btnCamera.setText("Camera off")
            self.isCameraOn = True
            self.btnRecord.show()
            self.cameraStart()

        else:
            self.btnCamera.setText("Camera on")
            self.isCameraOn = False
            self.btnRecord.hide()

            self.cameraStop()
            self.recordingStop()


    
    # def openFile(self):
    #     file = QFileDialog.getOpenFileName(filter='Image or Video (*.png *.jpg *.jpeg *.bmp *.avi)')

    #     filename = file[0]
    #     if filename: 
    #         if filename.endswith('.avi'):  
    #             self.video = cv2.VideoCapture(filename)  
    #             fps = self.video.get(cv2.CAP_PROP_FPS)  
    #             if fps == 0:  
    #                 fps = 30
    #             self.timer = QTimer(self)  
    #             self.timer.timeout.connect(self.updateVideo)  
    #             self.timer.start(int(1000 // fps)) 
    #         else:  
    #             self.cap = cv2.imread(filename)  
    #             self.cap = cv2.cvtColor(self.cap, cv2.COLOR_BGR2RGB)
    #             h, w, c = self.cap.shape
    #             qimage = QImage(self.cap.data, w, h, w * c, QImage.Format_RGB888)
    #             self.pixmap = QPixmap.fromImage(qimage)
    #             self.pixmap = self.pixmap.scaled(self.label.width(), self.label.height())
    #             self.label.setPixmap(self.pixmap)

    def openFile(self):
        file = QFileDialog.getOpenFileName(filter='Image or Video (*.png *.jpg *.jpeg *.bmp *.avi)')
        filename = file[0]
        if filename: 
            if filename.endswith('.avi'):  
                self.video_thread = VideoThread(filename)
                self.video_thread.frame_processed.connect(self.updateVideo)
                self.video_thread.start()
            else:  
                self.cap = cv2.imread(filename)  
                self.cap = cv2.cvtColor(self.cap, cv2.COLOR_BGR2RGB)
                h, w, c = self.cap.shape
                qimage = QImage(self.cap.data, w, h, w * c, QImage.Format_RGB888)
                self.pixmap = QPixmap.fromImage(qimage)
                self.pixmap = self.pixmap.scaled(self.label.width(), self.label.height())
                self.label.setPixmap(self.pixmap)

    def updateVideo(self, frame):
            qimage = QImage(frame, frame.shape[1], frame.shape[0], frame.strides[0], QImage.Format_RGB888)
            pixmap = QPixmap.fromImage(qimage)
            pixmap = pixmap.scaled(self.label.width(), self.label.height())
            self.label.setPixmap(pixmap)


    def cameraStart(self):
        self.camera.running = True
        self.camera.start()
        self.video = cv2.VideoCapture(0)
        

    def cameraStop(self):
        self.camera.running = False
        self.count = 0
        self.video.release()
    
    def updateCamera(self):
        ret, self.cap = self.video.read()
        if ret:
            self.cap = cv2.cvtColor(self.cap, cv2.COLOR_BGR2RGB)

            h,w,c = self.cap.shape
            qimage = QImage(self.cap.data,w,h,w*c, QImage.Format_RGB888 )

            self.pixmap = self.pixmap.fromImage(qimage)
            self.pixmap = self.pixmap.scaled(self.label.width(), self.label.height())

            self.label.setPixmap(self.pixmap)
        self.label_2.setText('run:' + str(self.count))
        self.count += 1

    # def updateVideo(self):
    #     ret, self.cap = self.video.read()
    #     if ret:
    #         # self.cap = cv2.cvtColor(self.cap, cv2.COLOR_BGR2RGB)

    #         h,w,c = self.cap.shape
    #         qimage = QImage(self.cap.data,w,h,w*c, QImage.Format_RGB888 )

    #         self.pixmap = self.pixmap.fromImage(qimage)
    #         self.pixmap = self.pixmap.scaled(self.label.width(), self.label.height())

    #         self.label.setPixmap(self.pixmap)
    #     self.label_2.setText('run:' + str(self.count))
    #     self.count += 1


if __name__ == "__main__":    
    app = QApplication(sys.argv) 
    myWindows = WindowClass() 
    myWindows.show()

    sys.exit(app.exec_())
