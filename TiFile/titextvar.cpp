#include "titextvar.h"

TiTextVar::TiTextVar() :
    TiVar(),
    m_cursor_offset(0x01),
    m_eof(0xE0)
{
    m_lines.append(new TiTextLine(NULL, TiTextLine::EndOfFile));
}

TiTextVar::TiTextVar(char *raw_data, qint32 const &length, qint16 const &checksum) :
    TiVar(raw_data, length, checksum)
{
}

TiTextVar::~TiTextVar()
{
    for(QList<TiTextLine*>::iterator it=m_lines.begin(); it!=m_lines.end(); it++) {
        delete *it;
    }
}

void TiTextVar::parse()
{
    QBuffer buffer;
    buffer.setData(m_raw_data, m_size);
    buffer.open(QIODevice::ReadOnly);
    QDataStream reader(&buffer);

    reader >> m_cursor_offset;

    QList<QByteArray> lines = buffer.buffer().split(static_cast<char>(TiTextLine::LineBreak));
    lines.last().chop(2); // remove the end of line  and end of file bytes from the last line
    lines.first() = lines.first().mid(2); // remove the cursor offset bytes from the first line
    for(QList<QByteArray>::iterator it=lines.begin(); it!=lines.end(); it++)
    {
        (*it) = (*it).mid(1); // remove the line type byte from current line

        qint8 line_type;
        char* data = new char[(*it).size()+1];
        strcpy(data, (*it).data());
        qint8 eol;

        reader >> line_type;
        reader.skipRawData((*it).size());
        reader >> eol;
        m_lines.append(new TiTextLine(data, static_cast<TiTextLine::LineEnd>(eol), static_cast<TiTextLine::LineType>(line_type)));
    }
    reader >> m_eof;

    buffer.close();
}

void TiTextVar::check() throw(Excep)
{
}
