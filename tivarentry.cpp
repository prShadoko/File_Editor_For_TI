#include "tivarentry.h"

TiVarEntry::TiVarEntry()
{
}

TiVarEntry::TiVarEntry(QDataStream *reader)
{
    reader.readRawData(m_offset, 4);
    reader.readRawData(m_name, 8);
    reader.readRawData(m_id, 1);
    reader.readRawData(m_attribute, 1);
    reader.readRawData(m_var_number, 2);
}

bool TiVarEntry::isFolder() {
    return (m_id == 0x1F);
}
