#ifndef MYGRAPHICSELLIPSEITEM_H
#define MYGRAPHICSELLIPSEITEM_H

#include <QGraphicsEllipseItem>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsTextItem>
#include <QDebug>

class MyGraphicsEllipseItem : public QGraphicsEllipseItem
{
public:
    explicit MyGraphicsEllipseItem(const QString &l, qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = 0);

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

private:
    QGraphicsTextItem *label;
    
};

#endif // MYGRAPHICSELLIPSEITEM_H
