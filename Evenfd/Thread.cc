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
//�����߳�
void Thread::start()
{
	pthread_create(&_pthid, NULL, threadFunc, this);
	_isRunning = true;
}
//�̺߳���
void * Thread::threadFunc(void * arg)
{
	Thread * pthread = static_cast<Thread *>(arg);//ǿ��ת��
	if(pthread)
		pthread->_cb();//�̺߳����е���_cb()����ִ������

	return NULL;
}
//�ȴ��������߳���Դ
void Thread::join() 
{
	if(_isRunning) {
		pthread_join(_pthid, NULL);
		_isRunning = false;
	}
}
//��������
Thread::~Thread()
{
	if(_isRunning) {
		pthread_detach(_pthid);
		_isRunning = false;
	}
}

}//end of namespace wd

