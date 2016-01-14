#include "mygraphicsellipseitem.h"

MyGraphicsEllipseItem::MyGraphicsEllipseItem(const QString &l, qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent) :
    label(new QGraphicsTextItem(l)), QGraphicsEllipseItem(x, y, width, height, parent)
{
    setAcceptsHoverEvents(true);

    setToolTip(label->toPlainText());
}

void MyGraphicsEllipseItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if(event->HoverEnter) {
        qDebug() << "hoverEnterEvent";
        setOpacity(0.7);
        label->show();
    }
}

void MyGraphicsEllipseItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    if(event->HoverLeave) {
        qDebug() << "hoverLeaveEvent";
        setOpacity(1);
        label->hide();
    }
}

