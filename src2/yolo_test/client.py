import sys
from PyQt5.QtWidgets import QApplication, QWidget, QVBoxLayout, QPushButton, QFileDialog, QLabel
import requests

class VideoUploader(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.layout = QVBoxLayout()

        self.uploadButton = QPushButton('Upload Video', self)
        self.uploadButton.clicked.connect(self.upload_video)
        self.layout.addWidget(self.uploadButton)

        self.resultLabel = QLabel('Result: ', self)
        self.layout.addWidget(self.resultLabel)

        self.setLayout(self.layout)
        self.setWindowTitle('Video Uploader')
        self.show()

    def upload_video(self):
        options = QFileDialog.Options()
        self.filePath, _ = QFileDialog.getOpenFileName(self, "Select Video", "", options=options)
        if self.filePath:
            self.resultLabel.setText('Video selected: ' + self.filePath)
            with open(self.filePath, 'rb') as f:
                files = {'video': f}
                # 서버 PC의 IP 주소와 포트를 설정
                server_address = 'http://192.168.1.214:5000'
                response = requests.post(f'{server_address}/api/upload', files=files)
                if response.status_code == 200:
                    result = response.json().get('message', 'No result')
                    self.resultLabel.setText(f'Result: {result}')
                else:
                    self.resultLabel.setText('Upload failed')

if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = VideoUploader()
    sys.exit(app.exec_())
