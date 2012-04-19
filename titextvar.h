#ifndef TITEXTVAR_H
#define TITEXTVAR_H

#include <cstring>
#include <QBuffer>
#include <QList>
#include "datastream.h"
#include "titextline.h"
#include "tivar.h"

class TiTextVar : public TiVar
{
public:
    TiTextVar();
    TiTextVar(char *raw_data, const qint32 &length, const qint16 &checksum);
    ~TiTextVar();

    virtual void parse();
    virtual void check() throw(Excep);

protected:
    qint16 m_cursor_offset;     // Offset, in characters, to the cursor position.
    QList<TiTextLine*> m_lines; // Text lines @see TiTextLine
    qint8 m_eof;                // This byte always has a value of 0xE0.
};

#endif // TITEXTVAR_H
