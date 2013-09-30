#ifndef THREADSGUI_THREAD_H
#define THREADSGUI_THREAD_H

#include <QtCore/QThread>

class Thread : public QThread
{
Q_OBJECT

public:
	Thread(int id, QObject *parent = 0);

	int id() const;
	int duration() const;

signals:
	void progress(int percents);

private slots:
	void onTimer();

private:
	int m_id;
	int m_duration;
	int m_currentStep;

	void run();
	void reset();
};

#endif // THREADSGUI_THREAD_H
