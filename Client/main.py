#!/usr/bin/env python3  
#coding=utf-8  

import json,sys,os
import paho.mqtt.client as mqtt
import time,random
from tkinter import *

fan_flag = False

def btn_callback():
    global lable
    global btn
    global fan_flag
    if fan_flag == False:
        fan_flag = True
        btn.config(text="关闭风扇")
        lable.config(text="风扇已经打开")
        publish_mqtt("/topic/fan","on","116.62.27.32")
    else:
        fan_flag = False
        btn.config(text="打开风扇")
        lable.config(text="风扇已经关闭")
        publish_mqtt("/topic/fan","off","116.62.27.32")

def publish_mqtt(topic,message,host):
    client_id = str(random.randint(0,100000))
    print(client_id)
    client = mqtt.Client(client_id, transport='tcp')
    client.connect(host, 1883, 1)
    client.loop_start()
    client.publish(topic,message)
    print("Successful send message!")

if __name__ == '__main__':
    global lable
    global window
    global btn
    sys.path.append(os.path.abspath(os.path.dirname(__file__) + '/' + '..'))
    sys.path.append("..")
    window = Tk()
    sw = window.winfo_screenwidth()
    sh = window.winfo_screenheight()
    ww = 250
    wh = 100
    x = (sw-ww) / 2
    y = (sh-wh) / 2
    window.title("客户端")
    window.resizable(0, 0)
    window.geometry("%dx%d+%d+%d" %(ww,wh,x,y))
    lable = Label(window, text='你好，这是智能风扇的客户端',
                font=('Arial', 10), width=30, height=2)
    btn = Button(window, text="打开风扇", font=('Arial', 20),
                 width=10, height=1, command=btn_callback)
    lable.pack()
    btn.place(x=40, y=40)
    window.mainloop()
