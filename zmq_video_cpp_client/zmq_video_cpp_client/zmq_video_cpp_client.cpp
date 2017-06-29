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
	zmq::socket_t socket(context, ZMQ_SUB);
	socket.connect("tcp://localhost:20");


	std::cout << "Client Up and Receiving\n";

	while (true)
	{
		zmq::message_t msg;
		socket.recv(&msg);
		std::string msgStr(static_cast<char *>(msg.data()), msg.size());
		std::string decoded = base64_decode(msgStr);
		std::vector<char> v(decoded.begin(), decoded.end());
		cv::Mat img = cv::imdecode(cv::Mat(v),1);
		cv::imshow("Image",img);

		int key = cv::waitKey(1);
		if (key >= 0)
		{
			switch (key)
			{
			case 27:
			case 'q':
			case 'Q':
				break;
			default:
				break;
			}
		}
	}
	socket.close();
	context.close();
  return 0;
}
