#include "tivar.h"

TiVar::TiVar(char *raw_data, qint32 const &length, qint16 const &checksum) :
    m_raw_data(raw_data),
    m_raw_data_length(length),
    m_checksum(checksum)
{
    if(calc_checksum() != m_checksum) {
        Excep(10, QString("Invalid checksum. File is corrupted."));
    }
}

TiVar::~TiVar() {
    delete[] m_raw_data;
}

qint16 TiVar::calc_checksum() const
{
    qint16 checksum = 0;
    for(qint32 i=0; i<m_raw_data_length; i++)
    {
        checksum += (unsigned char)m_raw_data[i];
    }

    return checksum;
}
