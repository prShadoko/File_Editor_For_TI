#include "tistringvar.h"

TiStringVar::TiStringVar(char *raw_data, qint32 const &length, qint16 const &checksum) :
    TiVar(raw_data, length, checksum)
{

}

TiStringVar::~TiStringVar()
{
    delete[] m_data;
}

void TiStringVar::parse()
{
    QBuffer buffer;
    buffer.setData(m_raw_data, m_raw_data_length);
    buffer.open(QIODevice::ReadOnly);
    QDataStream reader(&buffer);

    reader.setByteOrder(QDataStream::BigEndian);
    reader.skipRawData(4);              // skip the first four 0x00 bytes
    reader >> m_size;                   // size of the following data
    qint16 length = m_size - 2;         // size of the string itself
    reader >> m_signature1;             // should be 0x00
    m_data = new char[length];
    reader.readRawData(m_data, length); // the string content
    reader >> m_signature2;             // should be 0x2D

    buffer.close();

    if(m_signature1 != 0x00 || m_signature2 != 0x2D) {
        Excep(20, QString("Invalid signature encountered. File is corrupted.")).raise();
    }
}
