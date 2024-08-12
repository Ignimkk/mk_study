import sys
import requests
from PyQt5.QtWidgets import QApplication, QWidget, QPushButton, QVBoxLayout, QFileDialog
import os

class VideoUploadClient(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()
        self.video_paths = []

    def initUI(self):
        self.setWindowTitle('YOLOv8 Video Upload Client')

        self.uploadButton = QPushButton('Upload Videos', self)
        self.uploadButton.clicked.connect(self.upload_videos)

        self.downloadButton = QPushButton('Download Annotated Videos', self)
        self.downloadButton.clicked.connect(self.download_videos)

        layout = QVBoxLayout()
        layout.addWidget(self.uploadButton)
        layout.addWidget(self.downloadButton)
        self.setLayout(layout)

    def upload_videos(self):
        options = QFileDialog.Options()
        options |= QFileDialog.ReadOnly
        file_dialog = QFileDialog(self)
        file_dialog.setFileMode(QFileDialog.ExistingFiles)
        file_dialog.setNameFilter("Video Files (*.mp4)")
        if file_dialog.exec_():
            selected_files = file_dialog.selectedFiles()
            if selected_files:
                self.video_paths = selected_files
                self.send_videos_to_server()

    def send_videos_to_server(self):
        url = 'http://192.168.0.201:5000/api/upload'
        files = [('videos', (os.path.basename(path), open(path, 'rb'))) for path in self.video_paths]
        response = requests.post(url, files=files)

        if response.status_code == 201:
            print("Videos uploaded successfully")
            self.processed_videos = response.json().get('processed_videos', [])
        else:
            print("Error uploading videos")
            self.processed_videos = []

    def download_videos(self):
        for video_name in self.processed_videos:
            url = f'http://192.168.0.201:5000/api/download/{video_name}'
            response = requests.get(url)

            if response.status_code == 201:
                filename = os.path.join('/home/addinedu/dev_ws/src/video', video_name)
                with open(filename, 'wb') as f:
                    f.write(response.content)
                print(f"Annotated video '{filename}' downloaded successfully")
            else:
                print(f"Error downloading annotated video '{video_name}'")

if __name__ == '__main__':
    app = QApplication(sys.argv)
    client = VideoUploadClient()
    client.show()
    sys.exit(app.exec_())
