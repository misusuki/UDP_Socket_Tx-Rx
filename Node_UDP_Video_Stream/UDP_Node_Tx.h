/*
Author: Sushil 
Email: robosushil@gmail.com
*/
#define _CRT_SECURE_NO_DEPRECATE
#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <fstream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include "opencv2/opencv.hpp"
#include <opencv2/world.hpp>

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "opencv_world320.lib")
using namespace std;
using namespace cv;

int Socket;
struct sockaddr_in serverSockAddr;
unsigned short Serverport = 1234;
const char *ServerIP = "192.168.1.6";

VideoCapture cap(0); // open the default camera
Mat in_Img;
Mat gray;
Mat outImg;
Mat TxImg;
Mat NodeImg;
static const int nodeDataMax = 65500;
char buff[nodeDataMax];
vector<unsigned char> NodeBuff;
vector<unsigned char> temp;
vector<int> encodeBuf = vector<int>(2);



//---------------------------Draw FPS on IMG---------------------------//
float Tx_FPS, Cam_FPS;
static float drawFPS(int id, Mat img)
{
	ostringstream oss;
	static int counter[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	static clock_t t[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	static float RFPS[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	if (counter[id] > 30)// Add fps figure (every 30 frames)
	{
		RFPS[id] = (30.0f / (clock() - t[id]) * CLOCKS_PER_SEC);
		t[id] = clock();
		counter[id] = 0;
	}

	// Increment counter
	++counter[id];


	oss.str(""); oss << "FPS=" << RFPS[id];
	putText(img, oss.str(), Point(5, 30), FONT_HERSHEY_SIMPLEX, 0.4, Scalar(0, 0, 255));
	return  RFPS[id];
}
//---------------------------Draw FPS on IMG---------------------------//