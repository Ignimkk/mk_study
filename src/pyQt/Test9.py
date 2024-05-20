import sys
from PyQt6.QtWidgets import *
from PyQt6.QtGui import *
from PyQt6 import uic


from_class = uic.loadUiType("Test9.ui")[0]

class WindowClass(QMainWindow, from_class): 
    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.setWindowTitle("Test9")

        min = self.spinBox.minimum()
        max = self.spinBox.minimum()
        step = self.spinBox.minimum()

        self.editMin.setText(str(min))
        self.editMax.setText(str(max))
        self.editStep.setText(str(step))

        self.slider.setRange(min,max)
        self.slider.setSingleStep(step)
        
        self.btnApply.clicked.connect(self.apply)
        self.spinBox.valueChanged.connect(self.change)
        self.slider.valueChanged.connect(self.changeSlider)

        self.pixmap = QPixmap()
        self.pixmap.load("/home/addinedu/Downloads/gigi.png")
        

        # 이미지 리사이즈
        self.resized_pixmap = self.pixmap.scaled(self.labelpixmap.width(),self.labelpixmap.height())
        self.labelpixmap.setPixmap(self.resized_pixmap)

        self.btnApply_2.clicked.connect(self.openFile)

    def openFile(self):
        name, _ = QFileDialog.getOpenFileName(self, '파일 열기', '', '이미지 파일 (*.png *.jpg *.bmp)')

        if name:
            pixmap = QPixmap(name)
            
            if not pixmap.isNull():
                self.labelpixmap.setPixmap(pixmap)
            else:
                QMessageBox.warning(self, '경고', '유효하지 않은 이미지 파일입니다.')
    

    def changeSlider(self):
        actualValue = self.slider.value()
        self.labelValue_2.setText(str(actualValue))
        self.spinBox.setValue(actualValue)
        self.pixmap = QPixmap()
        self.pixmap.load(name)
        self.pixmap = self.pixmap.scaled(actualValue,actualValue)
        self.labelpixmap.setPixmap(self.pixmap)
        self.labelpixmap.resize(self.pixmap.width(),self.labelpixmap.height())

        
     

    # def resizeImage(self):

    #     self.pixmap = QPixmap()
    #     min = int(self.editMin.text())
    #     max = int(self.editMax.text())
    #     step = int(self.editStep.text())

    #     width = min + self.slider.value() * step
    #     height = max + self.slider.value() * step

    #     self.resized_pixmap = self.pixmap.scaled(width, height)
    #     self.labelpixmap.setPixmap(self.resized_pixmap)


    def change(self):
        actualValue = self.spinBox.value()
        self.labelValue.setText(str(actualValue))
        self.slider.setValue(actualValue)
        


    def apply(self):
        min = int(self.editMin.text())
        max = int(self.editMax.text())
        step = int(self.editStep.text())

        self.spinBox.setRange(min, max)
        self.spinBox.setSingleStep(step)

        self.slider.setRange(min, max)
        self.slider.setSingleStep(step)
        # self.pixmap = QPixmap()
        # self.resizeImage() 

        # self.resized_pixmap = self.pixmap.scaled(self.labelpixmap.width(), self.labelpixmap.height())
        # self.labelpixmap.setPixmap(self.resized_pixmap)




if __name__ == "__main__":
    app = QApplication([])
    myWindows = WindowClass() 
    myWindows.show()
    app.exec()