 ///
 /// @file    TestEventfd.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-08-23 11:39:56
 ///
 
#include "Thread.h"
#include "Eventfd.h"

#include <unistd.h>
#include <time.h>
#include <stdlib.h>


#include <iostream>
#include <functional>
using std::cout;
using std::endl;

void getNumber()
{
	::srand(::time(NULL));
	int number = ::rand() % 100;
	cout << ">>> subthread " << pthread_self() << "  get number " << number << endl;
}
 
int main(void)
{
	cout << "mainthread " << pthread_self() << endl;
    //创建Eventfd对象，传递一个任务给它
	wd::Eventfd event(getNumber);
    //将任务通过bind()函数绑定到thread对象上
	wd::Thread thread(std::bind(&wd::Eventfd::start, &event));//绑定
	thread.start();

	int cnt = 10;
	while(cnt--) 
	{
		event.wakeup();
		::sleep(1);
	}

	thread.join();

	return 0;
}
