#!/usr/bin/python
import io
import picamera
import datetime
import MySQLdb as mdb
import sys
import serial
from PIL import Image
import os
import time
import subprocess
from cStringIO import StringIO
id_card = []
mylist = []
param1 = "/dev/ttyUSB0"
param2 = "9600"
ard = serial.Serial(param1, param2, timeout=.1)
a=55
stream = io.BytesIO()
import subprocess
from cStringIO import StringIO
id_card = []
mylist = []
param1 = "/dev/ttyUSB0"
param2 = "9600"
ard = serial.Serial(param1, param2, timeout=.1)
a=55
stream = io.BytesIO()
while (a>1):
        a=a-1
        ard.flushInput()
        ard.flushOutput()
        id_card = (ard.readline()).split(",")
        if (id_card[0]<>''):
                print id_card[0]
                today = time.strftime("%Y-%m-%d %H:%M:%S")
                db = mdb.connect("localhost","root","Paulinka94","doch_sys")
                cursor = db.cursor()
        a=a-1
        ard.flushInput()
        ard.flushOutput()
        id_card = (ard.readline()).split(",")
        if (id_card[0]<>''):
                print id_card[0]
                today = time.strftime("%Y-%m-%d %H:%M:%S")
                db = mdb.connect("localhost","root","Paulinka94","doch_sys")
                cursor = db.cursor()
                sql = "INSERT INTO rfid_vchod(id_card,time_date) VALUES('"
                sql = sql+id_card[0]+"',"
                sql = sql+"'"+today
                sql = sql+"')"
                print sql
                cursor.execute(sql)
                db.commit()
                db.rollback()
                db.close()
                ard.write("OK\n")
                sql = sql+id_card[0]+"',"
                sql = sql+"'"+today
                sql = sql+"')"
                print sql
                cursor.execute(sql)
                db.commit()
                db.rollback()
                db.close()
                ard.write("OK\n")
                today = time.strftime("%Y-%m-%d %H:%M:%S")
                with picamera.PiCamera() as camera:
                        camera.resolution = (1600, 1200)
                        camera.rotation = 90
                        camera.annotate_text = today
                        camera.capture('image'+str(today)+'.jpeg')
        else:
                time.sleep(1);
