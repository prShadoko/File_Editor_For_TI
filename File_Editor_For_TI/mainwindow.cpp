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
    m_new_file_action = new QAction(QIcon(":/images/new.png"), tr("&New file"), this);
    m_new_file_action->setShortcut(QKeySequence::New);
    m_new_file_action->setStatusTip(tr("Create a new TI file"));
    connect(m_new_file_action, SIGNAL(triggered()), this, SLOT(newFile()));

    m_open_file_action = new QAction(QIcon(":/images/open.png"), tr("&Open file..."), this);
    m_open_file_action->setShortcut(QKeySequence::Open);
    m_open_file_action->setStatusTip(tr("Open a TI file"));
    connect(m_open_file_action, SIGNAL(triggered()), this, SLOT(openFile()));

    m_save_file_action = new QAction(QIcon(":/images/save.png"), tr("&Save file"), this);
    m_save_file_action->setStatusTip(tr("Save the current TI file"));
    connect(m_save_file_action, SIGNAL(triggered()), this, SLOT(saveFile()));

    m_close_file_action = new QAction(QIcon(":/images/close.png"), tr("&Close file"), this);
//    m_close_file_action->setShortcut(QKeySequence::Close);    //Usual close shortcut should not be used here
    m_close_file_action->setStatusTip(tr("Close the current TI file"));
    connect(m_close_file_action, SIGNAL(triggered()), this, SLOT(closeFile()));

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
    m_file_menu->addAction(m_new_file_action);
    m_file_menu->addAction(m_open_file_action);
    m_file_menu->addAction(m_save_file_action);
    m_file_menu->addAction(m_close_file_action);
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
    m_opened_files_tree = new OpenedFilesWidget(dock);
    QMenu *menu = new QMenu(m_opened_files_tree);

    menu->addActions(QList<QAction*>()
                     << m_new_file_action
                     << m_open_file_action
                     << m_close_file_action);
    m_opened_files_tree->setContextMenu(menu);
    m_opened_files_tree->setHeaderHidden(true);
    dock->setWidget(m_opened_files_tree);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, dock);
    m_view_menu->addAction(dock->toggleViewAction());
}

void MainWindow::newFile()
{
    //TODO
    //Choose calc model
    TiFile *file = new Ti9xFile();
    m_opened_files.append(file);
    file->buildFileTree();
    m_opened_files_tree->addTopLevelItem(file->fileTree());

    m_close_file_action->setEnabled(true);
}

void MainWindow::openFile()
{
    //TODO: complete the extension filter
    //TODO: allow multiple-file selection
    QString filename = QFileDialog::getOpenFileName(this, tr("Open a TI file"), QDir::homePath(), tr("All files(*.*);;TI strings (*.89s *.92s *.9xs *.v2s);;TI texts (*.89t *.92t *.9xt *.v2t)"));
    if(!filename.isEmpty())
    {
        TiFile *file = new Ti9xFile(filename);
        //TODO: check which file type it is to call the right constructor
        //TiFile *file = new Ti8xFile(filename);
        file->readHeader();
        m_opened_files.append(file);
        file->buildFileTree();
        m_opened_files_tree->addTopLevelItem(file->fileTree());
        m_close_file_action->setEnabled(true);
    }
}
void MainWindow::saveFile()
{
    //TODO
}

void MainWindow::closeFile()
{
    //TODO
    //If the file has not been saved, ask whether to do it
    QTreeWidgetItem *item = m_opened_files_tree->currentItem();
    qint32 index = m_opened_files_tree->indexOfTopLevelItem(item);
    delete m_opened_files_tree->takeTopLevelItem(index);
    for(QList<TiFile*>::iterator it=m_opened_files.begin(); it!=m_opened_files.end(); it++)
    {
        if((*it)->fileTree() == item)
        {
            delete *it;
            m_opened_files.erase(it);
            break;
        }
    }

    if(m_opened_files.isEmpty()) {
        m_close_file_action->setEnabled(false);
    }
}

void MainWindow::quit()
{
    //TODO
    while(!m_opened_files.isEmpty())
    {
        closeFile();
    }
    close();
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
