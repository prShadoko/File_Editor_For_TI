#ifndef TITEXTLINE_H
#define TITEXTLINE_H

#include <QtGlobal>

//TODO: Should it inherit from TiVar ?
class TiTextLine // : public TiVar
{
public:
    TiTextLine();

protected:
    qint8 m_type;   // Line type: 0Ch=page break, 20h=normal, 43h=Command, 50h=PrintObj
    char *m_data;   // Characters, first to last. The string is not zero-terminated.
    qint8 m_eol;    // Line delimiter: 0Dh=line break, 00h=end of file
};

#endif // TITEXTLINE_H
