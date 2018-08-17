/*
Author: Sushil 
Email: robosushil@gmail.com
*/
#include "UDP_Node.h"


void socket_init(unsigned short port, const char *IP) {
	WSADATA data;
	WSAStartup(MAKEWORD(2, 0), &data);
	memset(&serverSockAddr, 0, sizeof(serverSockAddr));
	serverSockAddr.sin_addr.S_un.S_addr = inet_addr(IP);
	serverSockAddr.sin_port = htons(port);
	serverSockAddr.sin_family = AF_INET;
	Socket = socket(AF_INET, SOCK_DGRAM, 0);
}

vector<unsigned char> nodeDataToServer(int _W, int _H) {
	cap >> in_Img;
	cvtColor(in_Img, gray, CV_RGB2GRAY);
	resize(in_Img, outImg, cv::Size(_W, _H), 0, 0, CV_INTER_LINEAR);
	Cam_FPS = drawFPS(0, outImg);
	imencode(".jpg", outImg, temp, encodeBuf);
	return temp;
}

int main() {
	socket_init(Serverport, ServerIP);
	
	int _qlt = 20, _qlt_max = 200;
	int _H = 480, _H_Max = 2000;
	int _W = 640, _W_Max = 2000;
	namedWindow("Send2NodeImg", 1);
	createTrackbar("Quality", "Send2NodeImg", &_qlt, _qlt_max);
	createTrackbar("Reso_x", "Send2NodeImg", &_W, _W_Max);
	createTrackbar("Reso_y", "Send2NodeImg", &_H, _H_Max);
	for(;;)
	{
		encodeBuf[0] = CV_IMWRITE_JPEG_QUALITY;
		encodeBuf[1] = _qlt;

		NodeBuff = nodeDataToServer(_W,_H);
		
		if (NodeBuff.size() > nodeDataMax) {
			cout << "Please Reduce Data Size....."<< "DataSize->" << NodeBuff.size() << endl;
		}
		else{
			cout <<"Data Transmitting....."<< "DataSize->" << NodeBuff.size() << endl;
			for (int i = 0; i<NodeBuff.size(); i++)
			{
				buff[i] = NodeBuff[i];
			}

			int result=sendto(Socket, buff, nodeDataMax, 0, (LPSOCKADDR)&serverSockAddr, sizeof(serverSockAddr));
		
			TxImg = imdecode(Mat(NodeBuff), CV_LOAD_IMAGE_COLOR);
			Tx_FPS=drawFPS(1, TxImg);
			
			cv::imshow("Send2NodeImg", TxImg);
		}
		NodeBuff.clear();
		if (waitKey(1) == 27) break;
	}
	
	closesocket(Socket);
	WSACleanup();
}