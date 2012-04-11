#ifndef EXCEP_H
#define EXCEP_H

#include <exception>
#include <QString>

using namespace std;

class Excep : public exception
{
public:
    Excep(qint8 number = 0, QString const& message = "", qint8 level = 0) throw();
    virtual ~Excep() throw();
    virtual const char* what() const throw();
    void raise() const throw();
    qint8 number() const throw();
    qint8 level() const throw();

protected:
    qint8 m_number;
    QString m_message;
    qint8 m_level;
};

#endif // EXCEP_H
