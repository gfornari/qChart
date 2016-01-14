#include "myhorizontallayoutwidget.h"

#include "mytabwidget.h"

MyHorizontalLayoutWidget::MyHorizontalLayoutWidget(QWidget *parent) :
    QWidget(parent)
{
    createObjects();
    createLayout();
    setLayout(horizontalLayout);

    connect(graphicsScene, SIGNAL(signalBarchart()), this, SLOT(createItemsForBarchart()));
    connect(graphicsScene, SIGNAL(signalLinechart()), this, SLOT(createItemsForLinechart()));
    connect(graphicsScene, SIGNAL(signalPiechart()), this, SLOT(createItemsForPiechart()));
    connect(tableWidget, SIGNAL(cellChanged(int,int)), dynamic_cast<MyTabWidget *>(parentWidget()), SLOT(insertStarAfter()));
    connect(tableWidget, SIGNAL(rowAdded()), dynamic_cast<MyTabWidget *>(parentWidget()), SLOT(insertStarAfter()));
    connect(tableWidget, SIGNAL(rowDeleted()), dynamic_cast<MyTabWidget *>(parentWidget()), SLOT(insertStarAfter()));
}

void MyHorizontalLayoutWidget::createObjects()
{
    tableWidget = new MyTableWidget(this);
    graphicsScene = new MyCustomScene();
    graphicsView = new QGraphicsView(graphicsScene, this);
    graphicsView->setRenderHint(QPainter::Antialiasing);
}

void MyHorizontalLayoutWidget::createLayout()
{
    horizontalLayout = new QHBoxLayout(this);

    horizontalLayout->addWidget(tableWidget, 0);
    horizontalLayout->addWidget(graphicsView, 4);
}

QString MyHorizontalLayoutWidget::slotSaveAsFromCurrentTab()
{
    try {
        return tableWidget->saveXml();
    } catch(QString err) {
        qDebug() << err;
        return "";
    }
}

QString MyHorizontalLayoutWidget::slotOpenOnNewTab()
{
    try {
        disconnect(tableWidget, SIGNAL(cellChanged(int,int)), dynamic_cast<MyTabWidget *>(parentWidget()), SLOT(insertStarAfter()));
        QString fileName = tableWidget->openXml();
        connect(tableWidget, SIGNAL(cellChanged(int,int)), dynamic_cast<MyTabWidget *>(parentWidget()), SLOT(insertStarAfter()));
        return fileName;
    } catch(QString err) {
        qDebug() << err;
        return "";
    }
}

void MyHorizontalLayoutWidget::slotBarchartFromCurrentTab()
{
    graphicsScene->createBarchart();
}

void MyHorizontalLayoutWidget::slotLinechartFromCurrentTab()
{
    graphicsScene->createLinechart();
}

void MyHorizontalLayoutWidget::slotPiechartFromCurrentTab()
{
    graphicsScene->createPiechart();
}

void MyHorizontalLayoutWidget::createItemsForBarchart()
{
    qDebug() << "createItemsForBarchart() called";

    chart = new Barchart(tableWidget->getColumnString(0), tableWidget->getColumnDouble(1));

    qDebug() << "barchart created";

    Barchart *barchart = dynamic_cast<Barchart*>(chart);
    if(barchart) {
        graphicsScene->addItems(barchart->getItemList());
        qDebug() << "items added to the scene";
    }

    delete chart;
}

void MyHorizontalLayoutWidget::createItemsForLinechart()
{
    qDebug() << "createItemsForLinechart() called";

    chart = new Linechart(tableWidget->getColumnString(0), tableWidget->getColumnDouble(1));

    qDebug() << "linechart created";

    Linechart *linechart = dynamic_cast<Linechart*>(chart);
    if(linechart) {
        graphicsScene->addItems(linechart->getItemList());
        qDebug() << "items added to the scene";
    }

    delete chart;
}

void MyHorizontalLayoutWidget::createItemsForPiechart()
{
    qDebug() << "createItemsForPiechart() called";

    QVector<double> columnB = tableWidget->getColumnDouble(1);

    bool zero = true;
    for(int i = 0; i < columnB.count() && zero; ++i) {
        if(columnB[i] != 0)
            zero = false;
    }

    if(!zero) {
        chart = new Piechart(tableWidget->getColumnString(0), columnB);

        qDebug() << "piechart created";

        Piechart *piechart = dynamic_cast<Piechart*>(chart);
        if(piechart) {
            graphicsScene->addItems(piechart->getItemList());
            qDebug() << "items added to the scene";
        }

        graphicsView->centerOn(165, -315);

        delete chart;
    }
}
