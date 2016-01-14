#ifndef MYTABLEWIDGET_H
#define MYTABLEWIDGET_H

#include <QTableWidget>
#include <QStringList>
#include <QDomDocument>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QKeyEvent>
#include <QDebug>
#include <QDoubleValidator>

class MyTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    MyTableWidget(QWidget *parent = 0);
    ~MyTableWidget();

    QVector<QString> getColumnString(int index = 0);
    QVector<double> getColumnDouble(int index = 1);

signals:
    void removeStar();
    void rowAdded();
    void rowDeleted();

public slots:
    QString saveXml() throw(QString);
    QString openXml() throw(QString);
    void addRowIfLast();
    void deleteRowSelected();
    void checkType(QTableWidgetItem * current, QTableWidgetItem * previous);

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    void setColumnLabels();

};

#endif // MYTABLEWIDGET_H
