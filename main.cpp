#include "mainwindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	MainWindow mainWindow;
	mainWindow.setWindowTitle(QObject::tr("GUI Multi-Threading"));
	mainWindow.show();

	app.exec();

	return 0;
}
