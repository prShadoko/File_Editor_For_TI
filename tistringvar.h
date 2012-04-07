#ifndef TISTRINGVAR_H
#define TISTRINGVAR_H

//#include <QtGlobal>
#include <QDataStream>
#include "tivar.h"

//TODO: generic class for string variables and lines from text variables.

class TiStringVar : public TiVar
{
public:
    TiStringVar(char const *data);

protected:
    qint16 m_size;      // Number of bytes in this string minus two for this field.
    qint8 m_signature;  // This byte always has a value of 0.
    char *m_data;       // Characters, first to last. The string is zero-terminated.
    qint8 m_end_mark;   // This byte always has a value of 2Dh.
};

#endif // TISTRINGVAR_H
