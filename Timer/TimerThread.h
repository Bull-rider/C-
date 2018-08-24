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
	: _timer(initTime, intervalTime, std::move(cb))//��һ��Timer�����ʼ��
	, _thread(std::bind(&Timer::start, &_timer))//��һ��Thread�����ʼ��
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
//ThreadTimer����������࣬һ���߳�Thread���һ����ʱ��Timer��
private:
	Timer _timer;
	Thread _thread;
};

}//end of namespace wd

