/**
 * @author Andy Wang, UC Berkeley.
 * Copyright 2016 reserve.
 * UC Berkeley, Slide_2016 project.
 * Advised by Prof. Sequin H. Carlos.
 */

#include "MainWindow.h"
#include "DarkStyle.h"
#include "Scripting/PythonModule.h"
#include <QApplication>
#include <QSurfaceFormat>

#include <iostream>

int main(int argc, char *argv[])
{
	InitPython();
    std::cout << "Welcome to NOME!" << std::endl;

    QApplication a(argc, argv);
	a.setApplicationName("Nome");
	a.setApplicationDisplayName("Nome 1 Extended Edition");
	a.setApplicationVersion("1.0");
	a.setOrganizationName("UC Berkeley");
	a.setOrganizationDomain("eecs.berkeley.edu");

	a.setStyle(new DarkStyle);

	QSurfaceFormat fmt;
	fmt.setDepthBufferSize(24);
	fmt.setStencilBufferSize(8);
	QSurfaceFormat::setDefaultFormat(fmt);

	CMainWindow* window = new CMainWindow();
    window->show();

    int retval = a.exec();
    FiniPythion();
	return retval;
}
