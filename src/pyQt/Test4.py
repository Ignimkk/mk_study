import sys
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5 import uic

from_class = uic.loadUiType("Test4.ui")[0]

class WindowClass(QMainWindow, from_class): 
    def __init__(self):

        super().__init__()
        self.setupUi(self)
        self.setWindowTitle("Test4")

        self.pushButton.clicked.connect(self.addText)
        self.pushButton_2.clicked.connect(lambda: self.setFont("Ubuntu"))
        self.pushButton_3.clicked.connect(lambda: self.setFont("NanumGothic"))

        self.pushButton_4.clicked.connect(lambda: self.setTextColor(255,0,0))
        self.pushButton_5.clicked.connect(lambda: self.setTextColor(0,255,0))
        self.pushButton_6.clicked.connect(lambda: self.setTextColor(0,0,255))
        self.pushButton_7.clicked.connect(self.setTextSize)


    def setTextSize(self):
        text = self.lineEdit.text()
        validator = QIntValidator(1, 100, self)
        state, size, _ = validator.validate(text,0)
        if state == QIntValidator.Acceptable:
            size = int(size)
            self.textEdit_2.selectAll()
            self.textEdit_2.setFontPointSize(size)
            self.textEdit_2.moveCursor(QTextCursor.End)
        else:
            pass

    def setTextColor(self, r, g, b):
        color = QColor(r, g, b)
        self.textEdit_2.selectAll()
        self.textEdit_2.setTextColor(color)
        self.textEdit_2.moveCursor(QTextCursor.End)

    def addText(self):
        input = self.textEdit.toPlainText()
        self.textEdit.clear()
        self.textEdit_2.append(input)

    def setFont(self, fontName):
        font = QFont(fontName, 11)
        self.textEdit_2.setFont(font)

if __name__ == "__main__":    
    app = QApplication(sys.argv) 
    myWindows = WindowClass() 
    myWindows.show()

    sys.exit(app.exec_())
