#include "datastream.h"

DataStream::DataStream(QIODevice *d) :
    QDataStream(d)
{

}

void DataStream::read(char *dest, qint32 len) throw(Excep)
{
    readRawData(dest, len);
    dest[len] = '\0';
    if(status() != Ok) {
        Excep(10, QString("An error occured while reading from stream. (status : %1)").arg(status())).raise();
    }
}

void DataStream::read(qint8 &dest) throw(Excep)
{
    (*this) >> dest;
    if(status() != Ok) {
        Excep(10, QString("An error occured while reading from stream. (status : %1)").arg(status())).raise();
    }
}

void DataStream::read(qint16 &dest) throw(Excep)
{
    (*this) >> dest;
    if(status() != Ok) {
        Excep(10, QString("An error occured while reading from stream. (status : %1)").arg(status())).raise();
    }
}

void DataStream::read(qint32 &dest) throw(Excep)
{
    (*this) >> dest;
    if(status() != Ok) {
        Excep(10, QString("An error occured while reading from stream. (status : %1)").arg(status())).raise();
    }
}
