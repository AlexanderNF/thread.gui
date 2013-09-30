#include "mainwindow.h"
#include "threadpool.h"

#if QT_VERSION >= 0x050000
#include <QtWidgets/QApplication>
#else
#include <QtGui/QApplication>
#endif

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

int main(int argc, char *argv[])
{
#ifdef MEMORY_LEAKS_SEARCH
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	QApplication app(argc, argv);

	MainWindow mainWindow;
	mainWindow.setWindowTitle(QObject::tr("GUI Multi-Threading"));
	mainWindow.show();

	app.exec();

	threadPool->deleteInstance();

	return 0;
}
