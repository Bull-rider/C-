 ///
 /// @file    TimerThread.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-08-23 16:47:10
 ///
 
#include "Timer.h"
#include "Thread.h"
#include <functional>

namespace wd
{

class TimerThread
{
public:
	using TimerCallback = std::function<void()>;
	TimerThread(int initTime, int intervalTime, TimerCallback && cb)
	: _timer(initTime, intervalTime, std::move(cb))//给一个Timer对象初始化
	, _thread(std::bind(&Timer::start, &_timer))//给一个Thread对象初始化
	{
	}

	void start() 
	{
		_thread.start();
	}

	void stop()
	{
		_timer.stop();
		_thread.join();
	}
//ThreadTimer类接收两个类，一个线程Thread类和一个定时器Timer类
private:
	Timer _timer;
	Thread _thread;
};

}//end of namespace wd

