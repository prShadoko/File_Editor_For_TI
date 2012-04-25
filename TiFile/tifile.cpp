#include "tifile.h"

TiFile::TiFile(QString const &file_path) :
    m_file_path(file_path),
    m_signature1(0x01),
    m_entries_number(0),
    m_file_size(0),
    m_signature2(0x5AA5)
{
    for(qint32 i=0; i<9; i++) {
        m_calc_model[i] = '\0';
        m_default_folder_name[i] = '\0';
    }
    for(qint32 i=0; i<41; i++) {
        m_comment[i] = '\0';
    }
}

TiFile::~TiFile()
{
    for(QList<TiVarEntry*>::iterator it=m_entries.begin(); it!=m_entries.end(); it++) {
        delete *it;
    }
}

void TiFile::readHeader()
{
    try
    {
        QFile ti_file(m_file_path);
        if(!ti_file.exists()) {
            Excep(1, QString("File does not exists : %1").arg(m_file_path)).raise();
        }
        if(!ti_file.open(QIODevice::ReadOnly)) {
            Excep(2, QString("Unable to open file : %1").arg(m_file_path)).raise();
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

            TiVarEntry *entry = new TiVarEntry(offset, name, static_cast<TiVarEntry::VarType>(type_id), attribute, var_number);
            m_entries.append(entry);
        }
//        qSort(m_entries);
        reader.setByteOrder(QDataStream::LittleEndian);
        reader.read(m_file_size);
        reader.read(m_signature2);
        ti_file.close();
    }
    catch(Excep &e)
    {
        std::cerr << "In file \"" << m_file_path.toStdString() << "\" : " << std::endl
                  << e.what() << std::endl;
    }
}

void TiFile::readVariables()
{
    try
    {
        QFile ti_file(m_file_path);
        if(!ti_file.exists()) {
            Excep(1, QString("File does not exists : %1").arg(m_file_path)).raise();
        }
        if(!ti_file.open(QIODevice::ReadOnly)) {
            Excep(2, QString("Unable to open file : %1").arg(m_file_path)).raise();
        }

        DataStream reader(&ti_file);
        for(QList<TiVarEntry*>::iterator it=m_entries.begin(); it!=m_entries.end(); it++) {
            if((*it)->isFolder()) {
                continue;
            }
            ti_file.seek((*it)->offset());
            reader.setByteOrder(QDataStream::BigEndian);
            reader.skipRawData(4);

            qint16 length;
            reader.read(length);

            char *data = new char[length];
            reader.read(data, length);

            qint16 checksum;
            reader.setByteOrder(QDataStream::LittleEndian);
            reader.read(checksum);

            TiVar *variable = NULL;
            switch((*it)->type_id()) {
                case TiVarEntry::Expression:{
//                    variable = new TiExpressionVar(data, length, checksum);
                    break;
                }
                case TiVarEntry::List:{
//                    variable = new TiListVar(data, length, checksum);
                    break;
                }
                case TiVarEntry::Matrix:{
//                    variable = new TiMatrixVar(data, length, checksum);
                    break;
                }
                case TiVarEntry::Data:{
//                    variable = new TiDataVar(data, length, checksum);
                    break;
                }
                case TiVarEntry::Text:{
                    variable = new TiTextVar(data, length, checksum);
                    break;
                }
                case TiVarEntry::String:{
                    variable = new TiStringVar(data, length, checksum);
                    break;
                }
                case TiVarEntry::GDB:{
//                    variable = new TiGDBVar(data, length, checksum);
                    break;
                }
                case TiVarEntry::Figure:{
//                    variable = new TiFigureVar(data, length, checksum);
                    break;
                }
                case TiVarEntry::Picture:{
//                    variable = new TiPictureVar(data, length, checksum);
                    break;
                }
                case TiVarEntry::Program:{
//                    variable = new TiProgramVar(data, length, checksum);
                    break;
                }
                case TiVarEntry::Function:{
//                    variable = new TiFunctionVar(data, length, checksum);
                    break;
                }
                case TiVarEntry::Macro:{
//                    variable = new TiMacroVar(data, length, checksum);
                    break;
                }
                default:{
                    break;
                }
            }
            (*it)->setVariable(variable);
        }
        ti_file.close();
    }
    catch(Excep &e)
    {
        std::cerr << "In file \"" << m_file_path.toStdString() << "\" : " << std::endl
                  << e.what() << std::endl;
    }
}
