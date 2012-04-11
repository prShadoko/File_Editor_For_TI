#ifndef DATASTREAM_H
#define DATASTREAM_H

#include <QDataStream>
#include "excep.h"

class DataStream : public QDataStream
{
public:
    DataStream(QIODevice *d);
    void read(char *dest, qint32 len) throw(Excep);
    void read(qint16 dest) throw(Excep);
};

#endif // DATASTREAM_H
