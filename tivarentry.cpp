#include "tivarentry.h"

TiVarEntry::TiVarEntry(qint32 &offset, char *name, qint8 &type_id, qint8 &attribute, qint16 &var_number) :
    m_offset(offset), m_type_id(type_id), m_attribute(attribute), m_var_number(var_number), m_variable(NULL)
{
    memcpy(m_name, name, 8);
}

bool TiVarEntry::isFolder() {
    return (m_type_id == 0x1F);
}
