#include "threadpool.h"
#include "thread.h"

#ifdef MEMORY_LEAKS_SEARCH
#ifdef _MSC_VER
#ifndef _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC
#endif
#include <crtdbg.h>
#endif
#if defined(_MSC_VER) && defined(_DEBUG)
#define new new(_NORMAL_BLOCK, THIS_FILE, __LINE__)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

ThreadPool *ThreadPool::m_pInstance = 0;

ThreadPool::ThreadPool(QObject *parent)
	: QObject(parent)
{
}

ThreadPool::~ThreadPool()
{
	blockSignals(true);
	stop();
	blockSignals(false);
}

ThreadPool *ThreadPool::instance()
{
	if (!m_pInstance) {
		m_pInstance = new ThreadPool();
	}

	return m_pInstance;
}

void ThreadPool::deleteInstance()
{
	delete instance();
}

void ThreadPool::start(int threadNumber)
{
	m_threads.resize(threadNumber);

	for (int i = 0; i < threadNumber; i++) {
		m_threads[i] = new Thread(i);

		connect(m_threads[i], SIGNAL(finished()),
				m_threads[i], SLOT(start()));

		m_threads[i]->start();

		emit threadStarted(m_threads[i]);
	}
}

void ThreadPool::stop()
{
	int count = m_threads.count();

	for (int i = 0; i < count; i++) {
		const int threadId = m_threads[i]->id();

		m_threads[i]->quit();
		m_threads[i]->wait();
		delete m_threads[i];

		emit threadDeleted(threadId);
	}

	m_threads.clear();
}
