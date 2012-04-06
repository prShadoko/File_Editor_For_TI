#include "tifile.h"

TiFile::TiFile(QString const file_path) : m_file_path(file_path)
{
    QFile ti_file(file_path);
    if(!ti_file.open(QIODevice::ReadOnly)) {
        return;
    }

    QDataStream reader(&ti_file);
    // HEADER
    reader.readRawData(m_calc_model, 8);
    m_calc_model[8] = '\0';

    reader.setByteOrder(QDataStream::LittleEndian);
    reader >> m_signature1;

    reader.setByteOrder(QDataStream::BigEndian);
    reader.readRawData(m_default_folder_name, 8);
    m_default_folder_name[8] = '\0';
    reader.readRawData(m_comment, 40);
    m_comment[40] = '\0';

    reader.setByteOrder(QDataStream::LittleEndian);
    reader >> m_entries_number;

    // VARIABLE TABLE
    for(int i=0; i<m_entries_number; i++) {
        qint32 offset;
        char name[9];
        qint8 type_id;
        qint8 attribute;
        qint16 var_number;

        reader >> offset;

        reader.setByteOrder(QDataStream::BigEndian);
        reader.readRawData(name, 8);
        reader[8] = '\0';

        reader.setByteOrder(QDataStream::LittleEndian);
        reader >> type_id;
        reader >> attribute;
        reader >> var_number;

        TiVarEntry *entry = new TiVarEntry(offset, name, type_id, attribute, var_number);
        m_entries.append(entry);
    }
    qSort(m_entries);

    reader.setByteOrder(QDataStream::LittleEndian);
    reader >> m_file_size;
    reader >> m_signature2;

    reader.setByteOrder(QDataStream::BigEndian);
    for(QList<TiVarEntry*>::iterator it=m_entries.begin(); it!=m_entries.end(); it++) {
        if(it->isFolder()) {
            continue;
        }

        qint32 length;
        if(it+1 != m_entries.end()) {
            length = (it+1)->offset() - it->offset();
        } else {
            length = m_file_size - it->offset();
        }
        char *data = new char[length];
        reader.readRawData(data, length);
        TiVar *variable = NULL;

        switch(it->type_id) {
            case TiVarEntry::Expression:{
//                    variable = new TiExpressionVar();
                break;
            }
            case TiVarEntry::List:{
//                    variable = new TiListVar();
                break;
            }
            case TiVarEntry::Matrix:{
//                    variable = new TiMatrixVar();
                break;
            }
            case TiVarEntry::Data:{
//                    variable = new TiDataVar();
                break;
            }
            case TiVarEntry::Text:{
//                    variable = new TiTextVar();
                break;
            }
            case TiVarEntry::String:{
                variable = new TiStringVar(data);
                break;
            }
            case TiVarEntry::GDB:{
//                    variable = new TiGDBVar();
                break;
            }
            case TiVarEntry::Figure:{
//                    variable = new TiFigureVar();
                break;
            }
            case TiVarEntry::Picture:{
//                    variable = new TiPictureVar();
                break;
            }
            case TiVarEntry::Program:{
//                    variable = new TiProgramVar();
                break;
            }
            case TiVarEntry::Function:{
//                    variable = new TiFunctionVar();
                break;
            }
            case TiVarEntry::Macro:{
//                    variable = new TiMacroVar();
                break;
            }
        }
        it->setVariable(variable);
        delete[] data;
    }
    ti_file.close();
}
