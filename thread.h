#ifndef GUITHREADS_THREAD_H
#define GUITHREADS_THREAD_H

#include <QtCore/QThread>

class Thread : public QThread
{
Q_OBJECT

public:
	Thread(int id, QObject *parent = 0);

	int id() const;
signals:
	void progress(int percents);
	void durationInited(int duration);

private slots:
	void onTimer();

private:
	int m_id;
	int m_duration;
	int m_currentStep;

	void run();
};

#endif // GUITHREADS_THREAD_H
