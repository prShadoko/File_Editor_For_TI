#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    m_mdi_area = new QMdiArea();
    setCentralWidget(m_mdi_area);

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    createDockWindows();

    setWindowTitle(tr("File Editor For TI"));
}

void MainWindow::createActions()
{
    m_open_file_action = new QAction(QIcon(":/images/open.png"), tr("&Open file..."), this);
    m_open_file_action->setShortcut(QKeySequence::Open);
    m_open_file_action->setStatusTip(tr("Open a TI file"));
    connect(m_open_file_action, SIGNAL(triggered()), this, SLOT(openFile()));

    m_save_file_action = new QAction(QIcon(":/images/save.png"), tr("&Save file"), this);
    m_save_file_action->setStatusTip(tr("Save the current TI file"));
    connect(m_save_file_action, SIGNAL(triggered()), this, SLOT(saveFile()));

    m_quit_action = new QAction(QIcon(":/images/exit.png"), tr("&Quit"), this);
    m_save_file_action->setShortcut(QKeySequence::Quit);
    m_quit_action->setStatusTip(tr("Quit the application"));
    connect(m_quit_action, SIGNAL(triggered()), this, SLOT(quit()));;

    m_new_variable_action = new QAction(QIcon(":/images/new.png"), tr("&New variable"), this);
    m_new_variable_action->setShortcut(QKeySequence(tr("Ctrl+Shift+N", "Edit|New variable")));
    m_new_variable_action->setStatusTip(tr("Create a new TI variable"));
    connect(m_new_variable_action, SIGNAL(triggered()), this, SLOT(newVariable()));

    m_about_action = new QAction(QIcon(":/images/about.png"), tr("&About..."), this);
    m_about_action->setStatusTip(tr("Show the application's About box"));
    connect(m_about_action, SIGNAL(triggered()), this, SLOT(about()));

    m_about_qt_action = new QAction(QIcon(":/images/about.png"), tr("About &Qt..."), this);
    m_about_qt_action->setStatusTip(tr("Show the Qt library's About box"));
    connect(m_about_qt_action, SIGNAL(triggered()), this, SLOT(aboutQt()));
}

void MainWindow::createMenus()
{
    m_file_menu = menuBar()->addMenu(tr("&File"));
    m_file_menu->addAction(m_open_file_action);
    m_file_menu->addAction(m_save_file_action);
    m_file_menu->addSeparator();
    m_file_menu->addAction(m_quit_action);

    m_edit_menu = menuBar()->addMenu(tr("&Edit"));
    m_edit_menu->addAction(m_new_variable_action);

    m_view_menu = menuBar()->addMenu(tr("&View"));

    menuBar()->addSeparator();

    m_help_menu = menuBar()->addMenu(tr("&Help"));
    m_help_menu->addAction(m_about_action);
    m_help_menu->addAction(m_about_qt_action);
}

void MainWindow::createToolBars()
{
    // TODO
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::createDockWindows()
{
    QDockWidget *dock = new QDockWidget(tr("Opened files"), this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    m_opened_files = new QTreeWidget(dock);
    m_opened_files->addTopLevelItems(QList<QTreeWidgetItem*>());
    dock->setWidget(m_opened_files);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    m_view_menu->addAction(dock->toggleViewAction());
}

void MainWindow::openFile()
{
    //TODO
}

void MainWindow::saveFile()
{
    //TODO
}

void MainWindow::quit()
{
    //TODO
}

void MainWindow::newVariable()
{
    //TODO
}

void MainWindow::about()
{
    //TODO
}

void MainWindow::aboutQt()
{
    //TODO
}
