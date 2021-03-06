 ///
 /// @file    Thread.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-08-20 09:47:14
 ///
 
#ifndef __WD_THREAD_H__
#define __WD_THREAD_H__

#include "Noncopyable.h"
#include <pthread.h>

#include <functional>

namespace wd
{

class Thread
: Noncopyable
{
public:
	using ThreadCallback = std::function<void()>;
    //构造函数传进来一个函数的引用
	Thread(ThreadCallback && cb);

	~Thread();

	void start();
	void join();

	pthread_t getThreadId() const {	return _pthid;	}

private:
	static void * threadFunc(void * arg);
private:
	pthread_t _pthid;
	ThreadCallback _cb;//子线程调用函数（做工作）
	bool _isRunning;
};

}//end of namespace wd


#endif
