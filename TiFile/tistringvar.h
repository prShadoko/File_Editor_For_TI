#ifndef TISTRINGVAR_H
#define TISTRINGVAR_H

#include <QBuffer>
#include <QDataStream>
#include "tivar.h"

class TiStringVar : public TiVar
{
public:
    TiStringVar();
    TiStringVar(char *raw_data, qint32 const &size, qint16 const &checksum);
    ~TiStringVar();
    virtual void parse();
    virtual void check() throw(Excep);

    // GETTERS
    inline qint8 const &signature1() const {
        return m_signature1;
    }
    inline char const *data() const {
        return m_data;
    }
    inline qint8 const &signature2() const {
        return m_signature2;
    }

protected:
    qint8 m_signature1; // This byte always has a value of 0.
    char *m_data;       // Characters, first to last. The string is zero-terminated.
    qint8 m_signature2; // This byte always has a value of 2Dh.
};

#endif // TISTRINGVAR_H
