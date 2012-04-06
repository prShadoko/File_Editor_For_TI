#include "tivarentry.h"

TiVarEntry::TiVarEntry(qint32 const &offset, char const *name, qint8 const &type_id, qint8 const &attribute, qint16 const &var_number) const :
    m_offset(offset), m_type_id(type_id), m_attribute(attribute), m_var_number(var_number), m_variable(NULL)
{
    strcpy(m_name, name);
}

bool const &TiVarEntry::isFolder() const {
    return (m_type_id == 0x1F);
}

bool const &TiVarEntry::operator<(TiVarEntry const &other) const {
    //
    return (this->offset() < other.offset() || (this->offset() == other.offset() && this->isFolder() && !other.isFolder()));
}

bool const &TiVarEntry::operator>(TiVarEntry const &other) const {
    return (this->offset() > other.offset() || (this->offset() == other.offset() && !this->isFolder() && other.isFolder()));
}
