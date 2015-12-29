#!/usr/bin/env python

import zmq
import time
context = zmq.Context()
 
publisher = context.socket (zmq.PUB)
publisher.bind ("tcp://127.0.0.1:8888")
 
i = 0
while True:
    message = str(i) + " hello world"
    print(message)
    publisher.send (message)
    i = 0 if ( i >= 10) else i + 1
    time.sleep(0.2)
