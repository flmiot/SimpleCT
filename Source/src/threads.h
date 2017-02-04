/*
 Copyright 2016 Florian Otte
 
 This file is part of Mneme v0.1 (Mayflower).
 Filename: threads.h
 */
#ifndef THREADS_H_
#define THREADS_H_

#include <wx/thread.h>

class CustomThreadClass {
public:
	CustomThreadClass();
	virtual ~CustomThreadClass();

protected:

	class WorkerThread: public wxThread {
	public:
		WorkerThread(CustomThreadClass* Handler);
		~WorkerThread();

	protected:
		CustomThreadClass* _handler;
		virtual wxThread::ExitCode Entry();

	};

	virtual wxThread::ExitCode Task() = 0;
	virtual void OnThread_DestructorCall() = 0;

	int StartTask();
	int StopTask();
	int PauseTask();
	int ResumeTask();

	WorkerThread* _pWorkerThread;
	wxCriticalSection _pWorkerThreadCS;


};


#endif /* THREADS_H_ */
