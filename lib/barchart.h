#ifndef BARCHART_H
#define BARCHART_H

#include <QDebug>
#include <QPen>
#include <QBrush>

#include "chart.h"

class Barchart : public Chart
{
public:
    explicit Barchart(QVector<QString> colA, QVector<double> colB);

    void makeItems();
    QList<QGraphicsItem *> returnItems() const;
    void normalize(QVector<double> &vDouble, int norm);

    QVector<double>& getColumnB();
    QList<QGraphicsItem *> getItemList() const;

private:
    QVector<QString> columnA;
    QVector<double> columnB;

    QList<QGraphicsItem *> itemList;
};

#endif // BARCHART_H
