#ifndef MYCUSTOMSCENE_H
#define MYCUSTOMSCENE_H

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QDebug>

class MyCustomScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit MyCustomScene(QObject *parent = 0);

    void addItems(QList<QGraphicsItem *> itemList);
    
signals:
    void signalBarchart();
    void signalLinechart();
    void signalPiechart();
    
public slots:
    void createBarchart();
    void createLinechart();
    void createPiechart();

private:

};

#endif // MYCUSTOMSCENE_H
