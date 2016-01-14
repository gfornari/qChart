#include <QtGui>
#include <QDomDocument>
#include <QDomElement>
#include <QDebug>

#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    tabWidget = new MyTabWidget(this);
    toolbar = new QToolBar(this);

    QAction *iconNewtab = toolbar->addAction(QIcon(QPixmap(":/img/newtab.png")), tr("New tab"));
    QAction *iconOpen = toolbar->addAction(QIcon(QPixmap(":/img/open.png")), tr("Open..."));
    QAction *iconSaveAs = toolbar->addAction(QIcon(QPixmap(":/img/save.png")), tr("Save as..."));

    toolbar->addSeparator();

    QAction *iconBarchart = toolbar->addAction(QIcon(QPixmap(":/img/barchart.png")), tr("Barchart"));
    QAction *iconLinechart = toolbar->addAction(QIcon(QPixmap(":/img/linechart.png")), tr("Linechart"));
    QAction *iconPiechart = toolbar->addAction(QIcon(QPixmap(":/img/piechart.png")), tr("Piechart"));

    connect(iconNewtab, SIGNAL(triggered()), this, SLOT(newTab()));
    connect(iconOpen, SIGNAL(triggered()), this, SLOT(open()));
    connect(iconSaveAs, SIGNAL(triggered()), this, SLOT(saveAs()));
    connect(iconBarchart, SIGNAL(triggered()), this, SLOT(barchart()));
    connect(iconLinechart, SIGNAL(triggered()), this, SLOT(linechart()));
    connect(iconPiechart, SIGNAL(triggered()), this, SLOT(piechart()));

    createActions();
    createMenus();

    setCentralWidget(tabWidget);
    addToolBar(toolbar);

    setWindowTitle( tr("qChart") );
    resize(800, 700);
}

MainWindow::~MainWindow() {}

void MainWindow::newTab()
{
    MyHorizontalLayoutWidget *newTabLayout = new MyHorizontalLayoutWidget(tabWidget);
    tabWidget->addTab(newTabLayout, tr("New tab"));
    tabWidget->setCurrentWidget(newTabLayout);
}

void MainWindow::open()
{
    tabWidget->slotOpen();
}

void MainWindow::saveAs()
{
    tabWidget->slotSaveAs();
}

void MainWindow::barchart()
{
    tabWidget->slotBarchart();
}

void MainWindow::linechart()
{
    tabWidget->slotLinechart();

}

void MainWindow::piechart()
{
    tabWidget->slotPiechart();
}

void MainWindow::createActions()
{
    actionNewTab = new QAction( tr("New &Tab"), this);
    actionNewTab->setShortcut(QKeySequence::AddTab);
    connect(actionNewTab, SIGNAL(triggered()), this, SLOT(newTab()));

    actionOpen = new QAction( tr("&Open..."), this);
    actionOpen->setShortcut(QKeySequence::Open);
    connect(actionOpen, SIGNAL(triggered()), this, SLOT(open()));

    actionSaveAs = new QAction( tr("&Save As..."), this);
    actionSaveAs->setShortcut(QKeySequence::SaveAs);
    connect(actionSaveAs, SIGNAL(triggered()), this, SLOT(saveAs()));

    actionExit = new QAction( tr("E&xit"), this);
    actionExit->setShortcut(QKeySequence::Close);
    connect(actionExit, SIGNAL(triggered()), this, SLOT(close()));

    actionBarchart = new QAction( tr("&Barchart"), this);
    connect(actionBarchart, SIGNAL(triggered()), this, SLOT(barchart()));

    actionLinechart = new QAction( tr("&Linechart"), this);
    connect(actionLinechart, SIGNAL(triggered()), this, SLOT(linechart()));

    actionPiechart = new QAction( tr("&Piechart"), this);
    connect(actionPiechart, SIGNAL(triggered()), this, SLOT(piechart()));
}

void MainWindow::createMenus()
{
    menuFile = menuBar()->addMenu( tr("&File") );
    menuFile->addAction(actionNewTab);
    menuFile->addAction(actionOpen);
    menuFile->addAction(actionSaveAs);
    menuFile->addAction(actionExit);

    menuMake = menuBar()->addMenu( tr("&Make") );
    menuMake->addAction(actionBarchart);
    menuMake->addAction(actionLinechart);
    menuMake->addAction(actionPiechart);
}
