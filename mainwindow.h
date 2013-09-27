#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>

class ProgressWidget;

class Thread;

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void onStart();
	void onThreadStarted(const Thread *thread);
	void onThreadDeleted(int threadId);

private:
	Ui::MainWindow *ui;
	QVector<ProgressWidget *> m_widgets;
	bool m_startEnabled;

	void init();
	void connect();
};

#endif // MAINWINDOW_H
