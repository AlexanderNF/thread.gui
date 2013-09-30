#include "thread.h"

#include <QtCore/QDateTime>
#include <QtCore/QTimer>

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

Thread::Thread(int id, QObject *parent)
	: QThread(parent), m_duration(0), m_currentStep(0)
{
	m_id = id;
}

int Thread::id() const
{
	return m_id;
}

int Thread::duration() const
{
	return m_duration;
}

void Thread::onTimer()
{
	if (m_currentStep == m_duration) {
		emit progress(100);

		quit();
	} else {
		emit progress(100 * m_currentStep / m_duration);

		m_currentStep++;
	}
}

void Thread::run()
{
	reset();

	qsrand(QDateTime::currentMSecsSinceEpoch() / 1000 * (m_id + 1) + m_id);
	m_duration = qrand() % 99 + 1;

	QTimer timer;
	timer.setInterval(1000);

	connect(&timer, SIGNAL(timeout()),
			SLOT(onTimer()),
			Qt::DirectConnection);

	timer.start();

	exec();

	timer.stop();
}

void Thread::reset()
{
	m_duration = 0;
	m_currentStep = 0;
}
