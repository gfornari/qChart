#include "mytablewidget.h"

MyTableWidget::MyTableWidget(QWidget *parent) :
    QTableWidget(parent)
{
    setColumnCount(2);
    setRowCount(1);

    setColumnLabels();
    setColumnWidth(0, 118);
    setColumnWidth(1, 119);

    connect(this, SIGNAL(currentItemChanged(QTableWidgetItem*,QTableWidgetItem*)), this, SLOT(checkType(QTableWidgetItem*, QTableWidgetItem*)));
    connect(this, SIGNAL(removeStar()), parentWidget()->parentWidget(), SLOT(removeStarAfter()));
}

MyTableWidget::~MyTableWidget() {}

/* return a QVector<QString> of column index */
QVector<QString> MyTableWidget::getColumnString(int index)
{
    qDebug() << "getColumnString called";

    QVector<QString> v;
    v.resize(rowCount());
    for(int i=0; i<rowCount(); i++) {
        if(item(i, index))
            v[i] = item(i, index)->text();
        else
            v[i] = "";
    }

    qDebug() << "getColumnString finished";

    return v;
}

/* return a QVector<double> of column index */
QVector<double> MyTableWidget::getColumnDouble(int index)
{
    QVector<double> v;
    v.resize(rowCount());
    for(int i=0; i<rowCount(); i++) {
        if(item(i, index)) {
            if(item(i, index)->text() == "")
                v[i] = 0;
            else {
                QVariant val = item(i, index)->text();
                v[i] = val.toDouble();
                qDebug() << i << " = " << v[i];
            }
        } else
            v[i] = 0;
    }
    return v;
}

QString MyTableWidget::saveXml() throw(QString)
{
    if(rowCount() == 0) {
        QMessageBox::information(this, tr("qChart"), tr("Nothing to save."));
        throw QString("Nothing to save.");
    }

    QDomDocument doc;
    QDomElement root = doc.createElement("Table");
    doc.appendChild(root);

    /* Write column A */
    QDomElement colA = doc.createElement("ColumnA");
    for(int i=0; i<rowCount(); i++) {
        QDomElement rowI = doc.createElement("Row");
        if(item(i, 0)) {
            rowI.setAttribute("number", QString::number(i));
            rowI.setAttribute("value", item(i, 0)->text());
        } else {
            rowI.setAttribute("number", QString::number(i));
            rowI.setAttribute("value", "");
        }
        colA.appendChild(rowI);
    }
    root.appendChild(colA);

    /* Write column B */
    QDomElement colB = doc.createElement("ColumnB");
    for(int i=0; i<rowCount(); i++) {
        QDomElement rowI = doc.createElement("Row");
        if(item(i, 1)) {
            rowI.setAttribute("number", QString::number(i));
            rowI.setAttribute("value", item(i, 1)->text());
        } else {
            rowI.setAttribute("number", QString::number(i));
            rowI.setAttribute("value", "");
        }
        colB.appendChild(rowI);
    }
    root.appendChild(colB);

    QString name = QFileDialog::getSaveFileName(this, tr("Save file"), "/", tr("XML files (*.xml)"));
    if(!name.isEmpty()) {

        if(!name.endsWith(".xml"))
            name.append(".xml");

        QFile file(name);

        if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, tr("qChart"), tr("Cannot save the file."));
            throw QString("Cannot save the file.");
        } else {
            QTextStream stream(&file);
            stream << doc.toString();
            file.close();
            emit removeStar();

            QFileInfo fi(file);     // new fileName

            return fi.fileName();
        }
    }
    return "";
}

QString MyTableWidget::openXml() throw(QString)
{
    QDomDocument doc;
    QFile file(QFileDialog::getOpenFileName(this, tr("Open file"), "/", tr("XML files (*.xml)")));
    file.open(QIODevice::ReadOnly);
    if(file.fileName() == "")
        throw QString("Empty file name.");
    if (!doc.setContent(&file)) {
        QMessageBox::warning(this, tr("qChart"), tr("Cannot open the file."));
        file.close();
        throw QString("Cannot open the file.");
    }

    QDomElement root = doc.firstChildElement();
    QDomElement colA = root.firstChildElement();
    QDomElement colB = root.lastChildElement();
    QDomNodeList rowA = colA.elementsByTagName("Row");
    QDomNodeList rowB = colB.elementsByTagName("Row");

    clear();
    setRowCount(rowA.count());

    for(int i = 0; i<rowA.count(); i++) {
        QDomNode itemNode = rowA.at(i);
        if(itemNode.isElement()) {
            QDomElement itemElement = itemNode.toElement();
            setItem(i, 0, new QTableWidgetItem(itemElement.attribute("value")));
        }
    }

    for(int i = 0; i<rowB.count(); i++) {
        QDomNode itemNode = rowB.at(i);
        if(itemNode.isElement()) {
            QDomElement itemElement = itemNode.toElement();
            setItem(i, 1, new QTableWidgetItem(itemElement.attribute("value")));
        }
    }

    setColumnLabels();

    QFileInfo fi(file);

    return fi.fileName();
}

void MyTableWidget::addRowIfLast()
{
    if(this->currentRow() == this->rowCount()-1) {
        this->insertRow(this->rowCount());
        setCurrentCell(currentRow()+1, currentColumn());
        emit rowAdded();
    } else
        setCurrentCell(currentRow()+1, currentColumn());
}

void MyTableWidget::deleteRowSelected()
{
    if(rowCount() > 1) {
        removeRow(currentRow());
        emit rowDeleted();
    }
}

void MyTableWidget::checkType(QTableWidgetItem * current, QTableWidgetItem * previous)
{
    if(previous) {
        if(previous->column() == 1) {
            QDoubleValidator validator(this);
            validator.setBottom(0);
            validator.setNotation(QDoubleValidator::StandardNotation);
            qDebug() << "0";
            QString cellContent(previous->text());
            int pos = 0;
            qDebug() << "entered 1";
            if(!(validator.validate(cellContent, pos) == QValidator::Acceptable)) {
                previous->setText("");
                qDebug() << "entered 2";
            }
        }
    }
}

void MyTableWidget::keyPressEvent(QKeyEvent *event)
{
    QTableWidget::keyPressEvent(event);
    if(event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
        addRowIfLast();
    if(event->key() == Qt::Key_Delete)
        deleteRowSelected();
}

void MyTableWidget::setColumnLabels()
{
    QStringList *columnLabels = new QStringList();
    columnLabels->push_back("Labels");
    columnLabels->push_back("Values");
    setHorizontalHeaderLabels(*columnLabels);
}
