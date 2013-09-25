import RPi.GPIO as gpio
import time

#Motor 1 GPIO Pin
IC1A = 27
IC2A = 22

#Motor 2 GPIO Pin
IC3A = 4
IC4A = 17

gpio.cleanup()

gpio.setmode(gpio.BCM)

#Pin Output Setup
gpio.setup(IC1A, gpio.OUT)
gpio.setup(IC2A, gpio.OUT)
gpio.setup(IC3A, gpio.OUT)
gpio.setup(IC4A, gpio.OUT)

#Pin Initialization

gpio.output(IC1A, gpio.LOW)
gpio.output(IC2A, gpio.LOW)
gpio.output(IC3A, gpio.LOW)
gpio.output(IC4A, gpio.LOW)

# RC BACK 
for i in range(100):
    gpio.output(IC1A, gpio.HIGH)
    time.sleep(0.01)

gpio.output(IC1A, gpio.LOW)

# RC FORWORD
for i in range(100):
    gpio.output(IC2A, gpio.HIGH)
    time.sleep(0.01)

gpio.output(IC2A, gpio.LOW)

# LEFT 
for i in range(100):
    gpio.output(IC3A, gpio.HIGH)
    time.sleep(0.01)

gpio.output(IC3A, gpio.LOW)

# RIGHT
for i in range(100):
    gpio.output(IC4A, gpio.HIGH)
    time.sleep(0.01)

gpio.output(IC4A, gpio.LOW)

gpio.cleanup()
