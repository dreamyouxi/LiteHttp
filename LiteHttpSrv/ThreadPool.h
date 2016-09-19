#ifndef __THREADPOOL____
#define  __THREADPOOL____

#include "queue"
#include <thread>
#include <condition_variable>
#include <mutex>


class HttpRequest;

#define  LOCK(WHAT)   std::unique_lock<std::mutex> locker(WHAT);

template<class T>
class QueueThreadSafe
{
public:
	void push(T &t)
	{
		LOCK(this->_mutex);
		this->_queue.push(t);
		_cond.notify_one();
	}
	T get()
	{
		LOCK(this->_mutex);
		T & ret = this->_queue.front();
		this->_queue.pop();
		return ret;
	}

	bool empty()
	{
		LOCK(this->_mutex);
		bool ret = this->_queue.empty();
		return ret;
	}
private:
	std::queue<T>  _queue;
	std::mutex _mutex;
	std::condition_variable_any _cond;


};





class ThreadPool
{
public:
	void addTask(HttpRequest*);
	static ThreadPool * getInstance();

private:
	std::queue<HttpRequest*> works;
	std::vector<std::thread*> workers;

	void WorkThread();

	ThreadPool();


	std::mutex _mutex;
	std::condition_variable_any _cond;

};






#endif