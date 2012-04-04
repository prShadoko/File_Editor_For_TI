#include "tifile.h"

TiFile::TiFile(const QString filepath) : m_var_entries_number(0), m_fol_entries_number(0)
{
    int offset = 0;
    Qfile ti_file(filepath);
    if(!ti_file.open(QIODevice::ReadOnly)) {
        return;
    }

    QDataStream reader(ti_file);
    // HEADER
    reader.readRawData(m_calc_model, 8);
    reader.readRawData(m_signature1, 2);
    reader.readRawData(m_default_folder_name, 8);
    reader.readRawData(m_comment, 40);
    reader.readRawData(m_entries_number, 2);

    offset += 60;

    // VARIABLE TABLE
    m_entries = new TiVarEntry*[m_entries_number];
    for(int i=0; i<m_entries_number; i++) {
        m_entries[i] = new TiVarEntry(&reader);
        if(!m_entries[i]->isFolder()) {
            m_var_entries_number++;
        }
        offset += 16;
    }
    m_fol_entries_number = m_entries_number - m_var_entries_number;

    reader.readRawData(m_file_size, 4);
    reader.readRawData(m_signature2, 2);

    offset += 6;

    m_variables = new TiVar*[m_var_entries_number];

    for(qint8 i=0; i<m_var_entries_number; i++) {
        for(qint8 j=0; j<m_entries_number; j++) {
            if(!m_entries[j]->isFolder()) {
                if(m_entries[j]->offset() == offset) { //TODO: Check endianness
                    m_variables[i] = new TiVar(); //TODO
                }
            }
        }
    }
}

TiFile::~TiFile() {
    delete[] m_entries;
    delete[] m_variables;
}
