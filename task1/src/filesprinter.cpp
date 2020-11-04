#include "filesprinter.h"
#include <QDebug>
#include <QDir>
#include <utility>
#include <iostream>
#include <QtMath>
#include <QtGlobal>
#include <limits>

FilesPrinter::FilesPrinter(QObject *parent) : QObject(parent)
{}

void FilesPrinter::initVec()
{
    QDir curDir = QDir::current();
    curDir.setSorting(QDir::Reversed | QDir::Size);
    QFileInfoList files = curDir.entryInfoList();
    data.resize(files.size());
    for (int i = 0; i < files.size(); ++i) {
        data[i].fileName = std::move(files[i].fileName());
        data[i].size = files[i].size();
    }
}

void FilesPrinter::createSet()
{
    for (int i = 0; i < data.size(); ++i)
        names.insert(data[i].fileName);
}

void FilesPrinter::printData()
{
    QTextStream stream(stdout);
    stream << "{";
    for (auto it = names.begin(); it != names.end();) {
            stream << *it;
            if (++it != names.end())
                stream << ", ";
    }
    stream << "}\n>\n";
}

#define DEVIATION ( static_cast<double>(data[i].size) - (0.75 * midSizeFile()) )

double FilesPrinter::UniqueRootMeanSquareDeviation(int i)
{
    double multip = (DEVIATION * DEVIATION);
    Q_ASSERT(multip > 0);
    return qSqrt(multip);
}

#undef DEVIATION

double FilesPrinter::midSizeFile()
{
    double sum = 0;
    for (int i = 0; i < data.size(); ++i) {
            sum += data[i].size;
    }
    Q_ASSERT(data.size());
    return sum / data.size();
}


void FilesPrinter::handleTimer()
{
    if (data.empty()) {
        Q_ASSERT(names.empty());
        qDebug() << "{}\n";
        return;
    }
    int index = 0;
    double min = std::numeric_limits<double>::max();
    double value = 0.0;
    for (int i = 0; i < data.size(); ++i) {
            value = UniqueRootMeanSquareDeviation(i);
            if (value < min) {
                min = value;
                index = i;
            }
    }

    auto findIt = names.begin(); //find the element to erase from the set
    while (findIt != names.end()) {
        if (*findIt == data[index].fileName)
            break;
        ++findIt;
    }
    Q_ASSERT(findIt != names.end());
    names.erase(findIt);
    data.erase(data.begin() + index);
    printData();
}

void FilesPrinter::restartSetOfFiles()
{
    data.clear();
    names.clear();
    initVec();
    createSet();
    printData();
}
