/*
Author: Sushil 
Email: robosushil@gmail.com
*/
#include"UDP_Server.h"

void socket_init(unsigned short port) {
	WSADATA data;
	WSAStartup(MAKEWORD(2, 0), &data);
	memset(&serverSockAddr, 0, sizeof(serverSockAddr));
	serverSockAddr.sin_port = htons(port);
	serverSockAddr.sin_family = AF_INET;
	serverSockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
	bind(serverSocket, (LPSOCKADDR)&serverSockAddr, (int) sizeof(serverSockAddr));
}


int main() {
	socket_init(ServerPort);
	
	for (;;) {
		numrcv = recvfrom(serverSocket, buff, nodeDataSize, 0, (LPSOCKADDR)&nodeSockAddr, &nodeAddrSize);
		cout << nodeDataSize << endl;
		for (int i = 0; i<sizeof(buff); i++) {
			NodeBuff.push_back((uchar)buff[i]);
		}
		
		NodeImg = imdecode(Mat(NodeBuff), CV_LOAD_IMAGE_COLOR);
		
		imshow("ReceivedImage", NodeImg);
		if (waitKey(1) == 27) break;
		NodeBuff.clear();
	}
	NodeImg.release();
	closesocket(serverSocket);
	WSACleanup();
}
