#ifndef TIVARENTRY_H
#define TIVARENTRY_H

#include <cstring>
#include "tivar.h"

class TiVarEntry
{
public:
    static qint8 const Expression = 0x00;
    static qint8 const List       = 0x04;
    static qint8 const Matrix     = 0x06;
    static qint8 const Data       = 0x0A;
    static qint8 const Text       = 0x0B;
    static qint8 const String     = 0x0C;
    static qint8 const GDB        = 0x0D;
    static qint8 const Figure     = 0x0E;
    static qint8 const Picture    = 0x10;
    static qint8 const Program    = 0x12;
    static qint8 const Function   = 0x13;
    static qint8 const Macro      = 0x14;

    TiVarEntry(qint32 const &offset, char const *name, qint8 const &type_id, qint8 const &attribute, qint16 const &var_number);
    ~TiVarEntry();
    bool isFolder() const;
    // WARNING: Those may not have the expected signature
    bool operator<(TiVarEntry const &other) const;
    bool operator>(TiVarEntry const &other) const;

    // GETTERS
    inline qint32 const &offset() const {
        return m_offset;
    }
    inline char const *name() const {
        return m_name;
    }
    inline qint8 const &type_id() const {
        return m_type_id;
    }
    inline qint8 const &attribute() const {
        return m_attribute;
    }
    inline qint16 const &var_number() const {
        return m_var_number;
    }
    inline TiVar const *variable() const {
        return m_variable;
    }
    // SETTERS
    inline void setVariable(TiVar *variable) {
        m_variable = variable;
    }

protected:
    qint32 m_offset;        // Variable : Offset to the data for this variable from the beginning of the file.
                            // Folder : Offset to the data for the next variable from the beginning of the file.
    char m_name[9];         // Name of variable/folder (zero terminated if not 8 characters long).
    qint8 m_type_id;        // Variable : Type ID of the variable.
                            // Folder : This value is always 1Fh.
    qint8 m_attribute;      // Variable : Attribute (0: none, 1: locked, 2: archived)
                            // Folder : This value is always 0.
    qint16 m_var_number;    // Variables : Each byte has a value of 0.
                            // Folders : The number of variables in this folder.

    TiVar *m_variable;
};

#endif // TIVARENTRY_H
