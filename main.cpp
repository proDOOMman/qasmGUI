// Copyright 2009 proDOOMman
// Distributed under the terms of the GNU General Public License v2

#include <QtGui/QApplication>
#include "codewindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    codeWindow w;
    w.show();
    return a.exec();
}
