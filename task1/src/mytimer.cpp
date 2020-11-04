#include "mytimer.h"
#include <stdio.h>

MyTimer::MyTimer(QObject *parent) : QObject(parent)
{
    timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), SIGNAL(allowPrint()));
    timer->start(5000); // 5 sek

    notifier = new QSocketNotifier(fileno(stdin), QSocketNotifier::Read, this);
    connect(notifier, SIGNAL(activated(int)), SLOT(commandEntered()));

}

void MyTimer::commandEntered()
{
    QTextStream stream(stdin);
    QString command;

    stream >> command;

    if(command == "stop")
        timer->stop();
    else if (command == "start")
        timer->start();
    else if (command == "exit")
        QCoreApplication::quit();
    else if(command == "timeout") {
        int value = 0;
        stream >> value;
        timer->setInterval(value);
    }
    else if (command == "restart") {
        emit restart();
        timer->start(5000);
    }
    else {
        qDebug() << "Garbage data in command == " << command;
        QCoreApplication::quit();
    }

}
