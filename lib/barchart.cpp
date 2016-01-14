#include "barchart.h"

Barchart::Barchart(QVector<QString> colA, QVector<double> colB) :
    columnA(colA), columnB(colB)
{
    normalize(getColumnB(), 480);

    qDebug() << "columnB normalized";

    makeItems();

    qDebug() << "items made";
}

void Barchart::makeItems()
{
    double max = 500; // max height of ax_Y

    int distanceBetweenBar = 20;
    int barWidth = 50;

    /* create axes */
    QGraphicsLineItem *ax_Y = new QGraphicsLineItem(0, -max, 0, 0);
    QGraphicsLineItem *ax_X = new QGraphicsLineItem(0, 0, columnB.size()*(distanceBetweenBar+barWidth) + barWidth, 0);
    for(int i=1; i<7; i++) {
        QGraphicsLineItem *line = new QGraphicsLineItem(-5, -80*i, columnB.size()*(distanceBetweenBar+barWidth) + barWidth, -80*i, ax_Y);
        line->setPen(QPen(Qt::DashLine));
    }
    itemList.append(ax_X);
    itemList.append(ax_Y);

    /* create bars and labels (like bars' childs), and append them to itemList */
    for(int i=0; i<columnB.size(); i++) {
        QGraphicsRectItem *rect = new QGraphicsRectItem(distanceBetweenBar*(i+1)+barWidth*i, -columnB[i], barWidth, columnB[i]);
        QGraphicsTextItem *text = new QGraphicsTextItem(columnA[i], rect);
        QColor color;
        color.setHsv(i*50, 240, 230);
        rect->setBrush(QBrush(color));
        text->setTextWidth(50);
        text->setHtml("<p align=center>" + columnA[i] + "</p>");
        text->setPos(distanceBetweenBar*(i+1)+barWidth*i, 10);
        itemList.append(rect);
    }
}

void Barchart::normalize(QVector<double>& vDouble, int norm)
{
    double max = findMax(vDouble);
    double scalar = norm/max;
    for(int i=0; i<vDouble.size(); i++)
        vDouble[i] = vDouble[i] * scalar;
}

QList<QGraphicsItem *> Barchart::returnItems() const
{
    QList<QGraphicsItem *> itemList;
    return itemList;
}

QVector<double>& Barchart::getColumnB()
{
    return columnB;
}

QList<QGraphicsItem *> Barchart::getItemList() const
{
    return itemList;
}
