#Based on code found on this Stack Overflow post:
#https://stackoverflow.com/questions/43817161/how-to-send-opencv-video-footage-over-zeromq-sockets

import cv2
import zmq
import base64

context = zmq.Context()
footage_socket = context.socket(zmq.PUB)
footage_socket.bind('tcp://*:20')
footage_socket.setsockopt(zmq.CONFLATE, 1)

camera = cv2.VideoCapture(0)

while True:
    try:
        (grabbed, frame) = camera.read()
        frame = cv2.resize(frame, (640, 480))
        encoded, buffer = cv2.imencode('.png', frame)
        footage_socket.send_string(base64.b64encode(buffer))


    except KeyboardInterrupt:
        camera.release()
        cv2.destroyAllWindows()
        print "\n\nBye bye\n"
        break
