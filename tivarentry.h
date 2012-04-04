#ifndef TIVARENTRY_H
#define TIVARENTRY_H

class TiVarEntry
{
public:
    TiVarEntry();

private:
    qint8 m_offset[4];      // Variable : Offset to the data for this variable from the beginning of the file.
                            // Folder : Offset to the data for the next variable from the beginning of the file.
    qint8 m_name[8];        // Name of variable/folder (zero terminated if not 8 characters long).
    qint8 m_id;             // Variable : Type ID of the variable.
                            // Folder : This value is always 1Fh.
    qint8 m_attribute;      // Variable : Attribute (0: none, 1: locked, 2: archived)
                            // Folder : This value is always 0.
    qint8 m_var_number[2];  // Variables : Each byte has a value of 0.
                            // Folders : The number of variables in this folder.
};

#endif // TIVARENTRY_H
