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
//TODO: error management / checking signatures
    QBuffer buffer;
    buffer.setData(m_raw_data, m_raw_data_length);
    QDataStream reader(&buffer);

    reader.setByteOrder(QDataStream::LittleEndian);
    reader >> m_size; // should be m_raw_data_length - 2
    reader >> m_signature1; // should be 0x00

    m_data = new char[m_size-2];
    reader.setByteOrder(QDataStream::BigEndian);
    reader.readRawData(m_data, m_size-2);

    reader.setByteOrder(QDataStream::LittleEndian);
    reader >> m_signature2; // should be 0x2D

    buffer.close();
}
