import RPi.GPIO as GPIO
import time
import os

GPIO.setmode(GPIO.BCM)
GPIO.setup(7, GPIO.IN)
GPIO.setup(8, GPIO.IN)

while True:
  if(GPIO.input(7)):
    os.system("sudo shutdown -r now")
    break
  elif(GPIO.input(8)):
    os.system("sudo shutdown -h now")
    break
  else:
    time.sleep(1)
