#include "datastream.h"

DataStream::DataStream(QIODevice *d) :
    QDataStream(d)
{

}

void DataStream::read(char *dest, qint32 len) throw(Excep)
{
    if(readRawData(dest, len) != len || status() != QDataStream::Ok) {
        Excep(10, QString("An error occured while reading from stream.")).raise();
    }
}

void DataStream::read(qint16 dest) throw(Excep)
{
    (*this) >> dest;
    if(status() != QDataStream::Ok) {
        Excep(10, QString("An error occured while reading from stream.")).raise();
    }
}
