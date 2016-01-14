#ifndef PIECHART_H
#define PIECHART_H

#include <QDebug>
#include <QBrush>
#include <QColor>
#include <QGraphicsDropShadowEffect>

#include "chart.h"
#include "mygraphicsellipseitem.h"

class Piechart : public Chart
{
public:
    explicit Piechart(QVector<QString> colA, QVector<double> colB);
    
    void makeItems();
    QList<QGraphicsItem *> returnItems() const;
    void normalize(QVector<double>& vDouble, int norm);

    QVector<double>& getColumnB();
    QList<QGraphicsItem *> getItemList() const;

private:
    QVector<QString> columnA;
    QVector<double> columnB;

    QList<QGraphicsItem *> itemList;
};

#endif // PIECHART_H
