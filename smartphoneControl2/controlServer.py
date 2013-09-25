import cgi 
import RPi.GPIO as gpio 
from BaseHTTPServer import HTTPServer
from SimpleHTTPServer import SimpleHTTPRequestHandler

#Motor 1 GPIO Pin
IC1A = 4
IC2A = 17

#Motor 2 GPIO Pin
IC3A = 27
IC4A = 22

class Handler(SimpleHTTPRequestHandler):
    def do_POST(self):
        if self.path == '/rccar':
            form = cgi.FieldStorage(fp=self.rfile, 
                                    headers=self.headers,
                                    environ={'REQUEST_METHOD':'POST'})
            cmd = form['cmd'].value
            print cmd

            if cmd == "GO":
                gpio.output(IC3A, gpio.LOW)
                gpio.output(IC4A, gpio.HIGH)
            elif cmd == "LEFT":
                gpio.output(IC1A, gpio.HIGH)
                gpio.output(IC2A, gpio.LOW)
            elif cmd == "STOP":
                gpio.output(IC1A, gpio.LOW)
                gpio.output(IC2A, gpio.LOW)
                gpio.output(IC3A, gpio.LOW)
                gpio.output(IC4A, gpio.LOW)
            elif cmd == "RIGHT":
                gpio.output(IC1A, gpio.LOW)
                gpio.output(IC2A, gpio.HIGH)
            elif cmd == "BACK":
                gpio.output(IC3A, gpio.HIGH)
                gpio.output(IC4A, gpio.LOW)

            self.send_response(100)
            self.send_header('Content-type', 'text/html')

            return

        return self.do_GET() 

gpio.setwarnings(False)
gpio.setmode( gpio.BCM ) 

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


server = HTTPServer(('', 8002), Handler).serve_forever()
