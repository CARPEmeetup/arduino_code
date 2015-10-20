"""
A simple example of hooking the keyboard on Linux using pyxhook

Any key pressed prints out the keys values, program terminates when spacebar is pressed
"""

#Libraries we need
import pyxhook
import time

 

    

def kbevent( event ):    
    print event    
    #If the ascii value matches escape key, terminate the while loop
    if event.Ascii == 0:
        print 'True'
    else: return False
        

hookman = pyxhook.HookManager()    
hookman.KeyDown = kbevent    
hookman.HookKeyboard()    
hookman.start()

running = True
while running:
    time.sleep(0.1)
hookman.cancel()
