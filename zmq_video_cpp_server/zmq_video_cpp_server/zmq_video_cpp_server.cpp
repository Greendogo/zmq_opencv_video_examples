#include "stdafx.h"
#include "zmq.hpp"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <string>
#include <base64.h>
#include <vector>

int main()
{
	zmq::context_t context(1);
	zmq::socket_t socket(context, ZMQ_PUB);
	socket.bind("tcp://*:20");
	socket.setsockopt(ZMQ_SUBSCRIBE, "", 0);
	socket.setsockopt(ZMQ_CONFLATE, 1);
	cv::VideoCapture camera(0);

	std::cout << "Server Up and Sending\n";


	while (true)
	{
		cv::Mat img;
		camera.read(img);
		std::vector<uchar> buffer;
		cv::imencode(".png", img, buffer);
		std::string encoded(buffer.begin(), buffer.end());
		std::string encodedB64(base64_encode(encoded));
		zmq::message_t msg(encodedB64.data(), encodedB64.size());
		socket.send(msg);
	}
	return 0;
}
