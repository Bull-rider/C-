 ///
 /// @file    Thread.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-08-20 09:50:11
 ///
 
#include "Thread.h"

namespace wd
{

Thread::Thread(ThreadCallback && cb)
: _pthid(0)
, _cb(std::move(cb))
{}
//创建线程
void Thread::start()
{
	pthread_create(&_pthid, NULL, threadFunc, this);
	_isRunning = true;
}
//线程函数
void * Thread::threadFunc(void * arg)
{
	Thread * pthread = static_cast<Thread *>(arg);//强制转换
	if(pthread)
		pthread->_cb();//线程函数中调用_cb()函数执行任务

	return NULL;
}
//等待回收子线程资源
void Thread::join() 
{
	if(_isRunning) {
		pthread_join(_pthid, NULL);
		_isRunning = false;
	}
}
//析构函数
Thread::~Thread()
{
	if(_isRunning) {
		pthread_detach(_pthid);
		_isRunning = false;
	}
}

}//end of namespace wd

