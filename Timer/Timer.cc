
 ///
 /// @file    Timer.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-08-23 16:18:30
 ///
 
#include "Timer.h"

#include <unistd.h>
#include <stdio.h>
#include <poll.h>
#include <errno.h>
#include <sys/timerfd.h>

using namespace wd;

Timer::Timer(int initTime, int intervalTime, TimerCallback && cb)
: _fd(createTimerFd())
, _initTime(initTime)
, _intervalTime(intervalTime)
, _cb(std::move(cb))
, _isStarted(false)
{}

void Timer::start()
{
	_isStarted = true;

	struct pollfd pfd;
	pfd.fd = _fd;
	pfd.events = POLLIN;

	setTimerfd(_initTime, _intervalTime);
	while(_isStarted) {
		int nready = ::poll(&pfd, 1, 5000);
		if(nready == -1 && errno == EINTR)
			continue;
		else if(nready == -1) 
			exit(EXIT_FAILURE);
		else if(nready == 0)
			printf(">>> poll timeout!\n");
		else {
			if(pfd.revents & POLLIN) 
			{
				handleRead();//如果不处理，事件会一直触发
				if(_cb) {
					_cb();
				}
			}
		}
	}
}

//stop跟start在不同的线程中执行
void Timer::stop()
{
	if(_isStarted) {
		_isStarted = false;
		setTimerfd(0, 0);//停止定时器
	}
}

int Timer::createTimerFd()
{
	int fd = ::timerfd_create(CLOCK_REALTIME, 0);
	if(fd == -1)
	{
		perror("timerfd_create error");
	}
	return fd;
}


void Timer::setTimerfd(int initTime, int intervalTime)
{
	struct itimerspec value;
	value.it_value.tv_sec = initTime;
	value.it_value.tv_nsec = 0;
	value.it_interval.tv_sec = intervalTime;
	value.it_interval.tv_nsec = 0;

	int ret = ::timerfd_settime(_fd, 0, &value, NULL);
	if(ret == -1)
	{
		perror(">> timerfd_settime error");
	}
}

void Timer::handleRead() 
{
	uint64_t howmany = 0;
	int ret = ::read(_fd, &howmany, sizeof(uint64_t));
	if(ret != sizeof(uint64_t)) {
		perror("read error");
	}
}
