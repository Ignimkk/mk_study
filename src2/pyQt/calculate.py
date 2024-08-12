import sys
from PyQt6.QtWidgets import *
from PyQt6.QtGui import *
from PyQt6 import uic

from_class = uic.loadUiType("calculate.ui")[0]


class WindowClass(QMainWindow, from_class): 
    def __init__(self):

        super().__init__()
        self.setupUi(self)
        self.setWindowTitle("calculate")
        self.dp_flag = False
        self.result_flag = False
        self.last_input = ''
        self.cal =''
        self.abc_flag = False

        self.num0.clicked.connect(lambda: self.button_click('0'))
        self.num1.clicked.connect(lambda: self.button_click('1'))
        self.num2.clicked.connect(lambda: self.button_click('2'))
        self.num3.clicked.connect(lambda: self.button_click('3'))
        self.num4.clicked.connect(lambda: self.button_click('4'))
        self.num5.clicked.connect(lambda: self.button_click('5'))
        self.num6.clicked.connect(lambda: self.button_click('6'))
        self.num7.clicked.connect(lambda: self.button_click('7'))
        self.num8.clicked.connect(lambda: self.button_click('8'))
        self.num9.clicked.connect(lambda: self.button_click('9'))

        self.pushButton_M.clicked.connect(lambda: self.button_click('-'))
        self.pushButton_Plus.clicked.connect(lambda: self.button_click('+'))
        self.pushButton_D.clicked.connect(lambda: self.button_click('/'))
        self.pushButton_x.clicked.connect(lambda: self.button_click('*'))
        self.pushButton_result.clicked.connect(self.reresult)
        self.pushButton_result.clicked.connect(self.equal)
        

        self.pushButton_AC.clicked.connect(self.reset)
        self.pushButton_C.clicked.connect(self.delete)
        self.pushButton_dot.clicked.connect(lambda: self.button_click('.'))

        # self.pushButton_on_off.clicked.connect(self.on_off)
        self.pushButton_abc.clicked.connect(self.toggle_parentheses)

    def toggle_parentheses(self):
        if self.abc_flag == True:
            self.button_click(')')
            self.abc_flag = False
        else:
            self.button_click('(')
            self.abc_flag = True


    def reset(self):
        self.lineEdit.setText("")
        self.dp_flag = False
        self.result_flag =False
        self.last_input = ''
        self.cal =''
        self.abc_flag = False

    # '='을 연속으로 누르면 직전에 실행한 연산을 한번 더함
    def reresult(self):
        if self.result_flag == True:
            self.lineEdit.setText((self.lineEdit.text() + self.cal + self.last_input))
            result = eval(self.lineEdit.text())
            self.lineEdit.clear()
            self.lineEdit.setText(str(result))
            self.result_flag = True
            self.dp_flag = True
            print("re equal:", self.cal)
            print("re, last_input", self.last_input)


    def button_click(self, text):
        # 결과 출력 직 후 연산자 입력만 가능
        if self.result_flag == True:
            if text in ['+','-','*','/']:
                self.lineEdit.setText((self.lineEdit.text() + text))
                self.result_flag = False
                self.dp_flag = False
                self.last_input = ''
                return

        #평소
        else:
            if text in ['+', '-', '*', '/'] and self.last_input in ['+', '-', '*', '/']:
                return
            # 모든 flag가 꺼져있음 그렇기 때문에 아무거나 입력되도 됨.
            if self.dp_flag == False and self.result_flag == False:
                if text == '.' and '.' in self.last_input:
                    return  # 이미 소수점이 존재하면 더 이상 추가하지 않음
                 
                self.lineEdit.setText((self.lineEdit.text() + text))
                print("입력값 :", text)
                pre = text
                if pre in ['+', '-', '*', '/']:
                    self.dp_flag = True
                    self.cal = pre
                    print(self.cal)
                else:
                    self.dp_flag = False
            
            #연산자가 나와서 dp_flag가 True 임. 그 다음엔 반드시 숫자.    
            if self.dp_flag == True and self.result_flag == False:
                if text == '.' and '.' in self.last_input:
                    return 
                if text in ['1','2','3','4','5','6','7','8','9','(',')']:
                    self.lineEdit.setText((self.lineEdit.text() + text))
                    self.dp_flag = False

            if text in ['+', '-', '*', '/']:
                self.last_input = ''

            # 숫자 입력 시 last_input 업데이트
            if text.isdigit():
                self.last_input += text
            elif text == '.':
                self.last_input += text


    def delete(self):
        current_text = self.lineEdit.text()
        if self.result_flag == False:

            if current_text:
                self.lineEdit.setText(current_text[:-1])
                self.last_input = ''

            if current_text[:-1] == '(':
                self.abc_flag = False
            else:
                self.abc_flag = True  
        
    def equal(self):
        try:
            result = eval(self.lineEdit.text())
            self.lineEdit.clear()
            self.lineEdit.setText(str(result))
            self.result_flag = True
            self.dp_flag = True

        except:
            print('error')



if __name__ == "__main__":
    app = QApplication([])
    myWindows = WindowClass() 
    myWindows.show()
    app.exec()

    
       


