#ifndef TISTRINGVAR_H
#define TISTRINGVAR_H

#include <QtGlobal>
#include "tivar.h"

//TODO: generic class for string variables and lines from text variables.

class TiStringVar : public TiVar
{
public:
    TiStringVar();

protected:
    char m_line_type;  // This byte always has a value of 0.
    char* m_data;      // Characters, first to last. The string is zero-terminated.
    char m_end_mark;   // This byte always has a value of 2Dh.
};

#endif // TISTRINGVAR_H
