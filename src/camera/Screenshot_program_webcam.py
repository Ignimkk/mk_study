# -*- coding:utf-8 -*-


'''
title : Code for Calibration
name : Mingu Kim
mail : mingu216@gmail.com
date : 2018/07/21

< Manual >
1. 'video'를 누른다.
2. 옆 B, G, R, H, S, V를 알맞게 조절하여 체스보드판에 빛 반사가 없도록 한다.
3. 'screenshot'을 누르면 1번부터 차례로 저장된다.
4. 20장정도 찍었으면 종료한다.

※ 다시 찍을때 파일명이 중복되니, 한번 찍고 나면 이미지를 다른곳에 옮기고 다시 사용하시오.
'''

from __future__ import absolute_import, print_function, division
from pymba import *

import tkinter as tk
from tkinter import *
import cv2
import time
import numpy as np

from PIL import Image, ImageTk
from itertools import count

cap = cv2.VideoCapture(0)           # <-------------------------- 수정
print("size of original image : ", cap.get(3), cap.get(4))
x = cap.get(3); y = cap.get(4)
#time.sleep(0.2)

i = 1 # 이미지 저장 번호 증가 지역 변수 선언


root = tk.Tk()
root.geometry("700x600")
root.bind('<Escape>', lambda e: root.quit())
lmain = tk.Label(root)
lmain.pack()

# for track bar
def onChange (x):
    pass

cv2.namedWindow('trackBar')

# bgr
cv2.createTrackbar('blue', 'trackBar', 0, 255, onChange)
cv2.createTrackbar('green', 'trackBar', 0, 255, onChange)
cv2.createTrackbar('red', 'trackBar', 0, 255, onChange)

# hsv
cv2.createTrackbar('hue', 'trackBar', 0, 179, onChange)
cv2.createTrackbar('saturation', 'trackBar', 0, 255, onChange)
cv2.createTrackbar('value', 'trackBar', 0, 255, onChange)

# gray
cv2.createTrackbar("gray", "trackBar", 0, 1, onChange)

def show_frame():

    _, frame = cap.read()
    resize = cv2.resize(frame,(640, 480))
    b, g, r = cv2.split(resize)

    blue = cv2.getTrackbarPos('blue', 'trackBar')
    green = cv2.getTrackbarPos('green', 'trackBar')
    red = cv2.getTrackbarPos('red', 'trackBar')

    # blue
    lim4 = 255 - blue
    b[b > lim4] = 255
    b[b <= lim4] += blue

    # grean
    lim5 = 255 - green
    g[g > lim5] = 255
    g[g <= lim5] += green

    # red
    lim6 = 255 - red
    r[r > lim6] = 255
    r[r <= lim6] += red

    rgb = cv2.merge((r,g,b))
    hsv = cv2.cvtColor(rgb, cv2.COLOR_RGB2HSV)
    h, s, v = cv2.split(hsv)

    hue = cv2.getTrackbarPos('hue', 'trackBar')
    saturation = cv2.getTrackbarPos('saturation', 'trackBar')
    value = cv2.getTrackbarPos('value', 'trackBar')

    # hue
    lim1 = 179 - hue
    h[h > lim1] = 179
    h[h <= lim1] += hue

    # saturation
    lim2 = 255 - saturation
    s[s > lim2] = 255
    s[s <= lim2] += saturation

    # value
    lim3 = 255 - value
    v[v > lim3] = 255
    v[v <= lim3] += value
    #print('v', v)
    #print("h, s, v : ", h, s, v)

    final_hsv = cv2.merge((h, s, v))
    img = cv2.cvtColor(final_hsv, cv2.COLOR_HSV2RGB)

    gr = cv2.getTrackbarPos("gray", "trackBar")
    if gr == 0:
        pass
    else:
        img = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)


    final = img
    #final = cv2.cvtColor(final, cv2.COLOR_RGB2GRAY)
    #cv2.putText(final, '640 x 480', (center_x, center_y), cv2.FONT_HERSHEY_PLAIN, 1, (255, 255, 255), 2)
    #cv2.imshow('final', final)



    img = Image.fromarray(final)

    imgtk = ImageTk.PhotoImage(image=img)
    lmain.imgtk = imgtk
    lmain.configure(image=imgtk)

    lmain.after(1, show_frame)
    return final


def screenshotcallback():
    global i
    #frame = show_frame()
    _, frame = cap.read()
    #resize = cv2.resize(frame, (640,480))
    cv2.imwrite('image/image_%d.jpg' % (i), frame)
    print('captured')
    print('"image_%d.jpg"' % (i), ' is saved -> /image/..')
    i += 1

def closecallback():
    root.destroy()
    print('closed')
    cap.release()
    cv2.destroyAllWindows()

Button(root, text="1. Video", command=show_frame).pack()
Button(root, text="2. screenshot", command=screenshotcallback).pack()
Button(root, text="3. Close", command=closecallback).pack()
root.mainloop()
cap.release()