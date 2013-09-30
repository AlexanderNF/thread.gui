#include "progresswidget.h"

#include "thread.h"
#include "ui_progresswidget.h"

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
