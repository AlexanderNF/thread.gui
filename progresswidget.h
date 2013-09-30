#ifndef THREADSGUI_PROGRESSWIDGET_H
#define THREADSGUI_PROGRESSWIDGET_H

#if QT_VERSION >= 0x050000
#include <QtWidgets/QWidget>
#else
#include <QtGui/QWidget>
#endif

class Thread;

namespace Ui {
	class ProgressWidget;
}

class ProgressWidget : public QWidget
{
	Q_OBJECT

public:
	explicit ProgressWidget(const Thread *thread, QWidget *parent = 0);
	~ProgressWidget();

public slots:
	void setProgress(int percents);

private:
	Ui::ProgressWidget *ui;
	const Thread *m_pThread;

	void init();
};

#endif // THREADSGUI_PROGRESSWIDGET_H
