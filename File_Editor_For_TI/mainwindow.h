#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QDockWidget>
#include <QMainWindow>
#include <QMdiArea>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QTreeWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);

public slots:
    void openFile();
    void saveFile();
    void quit();
    void newVariable();
    void about();
    void aboutQt();

private:
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void createDockWindows();

    QMdiArea *m_mdi_area;
    QTreeWidget *m_opened_files;

    QMenu *m_file_menu;
    QMenu *m_edit_menu;
    QMenu *m_view_menu;
    QMenu *m_help_menu;
//    QToolBar *m_file_tool_bar;
//    QToolBar *m_edit_tool_bar;
    QAction *m_open_file_action;
    QAction *m_save_file_action;
    QAction *m_quit_action;
    QAction *m_new_variable_action;
    QAction *m_about_action;
    QAction *m_about_qt_action;
};

#endif // MAINWINDOW_H
