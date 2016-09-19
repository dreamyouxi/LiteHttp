

#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include <vector>
#include <thread>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <atomic>

#include "winsock.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#pragma comment (lib,"wsock32")
#include "ThreadPool.h"
#include "Defs.h"
#include "Config.h"
#include "FileCache.h"
#include "HttpRequest.h"
#include "Application.h"
#include "ScriptCore.h"
using namespace std;




Application::Application()
{
	this->init();
}

bool  Application::init()
{

	FileCache::getInstance();
	ThreadPool::getInstance();
	ScriptCore::getInstance();


	return true;
}

void Application::startup()
{

	WSADATA wsadata;
	WORD wVersion = MAKEWORD(2, 0);
	WSAStartup(wVersion, &wsadata);



	int sock, length;
	length = sizeof(sockaddr);


	struct sockaddr_in server_ipaddr, client_ipaddr;
	memset(&server_ipaddr, 0, length);
	server_ipaddr.sin_family = AF_INET;
	server_ipaddr.sin_port = htons(80);

	server_ipaddr.sin_addr.s_addr = inet_addr(Config::SRV_HOST);


	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	::bind(sock, (sockaddr *)&server_ipaddr, length);


	listen(sock, Config::MAX_CONNECTION_COUNT);


	LOG("start http server ok");

	LOG("Accept Http Request at %s:%d", Config::SRV_HOST, Config::SRV_PORT);


	while (true)
	{

		int sock_client = accept(sock, (sockaddr *)&client_ipaddr, &length);
		if (sock_client == SOCKET_ERROR)
		{
			return;
		}
		HttpRequest*req = new HttpRequest;
		req->sock = sock_client;
		ThreadPool::getInstance()->addTask(req);
	}









}


