from PyQt5.QtWidgets import QApplication, QMainWindow, QTableWidgetItem
from PyQt5 import uic
import mysql.connector

from_class = uic.loadUiType("Test6.ui")[0]

class WindowClass(QMainWindow, from_class): 
    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.setWindowTitle("Test6")

        for year in range(1960, 2022+1):
            self.Year_1.addItem(str(year))
            self.Year_2.addItem(str(year))

        for month in range(1, 12 + 1):
            self.month_1.addItem(str(month))
            self.month_2.addItem(str(month))

        for day in range(1, 31+ 1):
            self.day_1.addItem(str(day))
            self.day_2.addItem(str(day))

        self.Year_1.setCurrentText(str(1990))
        self.Year_2.setCurrentText(str(2022))
        self.day_1.currentIndexChanged.connect(self.printBirthday)
        
        self.pushButton.clicked.connect(self.Add)
        self.tableWidget.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)

    def printBirthday(self):
        year1 = self.Year_1.currentText()
        year2 = self.Year_2.currentText()
        month1 = self.month_1.currentText()
        month2 = self.month_2.currentText()
        day1 = self.day_1.currentText()
        day2 = self.day_2.currentText()

        self.result.setText(year1 + '-' + month1.zfill(2) + '-' + day1.zfill(2))
        self.result2.setText(year2 + '-' + month2.zfill(2) + '-' + day2.zfill(2))

    def db(self, min_bir, max_bir):
        amrbase = mysql.connector.connect(
            host = "database-1.cdsoiiswk6c2.ap-northeast-2.rds.amazonaws.com",
            port = 3306,
            user = "robot",
            password = "6074",
            database = "amrbase"
        )
        cursor = amrbase.cursor(buffered=True)
        cursor.execute("SELECT * FROM celeb WHERE birthday BETWEEN (SELECT MIN(birthday) FROM celeb WHERE birthday > %s) AND (SELECT MAX(birthday) FROM celeb WHERE birthday < %s);", (min_bir, max_bir))
        result = cursor.fetchall()
        return result
        
    def Add(self):
        min_bir = self.result.text()
        max_bir = self.result2.text()

        result = self.db(min_bir, max_bir)

        self.tableWidget.setRowCount(0)  # 테이블 위젯 초기화

        for i, row in enumerate(result):
            self.tableWidget.insertRow(i)
            name = row[1]
            birthday = row[2].strftime('%Y-%m-%d')  # 날짜를 문자열로 변환
            age = str(row[3])
            gender = row[4]
            agency = row[5]

            self.tableWidget.setItem(i, 0, QTableWidgetItem(name))
            self.tableWidget.setItem(i, 1, QTableWidgetItem(birthday))
            self.tableWidget.setItem(i, 2, QTableWidgetItem(age))
            self.tableWidget.setItem(i, 3, QTableWidgetItem(gender))
            self.tableWidget.setItem(i, 4, QTableWidgetItem(agency))

if __name__ == "__main__":
    app = QApplication([])
    myWindows = WindowClass() 
    myWindows.show()
    app.exec_()