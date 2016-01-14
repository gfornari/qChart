#include "piechart.h"

Piechart::Piechart(QVector<QString> colA, QVector<double> colB) :
    columnA(colA), columnB(colB)
{
    normalize(getColumnB(), 5760);  // 5760 is the span angle
    qDebug() << "columnB normalized";

    makeItems();
    qDebug() << "items made";
}

void Piechart::makeItems()
{
    if(columnB.size() == 1 && columnB[0]) {
        QGraphicsTextItem *tips = new QGraphicsTextItem();
        tips->setPos(55, -430);
        tips->setHtml("<p>To view the labels, keep the mouse cursor on the slices.</p>");

        MyGraphicsEllipseItem *pie = new MyGraphicsEllipseItem(columnA[0], 90, -390, 300, 300);

        QColor color;
        color.setHsv(0, 240, 230);
        pie->setBrush(QBrush(color));

        itemList.append(pie);
        itemList.append(tips);
    } else {
        QGraphicsTextItem *tips = new QGraphicsTextItem();
        tips->setHtml("<p>To view the labels, keep the mouse cursor on the slices.</p>");
        itemList.append(tips);

        double totalSpanAngle = 0;
        for(int i=0; i<columnB.size(); i++) {

            if(columnB[i]) {
                /* create slices */
                MyGraphicsEllipseItem *slice = new MyGraphicsEllipseItem(columnA[i], 90, -390, 300, 300);
                slice->setSpanAngle(columnB[i]);
                if(i != 0)
                    slice->setStartAngle(totalSpanAngle + 1);
                else
                    slice->setStartAngle(0);
                totalSpanAngle += columnB[i];

                /* set fill color */
                QColor color;
                color.setHsv(i*50, 240, 230);
                slice->setBrush(QBrush(color));

                itemList.append(slice);
            }
        }
    }
}

void Piechart::normalize(QVector<double>& vDouble, int norm)
{
    double sum = totalSum(vDouble);
    double scalar = norm/sum;
    for(int i=0; i<vDouble.size(); i++) {
        vDouble[i] = vDouble[i] * scalar;
    }
}

QList<QGraphicsItem *> Piechart::returnItems() const
{
    QList<QGraphicsItem *> itemList;
    return itemList;
}

QVector<double>& Piechart::getColumnB()
{
    return columnB;
}

QList<QGraphicsItem *> Piechart::getItemList() const
{
    return itemList;
}
