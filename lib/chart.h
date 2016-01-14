#ifndef CHART_H
#define CHART_H

#include <QObject>
#include <QGraphicsItem>
#include <QDebug>

class Chart
{
public:
    explicit Chart();
    virtual ~Chart();

    virtual void makeItems() = 0;
    virtual QList<QGraphicsItem *> returnItems() const = 0;
    virtual void normalize(QVector<double>& vDouble, int norm = 1) = 0;

protected:
    double findMax(QVector<double>& v) const;
    double totalSum(QVector<double>& v) const;
};

#endif // CHART_H
