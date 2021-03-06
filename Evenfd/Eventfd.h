 ///
 /// @file    Eventfd.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-08-23 11:23:14
 ///
 
#ifndef __WD_EVNETFD_H__
#define __WD_EVNETFD_H__
#include <functional>

namespace wd
{

class Eventfd
{
using Callback = std::function<void()>;
public:
	Eventfd(Callback &&);

	void start();// 监听文件描述符_fd

	void wakeup();//唤醒

private:
	void handleRead();
	
	int createEventfd();
	
private:
	int _fd;
	Callback _cb;
	bool _isStarted;
};

}//end of namespace wd

#endif
