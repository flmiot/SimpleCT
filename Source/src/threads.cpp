#include "threads.h"

#include <stdexcept>

CustomThreadClass::CustomThreadClass() :
		_pWorkerThread(NULL) {};

CustomThreadClass::~CustomThreadClass() {
}


int CustomThreadClass::StartTask() {
	if( _pWorkerThread != NULL ) return 1;

	_pWorkerThread = new WorkerThread(this);
	wxThreadError err = _pWorkerThread->Create();

	if (err != wxTHREAD_NO_ERROR) {
		delete (_pWorkerThread);
		_pWorkerThread = NULL;
		return 1;
	}

	err = _pWorkerThread->Run();

	if (err != wxTHREAD_NO_ERROR) {
		delete (_pWorkerThread);
		_pWorkerThread = NULL;
		return 1;
	}
	return 0;
}


int CustomThreadClass::StopTask() {
	int err;
	if(_pWorkerThread != NULL) err = _pWorkerThread->Delete();
	if(err == wxTHREAD_NO_ERROR ) return 0;
	else return 1;
}

CustomThreadClass::WorkerThread::WorkerThread(CustomThreadClass* Handler) : _handler(Handler) {
}

CustomThreadClass::WorkerThread::~WorkerThread() {
	wxCriticalSectionLocker enter2(_handler->_pWorkerThreadCS);
	_handler->OnThread_DestructorCall();
	_handler->_pWorkerThread = NULL;

}

wxThread::ExitCode CustomThreadClass::WorkerThread::Entry(){
	return (ExitCode) _handler->Task();
}

int CustomThreadClass::PauseTask() {
	wxCriticalSectionLocker enter(_pWorkerThreadCS);
	if (_pWorkerThread) {
		if (_pWorkerThread->Pause() == wxTHREAD_NO_ERROR)
			return 0;
		else
			return 1;
	} else
		return 1;
}

int CustomThreadClass::ResumeTask() {
	wxCriticalSectionLocker enter(_pWorkerThreadCS);
	if (_pWorkerThread) {
		if (_pWorkerThread->Resume() == wxTHREAD_NO_ERROR)
			return 0;
		else
			return 1;
	} else
		return 1;
}
