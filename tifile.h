#include <qdatastream.h>
#include <qfile.h>
#include <qlist.h>

#include "tivar.h"
#include "tivarentry.h"

#ifndef TIFILE_H
#define TIFILE_H

class TiFile
{
public:
    TiFile(const QString filepath);

protected:
    // HEADER
    char    m_calc_model[8];            // 8-character signature. The signature is always "**TI89**".
    qint16  m_signature1;               // 2-byte further signature. These two bytes always contain {01h, 00h} = {1, 0}.
    char    m_default_folder_name[8];   // Default folder name (zero terminated unless 8 characters long).
    char    m_comment[40];              // Comment. The comment is either zero-terminated or padded on the right with space characters.
    qint16  m_entries_number;           // Number of variable and folder entries in the variable table.

    // VARIABLE TABLE
    QList<TiVarEntry*> m_entries;       // Variable and folder entries. @see TiVarEntry

    // DATA
    qint32 m_file_size;                 // The file size, in bytes.
    qint16 m_signature2;                // A 2-byte signature. These two bytes always contain {A5h, 5Ah}.
};

#endif // TIFILE_H
