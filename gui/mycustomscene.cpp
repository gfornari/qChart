#include "mycustomscene.h"

MyCustomScene::MyCustomScene(QObject *parent) :
    QGraphicsScene(parent)
{
    QGraphicsTextItem *tips = new QGraphicsTextItem();
    tips->setHtml("<p>For all the charts, insert the labels in the column A and the values (positive numbers) in the column B. </p>");
    addItem(tips);
}

void MyCustomScene::createBarchart()
{
    clear();
    update();
    emit signalBarchart();
}

void MyCustomScene::createLinechart()
{
    clear();
    update();
    emit signalLinechart();

}

void MyCustomScene::createPiechart()
{
    clear();
    update();
    emit signalPiechart();
}

void MyCustomScene::addItems(QList<QGraphicsItem *> itemList)
{
    for(int i=0; i < itemList.count(); i++) {
        addItem(itemList[i]);
    }
}
