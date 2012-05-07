#include "openedfileswidget.h"
#include <QDebug>

OpenedFilesWidget::OpenedFilesWidget(QWidget *parent, QMenu *context_menu) :
    QTreeWidget(parent),
    m_context_menu(context_menu)
{
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
}

void OpenedFilesWidget::contextMenuEvent(QContextMenuEvent *event)
{
    if(m_context_menu != NULL) {
        m_context_menu->exec(event->globalPos());
    }
}
