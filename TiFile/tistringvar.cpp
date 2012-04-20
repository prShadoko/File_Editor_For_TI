#include "tistringvar.h"

TiStringVar::TiStringVar() :
    TiVar(),
    m_signature1(0x00),
    m_data(NULL),
    m_signature2(0x2D)
{
}

TiStringVar::TiStringVar(char *raw_data, qint32 const &size, qint16 const &checksum) :
    TiVar(raw_data, size, checksum)
{
}

TiStringVar::~TiStringVar()
{
    if(m_data != NULL) {
        delete[] m_data;
    }
}

void TiStringVar::parse()
{
    QBuffer buffer;
    buffer.setData(m_raw_data, m_size);
    buffer.open(QIODevice::ReadOnly);
    QDataStream reader(&buffer);

    qint16 length = m_size - 2;         // size of the string itself
    reader >> m_signature1;             // should be 0x00
    m_data = new char[length];
    reader.readRawData(m_data, length); // the string content
    reader >> m_signature2;             // should be 0x2D

    buffer.close();

}

void TiStringVar::check() throw(Excep)
{
    if(m_signature1 != 0x00 || m_signature2 != 0x2D) {
        Excep(20, QString("Invalid signature encountered. File is corrupted.")).raise();
    }
    if(m_checksum != calc_checksum()) {
        Excep(21, QString("Invalid checksum. File is corrupted.")).raise();
    }
}
