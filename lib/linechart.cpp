#include "linechart.h"

Linechart::Linechart(QVector<QString> colA, QVector<double> colB) :
    columnA(colA), columnB(colB)
{
    normalize(getColumnB(), 480);
    qDebug() << "columnB normalized";

    makeItems();
    qDebug() << "items made";
}

void Linechart::makeItems()
{
    double max_Y = 500;

    int distanceBetweenValues = 70;

    /* create axes */
    QGraphicsLineItem *ax_Y = new QGraphicsLineItem(0, -max_Y, 0, 0);
    QGraphicsLineItem *ax_X = new QGraphicsLineItem(0, 0, columnB.size()*distanceBetweenValues, 0);
    QGraphicsLineItem *arrow1_ax_Y = new QGraphicsLineItem(-5, -max_Y+5, 0, -max_Y-1, ax_Y);
    QGraphicsLineItem *arrow2_ax_Y = new QGraphicsLineItem(0, -max_Y-1, 5, -max_Y+5, ax_Y);
    QGraphicsLineItem *arrow1_ax_X = new QGraphicsLineItem(columnB.size()*distanceBetweenValues-5, -5, columnB.size()*distanceBetweenValues+1, 0, ax_X);
    QGraphicsLineItem *arrow2_ax_X = new QGraphicsLineItem(columnB.size()*distanceBetweenValues+1, 0, columnB.size()*distanceBetweenValues-5, 5, ax_X);

    /* create grid */
    for(int i=1; i<7; i++) {
        QGraphicsLineItem *line = new QGraphicsLineItem(-5, -80*i, columnB.size()*distanceBetweenValues, -80*i, ax_Y);
        line->setPen(QPen(Qt::DashLine));
    }
    itemList.append(ax_X);
    itemList.append(ax_Y);

    /* create line and labels */
    if(columnA.size() == 1) {
        QGraphicsLineItem *line = new QGraphicsLineItem(0, -columnB[0], 1, -columnB[0]);
        QPen *pen = new QPen(Qt::red, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        line->setPen(*pen);

        QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
        shadow->setBlurRadius(5);
        shadow->setColor(QColor(63, 63, 63, 130));
        shadow->setOffset(2);
        line->setGraphicsEffect(shadow);

        QGraphicsTextItem *label = new QGraphicsTextItem(columnA[0]);
        label->setTextWidth(distanceBetweenValues);
        label->setHtml("<p align=center>" + columnA[0] + "</p>");
        label->setPos(-(distanceBetweenValues/2), 10);

        QGraphicsLineItem *mark = new QGraphicsLineItem(0, 0, 0, 5);
        itemList.append(line);
        itemList.append(label);
        itemList.append(mark);
    } else {
        for(int i=0; i<columnA.size()-1; i++) {
            QGraphicsLineItem *line = new QGraphicsLineItem(i*distanceBetweenValues, -columnB[i], (i+1)*distanceBetweenValues, -columnB[i+1]);
            QPen *pen = new QPen(Qt::red, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
            line->setPen(*pen);

            QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
            shadow->setBlurRadius(5);
            shadow->setColor(QColor(63, 63, 63, 130));
            shadow->setOffset(2);
            line->setGraphicsEffect(shadow);

            QGraphicsTextItem *label = new QGraphicsTextItem(columnA[i]);
            label->setTextWidth(distanceBetweenValues);
            label->setHtml("<p align=center>" + columnA[i] + "</p>");
            label->setPos(distanceBetweenValues*i-(distanceBetweenValues/2), 10);

            QGraphicsLineItem *mark = new QGraphicsLineItem(distanceBetweenValues*i, 0, distanceBetweenValues*i, 5);
            itemList.append(line);
            itemList.append(label);
            itemList.append(mark);
        }

        /* create last label */
        QGraphicsTextItem *label = new QGraphicsTextItem(columnA.last());
        label->setTextWidth(distanceBetweenValues);
        label->setHtml("<p align=center>" + columnA.last() + "</p>");
        label->setPos(distanceBetweenValues*(columnA.size()-1)-(distanceBetweenValues/2), 10);

        QGraphicsLineItem *mark = new QGraphicsLineItem(distanceBetweenValues*(columnA.size()-1), 0, distanceBetweenValues*(columnA.size()-1), 5);
        itemList.append(label);
        itemList.append(mark);
    }
}

void Linechart::normalize(QVector<double>& vDouble, int norm)
{
    double max = findMax(vDouble);
    double scalar = norm/max;
    for(int i=0; i<vDouble.size(); i++)
        vDouble[i] = vDouble[i] * scalar;
}

QList<QGraphicsItem *> Linechart::returnItems() const
{
    QList<QGraphicsItem *> itemList;
    return itemList;
}

QVector<QString>& Linechart::getColumnA()
{
    return columnA;
}

QVector<double>& Linechart::getColumnB()
{
    return columnB;
}

QList<QGraphicsItem *> Linechart::getItemList() const
{
    return itemList;
}
