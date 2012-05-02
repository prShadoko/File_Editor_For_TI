#ifndef TIFILE_H
#define TIFILE_H

#include <QString>
#include <QTreeWidgetItem>

class TiFile
{
public:
    TiFile(QString const &file_path = "");
    virtual ~TiFile();

    virtual void readHeader() = 0;
    virtual void readVariables() = 0;
    virtual QTreeWidgetItem *fileTree() = 0;

    // GETTERS
    inline QString const & filePath()
    {
        return m_file_path;
    }

    // SETTERS
    inline void setFilePath(QString const &file_path) {
        m_file_path = file_path;
    }

protected:
    QString m_file_path;

};

#endif // TIFILE_H
