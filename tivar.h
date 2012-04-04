#ifndef TIVAR_H
#define TIVAR_H

class TiVar
{
public:
    TiVar();

private:
    qint8* m_data;          // Data section.
    qint8 m_checksum[2];    // Checksum. This is the lower 16 bits of the sum of all bytes in the first four bytes and the variable data.
};

#endif // TIVAR_H
