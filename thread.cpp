#include "thread.h"

#include <QtCore/QDateTime>
#include <QtCore/QTimer>

Thread::Thread(int id, QObject *parent)
	: QThread(parent), m_duration(0), m_currentStep(0)
{
	m_id = id;
}

int Thread::id() const
{
	return m_id;
}

void Thread::onTimer()
{
	if (m_currentStep == m_duration) {
		quit();
	} else {
		emit progress(100 * m_currentStep / m_duration);

		m_currentStep++;
	}
}

void Thread::run()
{
	qsrand(QDateTime::currentMSecsSinceEpoch() / 1000 * m_id + m_id);
	m_duration = qrand() % 50;

	emit durationInited(m_duration);

	QTimer timer;
	timer.setInterval(1000);

	connect(&timer, SIGNAL(timeout()), SLOT(onTimer()));

	timer.start();

	exec();
}
