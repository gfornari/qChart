#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QStringList>
#include <QDebug>

#include "mytabwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void newTab();
    void open();
    void saveAs();

    void barchart();
    void linechart();
    void piechart();

signals:
    void signalSaveAs();

private:
    void createMenus();
    void createActions();

    QToolBar *toolbar;
    MyTabWidget *tabWidget;

    QMenu *menuFile;
    QMenu *menuMake;
    QAction *actionNewTab;
    QAction *actionOpen;
    QAction *actionSaveAs;
    QAction *actionExit;
    QAction *actionBarchart;
    QAction *actionLinechart;
    QAction *actionPiechart;
};

#endif // MAINWINDOW_H
