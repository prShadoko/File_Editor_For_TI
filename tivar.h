#ifndef TIVAR_H
#define TIVAR_H

#include <QtGlobal>

class TiVar
{
public:
    TiVar();
    virtual ~TiVar();

protected:
    char *m_data;          // Data section.
    qint16 m_checksum;    // Checksum. This is the lower 16 bits of the sum of all bytes in the first four bytes and the variable data.
};

#endif // TIVAR_H
