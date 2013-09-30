#include "mainwindow.h"
#include "progresswidget.h"
#include "thread.h"
#include "threadpool.h"
#include "ui_mainwindow.h"

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

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow), m_startEnabled(true)
{
	ui->setupUi(this);

	connect();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::onStart()
{
	if (m_startEnabled) {
		threadPool->start(ui->spinBox->value());

		ui->spinBox->setEnabled(false);
		ui->pushButton->setText(tr("Stop"));
		m_startEnabled = false;
	} else {
		threadPool->stop();

		ui->spinBox->setEnabled(true);
		ui->pushButton->setText(tr("Start"));
		m_startEnabled = true;
	}
}

void MainWindow::onThreadStarted(const Thread *thread)
{
	const int threadId = thread->id();

	if (m_widgets.size() <= threadId) {
		m_widgets.resize(threadId + 1);
	}

	m_widgets[threadId] = new ProgressWidget(thread);
	ui->horizontalLayout->insertWidget(threadId, m_widgets[threadId]);

	QObject::connect(thread, SIGNAL(progress(int)),
					 m_widgets[threadId], SLOT(setProgress(int)),
					 Qt::QueuedConnection);
}

void MainWindow::onThreadDeleted(int threadId)
{
	if (m_widgets[threadId]) {
		ProgressWidget *widget = dynamic_cast<ProgressWidget *>(ui->horizontalLayout->itemAt(threadId));
		ui->horizontalLayout->removeWidget(widget);
		delete m_widgets[threadId];
	}
}

void MainWindow::connect()
{
	QObject::connect(ui->pushButton, SIGNAL(clicked()),
					 SLOT(onStart()));

	QObject::connect(threadPool, SIGNAL(threadStarted(const Thread*)),
					 SLOT(onThreadStarted(const Thread*)));

	QObject::connect(threadPool, SIGNAL(threadDeleted(int)),
					 SLOT(onThreadDeleted(int)));


}
