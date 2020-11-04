#ifndef FILESPRINTER_H
#define FILESPRINTER_H

#include <QObject>
#include <QTextStream>
#include <QCoreApplication>
#include <QString>
#include <QFileInfo>

#include <vector>
#include <set>
#include <iostream>

typedef struct file_data {
    QString fileName;
    qint64 size;
}file_t;

//functor object to make a required order in set of files
class Functor {
public:
    bool operator()(const QString& file1, const QString& file2) const {
        QFileInfo f1(file1), f2(file2);
        Q_ASSERT(f1.exists() && f2.exists());
        return f1.size() <= f2.size();
    }

};

class FilesPrinter : public QObject
{
    Q_OBJECT
public:
    explicit FilesPrinter(QObject *parent = nullptr);
    void initVec();
    void createSet();
    /**Print data that is situated in the set*/
    void printData();
    double UniqueRootMeanSquareDeviation(int i);
    double midSizeFile();

signals:
    void readUserCommand();
public slots:
    void handleTimer();
    void restartSetOfFiles();

private:
    std::vector<file_t> data;
    std::set<QString, Functor> names;
};



#endif // FILESPRINTER_H
