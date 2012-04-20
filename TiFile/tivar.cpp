#include "tivar.h"

TiVar::TiVar() :
    m_raw_data(NULL),
    m_size(0),
    m_checksum(0)
{
}

TiVar::TiVar(char *raw_data, qint32 const &size, qint16 const &checksum) :
    m_raw_data(raw_data),
    m_size(size),
    m_checksum(checksum)
{
}

TiVar::~TiVar()
{
    if (m_raw_data != NULL) {
        delete[] m_raw_data;
    }
}

qint16 TiVar::calc_checksum() const
{
    unsigned char size_bytes[2];
    memcpy(size_bytes, reinterpret_cast<const unsigned char*>(&m_size), 2);
    qint16 checksum = size_bytes[0] + size_bytes[1];
    for(qint32 i=0; i<m_size; i++)
    {
        checksum += (unsigned char)m_raw_data[i];
    }

    return checksum;
}
