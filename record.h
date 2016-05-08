#ifndef RECORD_H
#define RECORD_H

#include "QtGui"

struct Record
{
    QString name;
    qint64 time;
    int clicks;
};

inline bool operator < (const Record & a, const Record & b)
{
    return a.time < b.time;
}

#endif // RECORD_H
