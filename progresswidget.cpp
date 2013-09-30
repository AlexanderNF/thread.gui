#include "progresswidget.h"

#include "thread.h"
#include "ui_progresswidget.h"

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

ProgressWidget::ProgressWidget(const Thread *thread, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ProgressWidget), m_pThread(thread)
{
	ui->setupUi(this);
	init();
}

ProgressWidget::~ProgressWidget()
{
	delete ui;
}

void ProgressWidget::setProgress(int percents)
{
	ui->progressBar->setValue(percents);
	ui->label->setText(QString::number(m_pThread->duration()));
	ui->label_2->setText(QString::number(percents) + "%");
}

void ProgressWidget::init()
{
	ui->label->setText(QString::number(m_pThread->duration()));
}
