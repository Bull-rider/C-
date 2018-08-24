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
    //����Eventfd���󣬴���һ���������
	wd::Eventfd event(getNumber);
    //������ͨ��bind()�����󶨵�thread������
	wd::Thread thread(std::bind(&wd::Eventfd::start, &event));//��
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
