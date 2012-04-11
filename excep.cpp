#include "excep.h"

Excep::Excep(qint8 number, QString const& message, qint8 level) throw() :
    m_number(number),
    m_message(message),
    m_level(level)
{

}

Excep::~Excep() throw()
{

}

char const *Excep::what() const throw()
{
    return m_message.toStdString().c_str();
}

void Excep::raise() const throw()
{
    throw *this;
}

qint8 Excep::number() const throw()
{
    return m_number;
}

qint8 Excep::level() const throw()
{
    return m_level;
}
