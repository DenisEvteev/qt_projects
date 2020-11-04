#ifndef MYTIMER_H
#define MYTIMER_H

#include <QObject>
#include <QTimer>
#include <QString>
#include <QTextStream>
#include <QSocketNotifier>
#include <QDebug>
#include <QCoreApplication>

class MyTimer : public QObject
{
    Q_OBJECT
public:
    MyTimer(QObject *parent = nullptr);
public slots:
    void commandEntered();
signals:
    void allowPrint();
    void restart();
private:
    QTimer          *timer;
    QSocketNotifier *notifier;
};

#endif // MYTIMER_H
