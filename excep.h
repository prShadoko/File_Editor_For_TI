#ifndef EXCEP_H
#define EXCEP_H

#include <QString>
#include <exception>

class Excep: public exception
{
public:
    Excep(qint8 number=0, QString const& message="", qint8 level=0) throw()
        :m_number(number),m_message(message),m_level(level)
    {}

    virtual const char* what() const throw()
    {
        return m_message.toStdString().c_str();
    }

    void raise() const throw(Excep)
    {
        throw *this;
    }

    qint8 number() const throw()
    {
        return m_number;
    }

    qint8 level() const throw()
    {
        return m_level;
    }

    virtual ~Erreur() throw()
    {}

private:
    qint8 m_number;
    QString m_message;
    qint8 m_level;
};

#endif // EXCEP_H
