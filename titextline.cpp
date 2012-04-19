#include "titextline.h"

TiTextLine::TiTextLine(char *data, LineEnd const eol, LineType const type) :
    m_type(type),
    m_data(data),
    m_eol(eol)
{
}

TiTextLine::~TiTextLine()
{
    if(m_data != NULL) {
        delete[] m_data;
    }
}
