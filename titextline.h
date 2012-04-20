#ifndef TITEXTLINE_H
#define TITEXTLINE_H

#include <QtGlobal>

//TODO: Should it inherit from TiVar ?
class TiTextLine // : public TiVar
{
public:
    enum LineType {
        PageBreak = 0x0C,
        Normal    = 0x20,
        Command   = 0x43,
        PrintObj  = 0x50
    };

    enum LineEnd {
        LineBreak = 0x0D,
        EndOfFile = 0x00
    };

    TiTextLine(char *data = NULL, LineEnd const eol = LineBreak, LineType const type = Normal);
    ~TiTextLine();

    // GETTERS
    inline LineType type() const {
        return m_type;
    }
    inline char const *data() const {
        return m_data;
    }
    inline LineEnd eol() const {
        return m_eol;
    }

protected:
    LineType m_type;    // Line type: 0Ch=page break, 20h=normal, 43h=Command, 50h=PrintObj
    char *m_data;       // Characters, first to last. The string is not zero-terminated.
    LineEnd m_eol;      // Line delimiter: 0Dh=line break, 00h=end of file
};

#endif // TITEXTLINE_H
