import webiopi

webiopi.setDebug()

GPIO = webiopi.GPIO

LED=25
SERVO_TILT=23
SERVO_PAN=24

def setup():
    webiopi.debug("Script with macros - Setup")
    GPIO.setFunction(LED, GPIO.OUT)
    GPIO.setFunction(SERVO_TILT, GPIO.PWM)
    GPIO.setFunction(SERVO_PAN, GPIO.PWM)
    GPIO.output(LED, GPIO.LOW)

def loop():
    webiopi.sleep(1)

def destroy():
    webiopi.debug("Script with macros - Destroy")
    GPIO.setFunction(LED, GPIO.IN)
    GPIO.setFunction(SERVO_TILT, GPIO.IN)
    GPIO.setFunction(SERVO_PAN, GPIO.IN)

@webiopi.macro
def led_on():
    GPIO.output(LED, GPIO.HIGH)

@webiopi.macro
def led_off():
    GPIO.output(LED, GPIO.LOW)
  
