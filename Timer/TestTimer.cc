 ///
 /// @file    TestTimer.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-08-23 16:34:57
 ///
 
#include "TimerThread.h"

#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <functional>
using std::cout;
using std::endl;


struct Task
{
	void process() 
	{
		::srand(::time(NULL));
		int number = ::rand() % 100;
		cout << ">> number = " << number << endl;
	}
};


int main(void)
{
	Task task;
	wd::TimerThread timer(3, 6, std::bind(&Task::process, &task));
	timer.start();//在子线程中运行定时器
	::sleep(20);
	timer.stop();
	return 0;
}
//我们整体看这个程序：首先我们把线程Thread和时钟设置Timer看作两个类，分别进行类的定义和初始化。
//然后创建另一个类TimerThread专门对这两个类进行操作。通过给一个TimerThread类型的对象传递参数
//实现对Timer和Thread这两个类对象的调用。

//---------其实面向对象编程就是找出对象之间的关系，通过参数之间的传递实现功能的------\\

