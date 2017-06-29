#Based on code found on this Stack Overflow post:
#https://stackoverflow.com/questions/43817161/how-to-send-opencv-video-footage-over-zeromq-sockets

import cv2
import zmq
import base64
import numpy as np

context = zmq.Context()
footage_socket = context.socket(zmq.SUB)
address = 'tcp://localhost:20'
footage_socket.connect(address)
footage_socket.setsockopt_string(zmq.SUBSCRIBE, unicode(''))

print "start"
print "connecting to ", address

while True:
    try:
        frame = footage_socket.recv_string()
        img = base64.b64decode(frame)
        npimg = np.fromstring(img, dtype=np.uint8)
        source = cv2.imdecode(npimg, 1)
        cv2.imshow("image", source)
        cv2.waitKey(1)

    except KeyboardInterrupt:
        cv2.destroyAllWindows()
        print "\n\nBye bye\n"
        break
