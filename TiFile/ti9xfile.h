#ifndef TI9XFILE_H
#define TI9XFILE_H

#include <QFile>
#include <QFileInfo>
#include <QList>
#include <QTreeWidgetItem>
#include <iostream>

#include "tifile.h"
#include "datastream.h"
#include "tivarentry.h"
#include "tistringvar.h"
#include "titextvar.h"

class Ti9xFile : public TiFile
{
public:
    Ti9xFile(QString const &file_path = "");
    virtual ~Ti9xFile();
    virtual void readHeader();
    virtual void readVariables();
    virtual void buildFileTree();

    // GETTERS
    inline char const *calc_model() const {
        return m_calc_model;
    }
    inline qint16 const &signature1() const {
        return m_signature1;
    }
    inline char const *default_folder_name() const {
        return m_default_folder_name;
    }
    inline char const *comment() const {
        return m_comment;
    }
    inline qint16 const &entries_number() const {
        return m_entries_number;
    }
    inline QList<TiVarEntry*> const &entries() {
        return m_entries;
    }
    inline qint32 const &file_size() const {
        return m_file_size;
    }
    inline qint16 const &signature2() const {
        return m_signature2;
    }

protected:
    // HEADER
    char    m_calc_model[9];            // 8-character signature. The signature is always "**TI89**".
    qint16  m_signature1;               // 2-byte further signature. These two bytes always contain {01h, 00h} = {1, 0}.
    char    m_default_folder_name[9];   // Default folder name (zero terminated unless 8 characters long).
    char    m_comment[41];              // Comment. The comment is either zero-terminated or padded on the right with space characters.
    qint16  m_entries_number;           // Number of variable and folder entries in the variable table.

    // VARIABLE TABLE
    QList<TiVarEntry*> m_entries;       // Variable and folder entries. @see TiVarEntry

    // DATA
    qint32 m_file_size;                 // The file size, in bytes.
    qint16 m_signature2;                // A 2-byte signature. These two bytes always contain {A5h, 5Ah}.
};

#endif // TI9XFILE_H
