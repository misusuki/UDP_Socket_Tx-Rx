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
#pragma comment(lib, "wsock32.lib")
#pragma comment(lib, "opencv_world320.lib")
using namespace std;
using namespace cv;

unsigned short ServerPort = 1234;


struct sockaddr_in nodeSockAddr;
struct sockaddr_in serverSockAddr;
int nodeAddrSize = sizeof(nodeSockAddr);
bool st= false, status;
int numrcv;
int serverSocket;
const char *IP;

//VideoCapture cap(0); // open the default camera
Mat in_Img;
Mat gray;
Mat outImg;
Mat jpgimg;
Mat NodeImg;
static const int nodeDataSize = 65507;
char buff[nodeDataSize];
vector<uchar> NodeBuff;
vector<unsigned char> temp;
vector<int> decodeBuf = vector<int>(2);
