#include <QCoreApplication>
#include "filesprinter.h"
#include "mytimer.h"
#include <iostream>
#include <QTextStream>

#include <QSet>
#include <QString>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    FilesPrinter printer;
    printer.initVec();
    printer.createSet();
    printer.printData();

    MyTimer timer;

    QObject::connect(&timer, SIGNAL(allowPrint()),
                     &printer, SLOT(handleTimer()));

    QObject::connect(&timer, SIGNAL(restart()), &printer, SLOT(restartSetOfFiles()));

    return a.exec();
}
