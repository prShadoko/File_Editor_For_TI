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
    virtual void buildFileTree() = 0;
    QTreeWidgetItem *fileTree() {
        return m_file_tree;
    }

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
    QTreeWidgetItem *m_file_tree;
};

#endif // TIFILE_H
