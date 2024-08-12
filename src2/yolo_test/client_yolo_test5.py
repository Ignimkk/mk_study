import sys
import requests
from PyQt5.QtWidgets import QApplication, QWidget, QPushButton, QVBoxLayout, QFileDialog

class VideoUploadClient(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()
        self.video_path = None

    def initUI(self):
        self.setWindowTitle('YOLOv8 Video Upload Client')

        self.uploadButton = QPushButton('Upload Video', self)
        self.uploadButton.clicked.connect(self.upload_video)

        layout = QVBoxLayout()
        layout.addWidget(self.uploadButton)
        self.setLayout(layout)

    def upload_video(self):
        options = QFileDialog.Options()
        options |= QFileDialog.ReadOnly
        fileName, _ = QFileDialog.getOpenFileName(self, "Select Video File", "", "All Files (*);;MP4 Files (*.mp4)", options=options)
        if fileName:
            self.video_path = fileName
            self.send_video_to_server()

    def send_video_to_server(self):
        url = 'http://192.168.0.201:5000/api/upload'
        files = {'video': open(self.video_path, 'rb')}
        response = requests.post(url, files=files)

        if response.status_code == 201:
            print("Video uploaded successfully")
        else:
            print("Error uploading video")

if __name__ == '__main__':
    app = QApplication(sys.argv)
    client = VideoUploadClient()
    client.show()
    sys.exit(app.exec_())
