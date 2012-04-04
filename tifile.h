#include "tivar.h"
#include "tivarentry.h"

#ifndef TIFILE_H
#define TIFILE_H

class TiFile
{
public:
    TiFile();

private:
    // HEADER
    qint8 m_calc_model[8];              // 8-character signature. The signature is always "**TI89**".
    qint8 m_signature1[2];              // 2-byte further signature. These two bytes always contain {01h, 00h} = {1, 0}.
    qint8 m_default_folder_name[8];     // Default folder name (zero terminated unless 8 characters long).
    qint8 m_comment[40];                // Comment. The comment is either zero-terminated or padded on the right with space characters.
    qint8 m_entries_number[2];          // Number of variable and folder entries in the variable table.

    // VARIABLE TABLE
    TiVarEntry** m_entries;             // Variable and folder entries. @see TiVarEntry

    // DATA
    qint8 m_file_size[4];               // The file size, in bytes.
    qint8 m_signature2[2];              // A 2-byte signature. These two bytes always contain {A5h, 5Ah}.
    TiVar** m_variables;                // Variables data. @see TiVar.

};

#endif // TIFILE_H
