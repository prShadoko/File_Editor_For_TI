#ifndef TIVARENTRY_H
#define TIVARENTRY_H

#include <cstring>
#include "tivar.h"

class TiVarEntry
{
public:
    TiVarEntry(qint32 &offset, char *name, qint8 &type_id, qint8 &attribute, qint16 &var_number);
    bool isFolder();

    // GETTERS
    inline const qint32& offset() {
        return m_offset;
    }

    inline const char* name() {
        return m_name;
    }

    inline const qint8& type_id() {
        return m_type_id;
    }

    inline const qint8& attribute() {
        return m_attribute;
    }

    inline const qint16& var_number() {
        return m_var_number;
    }

    inline const TiVar* variable() {
        return m_variable;
    }

    // SETTERS
    inline void setVariable(TiVar *variable) {
        m_variable = variable;
    }

protected:
    qint32 m_offset;        // Variable : Offset to the data for this variable from the beginning of the file.
                            // Folder : Offset to the data for the next variable from the beginning of the file.
    char m_name[8];         // Name of variable/folder (zero terminated if not 8 characters long).
    qint8 m_type_id;        // Variable : Type ID of the variable.
                            // Folder : This value is always 1Fh.
    qint8 m_attribute;      // Variable : Attribute (0: none, 1: locked, 2: archived)
                            // Folder : This value is always 0.
    qint16 m_var_number;    // Variables : Each byte has a value of 0.
                            // Folders : The number of variables in this folder.

    TiVar *m_variable;
};

#endif // TIVARENTRY_H
