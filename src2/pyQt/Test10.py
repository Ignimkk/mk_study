import sys
from PyQt6.QtWidgets import *
from PyQt6.QtGui import *
from PyQt6 import uic
from PyQt6 import QtCore, QtGui, QtWidgets, uic
from PyQt6.QtCore import *

from_class = uic.loadUiType("Test10.ui")[0]

class WindowClass(QMainWindow, from_class): 
    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.setWindowTitle("Test10")

        self.canvas = QtGui.QPixmap(self.label.width(), self.label.height())
        self.canvas.fill(Qt.GlobalColor.white)
        self.label.setPixmap(self.canvas)
        self.setCentralWidget(self.label)
        self.draw()


    def draw(self):
        self.canvas = self.label.pixmap()
        painter = QtGui.QPainter(self.canvas)
        self.pen = QPen(Qt.GlobalColor.red, 5, Qt.SolidLine)
        painter.drawLine(100, 100, 500, 100)
        painter.drawLine(100, 200, 500, 200)
        self.p1 = QPoint(100,300)
        self.p2 = QPoint(800,300)
        painter.drawLine(self.p1,self.p2)
        painter.end()
        self.label.setPixmap(self.canvas)


if __name__ == "__main__":
    app = QApplication([])
    myWindows = WindowClass() 
    myWindows.show()
    app.exec()