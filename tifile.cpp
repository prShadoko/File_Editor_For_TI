#include "tifile.h"

TiFile::TiFile(const QString file_path)
{
//    int offset = 0;
    QFile ti_file(file_path);
    if(!ti_file.open(QIODevice::ReadOnly)) {
        return;
    }

    QDataStream header_reader(&ti_file);
    // HEADER
    header_reader.readRawData(m_calc_model, 8);

    header_reader.setByteOrder(QDataStream::LittleEndian);
    header_reader >> m_signature1;

    header_reader.setByteOrder(QDataStream::BigEndian);
    header_reader.readRawData(m_default_folder_name, 8);
    header_reader.readRawData(m_comment, 40);

    header_reader.setByteOrder(QDataStream::LittleEndian);
    header_reader >> m_entries_number;

//    offset += 60;

    // VARIABLE TABLE
    for(int i=0; i<m_entries_number; i++) {
        qint32 offset;
        char name[8];
        qint8 type_id;
        qint8 attribute;
        qint16 var_number;

        header_reader >> offset;

        header_reader.setByteOrder(QDataStream::BigEndian);
        header_reader.readRawData(name, 8);

        header_reader.setByteOrder(QDataStream::LittleEndian);
        header_reader >> type_id;
        header_reader >> attribute;
        header_reader >> var_number;

        TiVarEntry *entry = new TiVarEntry(offset, name, type_id, attribute, var_number);
        if(!entry->isFolder()) {
//            QDataStream data_reader(&ti_file);
//            data_reader.skipRawData(offset);
//            m_entries.last()->setVariable(new TiVar());
        }
        m_entries.append(entry);
//TODO: sorting entries by variable offset with folders first
//        offset += 16;
    }

    header_reader.setByteOrder(QDataStream::LittleEndian);
    header_reader >> m_file_size;
    header_reader >> m_signature2;

//    offset += 6;
    ti_file.close();
}
