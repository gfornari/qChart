#ifndef LINECHART_H
#define LINECHART_H

#include <QPen>
#include <QGraphicsDropShadowEffect>

#include "chart.h"

class Linechart : public Chart
{
public:
    explicit Linechart(QVector<QString> colA, QVector<double> colB);
    
    void makeItems();
    QList<QGraphicsItem *> returnItems() const;
    void normalize(QVector<double> &vDouble, int norm);

    QVector<QString>& getColumnA();
    QVector<double>& getColumnB();
    QList<QGraphicsItem *> getItemList() const;

private:
    QVector<QString> columnA;
    QVector<double> columnB;

    QList<QGraphicsItem *> itemList;
};

#endif // LINECHART_H
