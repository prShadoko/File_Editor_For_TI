#ifndef OPENEDFILESWIDGET_H
#define OPENEDFILESWIDGET_H

#include <QContextMenuEvent>
#include <QMenu>
#include <QTreeWidget>

class OpenedFilesWidget : public QTreeWidget
{
    Q_OBJECT
public:
    OpenedFilesWidget(QWidget *parent = 0, QMenu *context_menu = NULL);

    inline QMenu *contextMenu() const {
        return m_context_menu;
    }

    inline void setContextMenu(QMenu *menu) {
        m_context_menu = menu;
    }

protected:
    void contextMenuEvent(QContextMenuEvent *event);

private:
    QMenu *m_context_menu;
};

#endif // OPENEDFILESWIDGET_H
