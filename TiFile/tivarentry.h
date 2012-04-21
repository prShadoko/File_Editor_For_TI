#ifndef TIVARENTRY_H
#define TIVARENTRY_H

#include <cstring>
#include "tivar.h"

class TiVarEntry
{
public:
    enum VarType {
        Expression = 0x00,
        List       = 0x04,
        Matrix     = 0x06,
        Data       = 0x0A,
        Text       = 0x0B,
        String     = 0x0C,
        GDB        = 0x0D,
        Figure     = 0x0E,
        Picture    = 0x10,
        Program    = 0x12,
        Function   = 0x13,
        Macro      = 0x14,
        Folder     = 0x1F
    };

    TiVarEntry(qint32 const offset, char const *name, VarType type_id, qint8 const attribute, qint16 const var_number);
    ~TiVarEntry();
    bool isFolder() const;

    // GETTERS
    inline qint32 const &offset() const {
        return m_offset;
    }
    inline char const *name() const {
        return m_name;
    }
    inline VarType const &type_id() const {
        return m_type_id;
    }
    inline qint8 const &attribute() const {
        return m_attribute;
    }
    inline qint16 const &var_number() const {
        return m_var_number;
    }
    inline TiVar *variable() const {
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
    VarType m_type_id;      // Variable : Type ID of the variable.
                            // Folder : This value is always 1Fh.
    qint8 m_attribute;      // Variable : Attribute (0: none, 1: locked, 2: archived)
                            // Folder : This value is always 0.
    qint16 m_var_number;    // Variables : Each byte has a value of 0.
                            // Folders : The number of variables in this folder.

    TiVar *m_variable;
};

#endif // TIVARENTRY_H
