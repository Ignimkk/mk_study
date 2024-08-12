import sys
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5 import uic

from_class = uic.loadUiType("Test.ui")[0]

class WindowClass(QMainWindow, from_class): 
    def __init__(self):

        super().__init__()
        self.setupUi(self)
        self.setWindowTitle("Hello, Qt!")

        self.pushButton_1.clicked.connect(self.button1_Clicked)
        self.pushButton_2.clicked.connect(self.button2_Clicked)
        self.pushButton_3.clicked.connect(self.button3_Clicked)
        
        self.checkBox_1.clicked.connect(self.check1_Clicked)
        self.checkBox_2.clicked.connect(self.check2_Clicked)
        self.checkBox_3.clicked.connect(self.check3_Clicked)
        self.checkBox_4.clicked.connect(self.check4_Clicked)

    def check1_Clicked(self):
        if (self.checkBox_1.isChecked()):
            self.textEdit.setText("CheckBox 1 Checked")
            self.checkBox_5.setChecked(True)
        else:
            self.textEdit.setText("CheckBox 1 Unchecked")
            self.checkBox_5.setChecked(False)


    def check2_Clicked(self):
        if (self.checkBox_2.isChecked()):
            self.textEdit.setText("CheckBox 2 Checked")
            self.checkBox_6.setChecked(True)
        else:
            self.textEdit.setText("CheckBox 2 Unchecked")
            self.checkBox_6.setChecked(False)


    def check3_Clicked(self):
        if (self.checkBox_3.isChecked()):
            self.textEdit.setText("CheckBox 3 Checked")
            self.checkBox_7.setChecked(True)
        else:
            self.textEdit.setText("CheckBox 3 Unchecked")
            self.checkBox_7.setChecked(False)

    def check4_Clicked(self):
        if (self.checkBox_4.isChecked()):
            self.textEdit.setText("CheckBox 4 Checked")
            self.checkBox_8.setChecked(True)
        else:
            self.textEdit.setText("CheckBox 4 Unchecked")
            self.checkBox_8.setChecked(False)
        
    def radioClicked(self):
        if self.radio_1.isChecked():
            self.textEdit.setText("Radio 1")
        elif self.radio_2.isChecked():
            self.textEdit.setText("Radio 2")
        elif self.radio_3.isChecked():
            self.textEdit.setText("Radio 3")
        else:
            self.textEdit.setText("Unknown")

    def button1_Clicked(self):
        self.textEdit.setText("Button 1")
        self.radio_1.setChecked(True)

    def button2_Clicked(self):
        self.textEdit.setText("Button 2")
        self.radio_2.setChecked(True)

    def button3_Clicked(self):
        self.textEdit.setText("Button 3")
        self.radio_3.setChecked(True)









if __name__ == "__main__":    
    app = QApplication(sys.argv) 
    myWindows = WindowClass() 
    myWindows.show()

    sys.exit(app.exec_())