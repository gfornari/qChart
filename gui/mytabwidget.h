#ifndef MyTabWidget_H
#define MyTabWidget_H

#include <QTabWidget>
#include <QHBoxLayout>
#include <QGraphicsView>

#include "myhorizontallayoutwidget.h"

class MyTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit MyTabWidget(QWidget *parent = 0);
    
signals:
    void signalSaveAsFromCurrentTab();
    
public slots:
    void slotSaveAs();
    void slotOpen();
    void insertStarAfter();
    void removeStarAfter();
    void closeTab(int index);

    void slotBarchart();
    void slotLinechart();
    void slotPiechart();

private:
    void createConnections();

    MyHorizontalLayoutWidget *horizontalLayoutWidget;
};

#endif // MyTabWidget_H
