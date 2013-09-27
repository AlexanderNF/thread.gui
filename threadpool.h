#include <QtCore/QObject>
#include <QtCore/QVector>

class Thread;

class ThreadPool : public QObject
{
	Q_OBJECT

public:
	ThreadPool(QObject *parent = 0);

	static ThreadPool *instance();

	void start(int threadNumber);
	void stop();

signals:
	void threadStarted(const Thread *thread);
	void threadDeleted(int id);

private:
	QVector<Thread *> m_threads;
	static ThreadPool *m_pInstance;
};

#define threadPool ThreadPool::instance()
