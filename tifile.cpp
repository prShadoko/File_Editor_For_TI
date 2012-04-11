#include "tifile.h"

TiFile::TiFile()
{
    for(qint32 i=0; i<9; i++) {
        m_calc_model[i] = '\0';
    }
    m_signature1 = 0x01;
    for(qint32 i=0; i<9; i++) {
        m_default_folder_name[i] = '\0';
    }
    for(qint32 i=0; i<9; i++) {
            m_comment[i] = '\0';
    }
    m_entries_number = 0;
    m_file_size = 0;
    m_signature2 = 0x5AA5;
}

TiFile::TiFile(QString const file_path) :
    m_file_path(file_path)
{
    TiFile();
    try
    {
        QFile ti_file(file_path);
        if(!ti_file.open(QIODevice::ReadOnly)) {
            Excep(1, QString("Unable to open file : %1").arg(file_path)).raise();
        }

        DataStream reader(&ti_file);
        // HEADER
        reader.read(m_calc_model, 8);

        reader.setByteOrder(QDataStream::LittleEndian);
        reader.read(m_signature1);

        reader.setByteOrder(QDataStream::BigEndian);
        reader.read(m_default_folder_name, 8);
        reader.read(m_comment, 40);

        reader.setByteOrder(QDataStream::LittleEndian);
        reader.read(m_entries_number);

        // VARIABLE TABLE
        for(int i=0; i<m_entries_number; i++) {
            qint32 offset;
            char name[9];
            qint8 type_id;
            qint8 attribute;
            qint16 var_number;

            reader.read(offset);

            reader.setByteOrder(QDataStream::BigEndian);
            reader.read(name, 8);

            reader.setByteOrder(QDataStream::LittleEndian);
            reader.read(type_id);
            reader.read(attribute);
            reader.read(var_number);

            TiVarEntry *entry = new TiVarEntry(offset, name, type_id, attribute, var_number);
            m_entries.append(entry);
        }
        qSort(m_entries);

        reader.setByteOrder(QDataStream::LittleEndian);
        reader.read(m_file_size);
        reader.read(m_signature2);

        reader.setByteOrder(QDataStream::BigEndian);
        for(QList<TiVarEntry*>::iterator it=m_entries.begin(); it!=m_entries.end(); it++) {
            if((*it)->isFolder()) {
                continue;
            }

            qint32 length;
            if(it+1 != m_entries.end()) {
                length = (*(it+1))->offset() - (*it)->offset() - 2;
            } else {
                length = m_file_size - (*it)->offset() - 2;
            }
            char *data = new char[length];
            qint16 checksum;
            reader.setByteOrder(QDataStream::BigEndian);
            reader.read(data, length);
            reader.setByteOrder(QDataStream::LittleEndian);
            reader.read(checksum);
            TiVar *variable = NULL;

            switch((*it)->type_id()) {
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
                    variable = new TiStringVar(data, length, checksum);
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
            (*it)->setVariable(variable);
        }
        ti_file.close();
    }
    catch(Excep &e)
    {
        // Handle exception
    }
}

TiFile::~TiFile()
{
    for(QList<TiVarEntry*>::iterator it=m_entries.begin(); it!=m_entries.end(); it++) {
        delete *it;
    }
}
