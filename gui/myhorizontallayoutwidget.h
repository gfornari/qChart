#ifndef MYHORIZONTALLAYOUTWIDGET_H
#define MYHORIZONTALLAYOUTWIDGET_H

#include <QHBoxLayout>
#include <QGraphicsView>
#include <QDebug>

#include "mytablewidget.h"
#include "mycustomscene.h"
#include "barchart.h"
#include "piechart.h"
#include "linechart.h"

class MyHorizontalLayoutWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyHorizontalLayoutWidget(QWidget *parent = 0);

signals:
    
public slots:
    QString slotSaveAsFromCurrentTab();
    QString slotOpenOnNewTab();

    void slotBarchartFromCurrentTab();
    void slotLinechartFromCurrentTab();
    void slotPiechartFromCurrentTab();

    void createItemsForBarchart();
    void createItemsForLinechart();
    void createItemsForPiechart();

private:
    void createObjects();
    void createLayout();

    QHBoxLayout *horizontalLayout;

    MyTableWidget *tableWidget;
    MyCustomScene *graphicsScene;
    QGraphicsView *graphicsView;

    Chart *chart;
};

#endif // MYHORIZONTALLAYOUTWIDGET_H
