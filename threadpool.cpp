#include "threadpool.h"
#include "thread.h"

ThreadPool *ThreadPool::m_pInstance = 0;

ThreadPool::ThreadPool(QObject *parent)
	: QObject(parent)
{
}

ThreadPool *ThreadPool::instance()
{
	if (!m_pInstance) {
		m_pInstance = new ThreadPool();
	}

	return m_pInstance;
}

void ThreadPool::start(int threadNumber)
{
	m_threads.resize(threadNumber);

	for (int i = 0; i < threadNumber; i++) {
		m_threads[i] = new Thread(i);
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
}
