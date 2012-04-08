#ifndef TIVAR_H
#define TIVAR_H

#include <QtGlobal>

class TiVar
{
public:
    TiVar(char *raw_data, qint32 const &length, qint16 const &checksum);
    virtual ~TiVar();

    qint16 calc_checksum() const;
    virtual void parse() = 0;

    // GETTERS
    inline char const *raw_data() const {
        return m_raw_data;
    }
    inline qint16 const &checksum() const {
        return m_checksum;
    }

protected:
    char *m_raw_data;           // Data section.
    qint32 m_raw_data_length;   //
    qint16 m_checksum;          // Checksum. This is the lower 16 bits of the sum of all bytes in the first four bytes and the variable data.
};

#endif // TIVAR_H
