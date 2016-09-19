
#include "ThreadPool.h"
#include "winsock.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include <fstream>
#include <iostream>
#include <string>
#include <atomic>
#include "Defs.h"
#include "Config.h"
#include "FileCache.h"
#include "HttpRequest.h"
#include "HttpRespone.h"
#include "ScriptCore.h"
#include "Utils.h"
using namespace std;










void SendThread(HttpRespone* rep)
{
	send(rep->sock, (const char*)rep->header, rep->header_size, 0);


	send(rep->sock, (const char*)rep->buffer, rep->size, 0);
	//	delete rep;

}

class ThreadCounterRAII
{
public:
	ThreadCounterRAII()
	{
		_count.fetch_add(1);
	}

	static atomic<int > _count;
	~ThreadCounterRAII()
	{
		_count.fetch_sub(1);
	}

};

atomic<int>  ThreadCounterRAII::_count = 0;





void SendErrorBuffer(int sock)
{

	HttpRespone *rep = new HttpRespone;
	rep->size = strlen(html404);
	rep->header = head_404;
	rep->sock = sock;
	rep->buffer = (unsigned char *)html404;
	rep->header_size = strlen(head_404);
	SendThread(rep);
	delete rep;
}

void ProcessRequestThread(HttpRequest*request, FileCache*cache)
{

	//	ThreadCounterRAII counter;

	//cout <<  ThreadCounterRAII:: _count/20.0*100 <<" %"<< endl;
	int  len, sock_client = request->sock;
	char  buff[4097];

	len = recv(sock_client, buff, 4095, 0);
	if (len == SOCKET_ERROR)
	{
		SendErrorBuffer(request->sock);
		closesocket(sock_client);

		return;
	}
	buff[4096] = '\0';
	buff[len] = '\0';

	std::string s = buff;
	std::string referer_orign = buff;//给GET请求分析参数


	//std::cout << __FUNCTION__<< " header "  <<s<< std::endl;
	if (!s.size())
	{
		SendErrorBuffer(request->sock);
		closesocket(sock_client);
		return;
	}
	//	LOG("%s ", s.c_str());

	s = s.substr(0, s.find("\n"));

	int i = s.find(" ", 0);


	std::string type = s.substr(0, i++);
	std::string req = s.substr(i, s.find(" ", i) - i);
	if (req == "/")
	{
		req = Config::DefaultIndexFile;
	}

	req = req.substr(1, -1);
	i = req.find("?v=");
	if (i != string::npos)
	{
		req = req.substr(0, i);
	}


	fstream file;
	file.open(req, ios::in);


	s = req;

	char *h = head_404;


	if (s.find(".css") != string::npos)
	{
		h = head_css;
	}
	if (s.find(".js") != string::npos)
	{
		h = head_js;
	}if (s.find(".html") != string::npos)
	{
		h = head;
	}
	if (s.find(".png") != string::npos)
	{
		h = head_png;
	}

	if (s.find(".jpg") != string::npos)
	{
		h = head_jpg;
	}
	if (s.find(".exe") != string::npos)
	{
		h = head_exe;
	}




	//do param with url
	if (s.find("?") != string::npos)
	{
		do{
			//if (referer_orign.find("Referer:") == string::npos)break;



			//	s = s.substr(referer_orign.find("Referer:"), -1);


			string url = s;

			int i = url.find("?");
			string service = url.substr(0, i);
			string params = url.substr(i + 1, -1);
		

			int count = 0;

			for (int i = 0; i < params.size(); i++)
			{

				if (params[i] == '%')
				{
					++count;
				}
				if (count >= 3)
				{
					//	if (referer_orign.find("MSIE") == string::npos || referer_orign.find("msie") == string::npos)
					params = Utils::decodeURL(params);//decode for utf-8
					break;
				}
			}


			string ret = ScriptCore::getInstance()->exec(service, params);




			HttpRespone *rep = new HttpRespone;
			rep->size = ret.size();
			rep->header = h;
			rep->sock = request->sock;
			rep->buffer = (unsigned char *)ret.c_str();
			rep->header_size = strlen(h);

			SendThread(rep);
			delete rep;

			closesocket(sock_client);
			return;


		} while (false);

	}





	//	LOG("%s",req.c_str());
	FileData *data = cache->getFileData(req);

	if (data)
	{


		HttpRespone *rep = new HttpRespone;
		rep->size = data->size;
		rep->header = h;
		rep->sock = request->sock;
		rep->buffer = data->buffer;
		rep->header_size = strlen(h);

		SendThread(rep);
		delete rep;


	}
	else
	{

		HttpRespone *rep = new HttpRespone;
		rep->size = strlen(html404);
		rep->header = h;
		rep->sock = request->sock;
		rep->buffer = (unsigned char *)html404;
		rep->header_size = strlen(h);

		SendThread(rep);
	}

	closesocket(sock_client);

}









ThreadPool * ThreadPool::getInstance()
{
	static ThreadPool * ins = nullptr;
	if (!ins)ins = new ThreadPool;
	return ins;
}



void ThreadPool::WorkThread()
{
	FileCache*cache = FileCache::create();

	while (true)
	{
		this->_mutex.lock();
		while (this->works.empty())
		{
			this->_cond.wait(this->_mutex);
		}
		HttpRequest * req = this->works.front();
		this->works.pop();
		this->_mutex.unlock();
		ProcessRequestThread(req, cache);
	}
	cache->release();
}



void  ThreadPool::addTask(HttpRequest*work)
{
	this->_mutex.lock();
	this->works.push(work);
	this->_mutex.unlock();

	this->_cond.notify_one();
}



ThreadPool::ThreadPool()
{
	int MAX_THREADS = std::thread::hardware_concurrency() * 50;

	LOG("%s max thread num : %d", __FUNCTION__, MAX_THREADS);

	while (MAX_THREADS--)
	{
		std::thread t(std::bind(&ThreadPool::WorkThread, this));

		t.detach();
	}


}