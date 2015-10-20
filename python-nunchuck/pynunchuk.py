import serial
import sys
import pyxhook
import time


running = True

def kbevent( event ): 
    #If the ascii value matches escape key, terminate the while loop    
    if event.Ascii == 0:
        global running
        running = False
    

hookman = pyxhook.HookManager()    
hookman.KeyDown = kbevent    
hookman.HookKeyboard()    
hookman.start()

try:
    ser = serial.Serial("/dev/ttyACM0", 19200, timeout=1)  
    print ser.name          
    #ser.write("hello")      # write a string
except:
    print "Serial Not Found"
    sys.exit(0)

while running == True:
    time.sleep(0.1)
    line = ser.readline()
    line_array = line.split(",")
    line_array = line_array[:-1]
    print line      
    
    
ser.close()
hookman.cancel()
sys.exit(0)
