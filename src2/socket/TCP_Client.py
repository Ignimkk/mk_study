import sys
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5 import uic
from PyQt5.QtCore import QRegExp
from PyQt5.QtCore import QTimer

import socket
import struct
import datetime

from_class = uic.loadUiType("TCP_Client.ui")[0]

class WindowClass(QMainWindow, from_class):
    def __init__(self):
        super().__init__()
        self.setupUi(self)
        # IP address format

        self.connected = False
        self.timer = QTimer(self)
        self.timer.start(1000)
        range = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])"
        ipRegex = QRegExp("^" + range + "\\." + range + "\\." + range + "\\." + range + "$")


        self.ipEdit.setValidator(QRegExpValidator(ipRegex, self))
        self.portEdit.setValidator(QIntValidator())
        self.degree.setValidator(QIntValidator())

        self.setWindowTitle("TCP Client")
        
        self.ConnectBtn.clicked.connect(self.connect)
        self.led21.clicked.connect(self.clickLED21)
        self.led22.clicked.connect(self.clickLED22)
        self.led23.clicked.connect(self.clickLED23)
        self.move.clicked.connect(self.clickMove)
        self.timer.time
    
    def clickMove(self):
        degree = int(self.degree.text())    
        self.updateLED(5, degree)

    def clickLED21(self):
        isOn = self.led21.isChecked()
        self.updateLED(21, isOn)

    def clickLED22(self):
        isOn = self.led22.isChecked()
        self.updateLED(22, isOn)

    def clickLED23(self):
        isOn = self.led23.isChecked()
        self.updateLED(23, isOn)

    def updateLED(self, pin, status):
        data = struct.pack('@ii', pin, status)  # struct 모듈의 pack 함수 사용
        self.sock.send(data)  # 데이터를 소켓으로 전송
        rev_data = self.recv_all(struct.calcsize('@ii'))  # 정확한 크기의 데이터 수신
        rev = struct.unpack('@ii', rev_data)  # struct 모듈의 unpack 함수 사용
        print(rev)


    def recv_all(self, size):
        data = b''
        while len(data) < size:
            packet = self.sock.recv(size - len(data))
            if not packet:
                return None
            data += packet
        return data

    def connect(self):
        ip = self.ipEdit.text()
        port = self.portEdit.text()

        self.sock = socket.socket()
        self.sock.connect((ip, int(port)))

        # message = "Hello TCP/IP!"
        # self.sock.send(message.encode())

        # data = ""
        # while len(data) < len(message):
        #     data += self.sock.recv(1).decode()

        # print(data)

    def __del__(self):
        self.sock.close()

if __name__ == "__main__":
    app = QApplication(sys.argv)
    myWindows = WindowClass()
    myWindows.show()
    sys.exit(app.exec_())
