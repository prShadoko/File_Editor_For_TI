#ifndef TIVAR_H
#define TIVAR_H

#include <QtGlobal>
#include "excep.h"

class TiVar
{
public:
    TiVar();
    TiVar(char *raw_data, qint32 const &size, qint16 const &checksum);
    virtual ~TiVar();

    virtual void parse() = 0;
    virtual void check() throw(Excep) = 0;
    qint16 calc_checksum() const;

    // GETTERS
    inline char const *raw_data() const {
        return m_raw_data;
    }
    inline qint16 const &size() const {
        return m_size;
    }
    inline qint16 const &checksum() const {
        return m_checksum;
    }

protected:
    char *m_raw_data;       // The variable raw data
    qint16 m_size;          // Size of variable data.
    qint16 m_checksum;      // Checksum. This is the lower 16 bits of the sum of all bytes in the variable data.
};

#endif // TIVAR_H
