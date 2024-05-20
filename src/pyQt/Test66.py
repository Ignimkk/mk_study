import sys
import mysql.connector
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5 import uic
from PyQt5.QtGui import *
amrbase = mysql.connector.connect(
    host = "database-1.cdsoiiswk6c2.ap-northeast-2.rds.amazonaws.com",
    port = 3306,
    user = "robot",
    password = "6074",
    database = "amrbase"
)

cursor = amrbase.cursor(buffered=True)

cursor.execute("SELECT name, sex, birthday FROM celeb")
result = cursor.fetchall()


from_class = uic.loadUiType("Test6.ui")[0]

class WindowClass(QMainWindow, from_class): 
    def __init__(self):

        super().__init__()
        self.setupUi(self)
        self.setWindowTitle("Test6")
        self.tableWidget.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)
        self.pushButton.clicked.connect(self.Add)

    def Add(self):
        row = self.tableWidget.rowCount()
        self.tableWidget.insertRow(row)
        for i in range(len(result)):
            name = result[i][0]
            gender = result[i][1]
            birthday = result[i][2]

            # name_input = self.lineEdit.text(name)
            # gender_input = self.lineEdit.text(gender)
            # birthday_input = self.lineEdit.text(birthday)

            self.tableWidget.setItem(row,0,QTableWidgetItem(name))
            self.tableWidget.setItem(row,1,QTableWidgetItem(gender))
            self.tableWidget.setItem(row,2,QTableWidgetItem(birthday))



if __name__ == "__main__":    
    app = QApplication(sys.argv) 
    myWindows = WindowClass() 
    myWindows.show()

    sys.exit(app.exec_())