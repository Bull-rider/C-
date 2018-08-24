 ///
 /// @file    Timer.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-08-23 16:15:42
 ///
 
#ifndef __WD_TIMER_H__
#define __WD_TIMER_H__

#include <functional>

namespace wd
{

class Timer
{
public:
	using TimerCallback = std::function<void()>;

	Timer(int, int, TimerCallback && cb);

	void start();
	void stop();

private:
	void handleRead();

	int createTimerFd();
	void setTimerfd(int initTime, int intervalTime);
	
private:
	int _fd;
	int _initTime;
	int _intervalTime;
	TimerCallback _cb;//回调函数调用线程
	bool _isStarted;
};

}//end of namespace wd

#endif
