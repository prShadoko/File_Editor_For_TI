#ifndef TIVARENTRY_H
#define TIVARENTRY_H

class TiVarEntry
{
public:
    TiVarEntry();
    TiVarEntry(QDataStream *reader);
    bool isFolder();

    inline const qint8* offset() {
        return m_offset;
    }

    inline const qint8* name() {
        return m_name;
    }

    inline const qint8 type_id() {
        return m_type_id;
    }

    inline const qint8 attribute() {
        return m_attribute;
    }

    inline const qint8* var_number() {
        return m_var_number;
    }

protected:
    qint8 m_offset[4];      // Variable : Offset to the data for this variable from the beginning of the file.
                            // Folder : Offset to the data for the next variable from the beginning of the file.
    qint8 m_name[8];        // Name of variable/folder (zero terminated if not 8 characters long).
    qint8 m_type_id;             // Variable : Type ID of the variable.
                            // Folder : This value is always 1Fh.
    qint8 m_attribute;      // Variable : Attribute (0: none, 1: locked, 2: archived)
                            // Folder : This value is always 0.
    qint8 m_var_number[2];  // Variables : Each byte has a value of 0.
                            // Folders : The number of variables in this folder.
};

#endif // TIVARENTRY_H
