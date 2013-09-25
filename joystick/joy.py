import uinput
import time
import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BCM)

GPIO.setup(17, GPIO.IN)
GPIO.setup(27, GPIO.IN)
GPIO.setup(22, GPIO.IN)
GPIO.setup(23, GPIO.IN)
GPIO.setup(4, GPIO.IN)
GPIO.setup(10, GPIO.IN)
GPIO.setup(9, GPIO.IN)
GPIO.setup(11, GPIO.IN)

events = (uinput.BTN_A, uinput.BTN_B, uinput.BTN_C, uinput.BTN_X, uinput.ABS_X + (0, 255, 0, 0), uinput.ABS_Y + (0, 255, 0, 0))

device = uinput.Device(events)

A = False
B = False
C = False
D = False
up = False
down = False
left = False
right = False

device.emit(uinput.ABS_X, 128, syn=False)
device.emit(uinput.ABS_Y, 128)

while True:
if (not A) and (not GPIO.input(4)): # A button pressed  
	A = True
	device.emit(uinput.BTN_A, 1)  
if A and GPIO.input(4): # A button released  
	A = False
	device.emit(uinput.BTN_A, 0) 
if (not B) and (not GPIO.input(10)): # B button pressed  
	B = True
	device.emit(uinput.BTN_B, 1)  
if B and GPIO.input(10): # B button released  
	B = False
	device.emit(uinput.BTN_B, 0) 
if (not C) and (not GPIO.input(9)): # C button pressed  
	C = True
	device.emit(uinput.BTN_C, 1)  
if C and GPIO.input(9): # C button released  
	C = False
	device.emit(uinput.BTN_C, 0) 
if (not D) and (not GPIO.input(11)): # D button pressed  
	D = True
	device.emit(uinput.BTN_D, 1)  
if D and GPIO.input(11): # D button released  
	D = False
	device.emit(uinput.BTN_D, 0) 
if (not up) and (not GPIO.input(17)): # Up button pressed
 up = True
 device.emit(uinput.ABS_Y, 0) # Zero Y
if up and GPIO.input(17): # Up button released
 up = False
 device.emit(uinput.ABS_Y, 128) # Center Y
if (not down) and (not GPIO.input(27)): # Down button pressed
 down = True
 device.emit(uinput.ABS_Y, 255) # Max Y
if down and GPIO.input(27): # Down button released
 down = False
 device.emit(uinput.ABS_Y, 128) # Center Y
if (not left) and (not GPIO.input(22)): # Left button pressed
 left = True
 device.emit(uinput.ABS_X, 0) # Zero X
if left and GPIO.input(22): # Left button released
 left = False
 device.emit(uinput.ABS_X, 128) # Center X
if (not right) and (not GPIO.input(23)):# Right button pressed
 right = True
 device.emit(uinput.ABS_X, 255) # Max X
if right and GPIO.input(23): # Right button released
 right = False
 device.emit(uinput.ABS_X, 128) # Center X
time.sleep(.02) # Poll every 20ms
