#ifndef THREADSGUI_MAINWINDOW_H
#define THREADSGUI_MAINWINDOW_H

#if QT_VERSION >= 0x050000
#include <QtWidgets/QMainWindow>
#else
#include <QtGui/QMainWindow>
#endif

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

	void connect();
};

#endif // THREADSGUI_MAINWINDOW_H
