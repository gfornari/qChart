#include "mytabwidget.h"

MyTabWidget::MyTabWidget(QWidget *parent) :
    QTabWidget(parent)
{
    horizontalLayoutWidget = new MyHorizontalLayoutWidget(this);

    addTab(horizontalLayoutWidget, tr("New tab"));
    setTabsClosable(true);
    setMovable(true);

    createConnections();
}

void MyTabWidget::slotSaveAs()
{
    QWidget *currentTab = currentWidget();
    MyHorizontalLayoutWidget *currentLayoutWidget = dynamic_cast<MyHorizontalLayoutWidget*>(currentTab);
    if(currentLayoutWidget) {
        QString fileName = currentLayoutWidget->slotSaveAsFromCurrentTab();
        if(fileName != "")
            setTabText(currentIndex(), fileName);
    }
}

void MyTabWidget::slotOpen()
{
    MyHorizontalLayoutWidget *openHorizontalLayoutWidget = new MyHorizontalLayoutWidget(this);
    QString fileName = openHorizontalLayoutWidget->slotOpenOnNewTab();
    if(fileName != "") {
        addTab(openHorizontalLayoutWidget, fileName);
        setCurrentWidget(openHorizontalLayoutWidget);
    }
}

void MyTabWidget::closeTab(int index)
{
    if(tabText(index).endsWith("*")) {
        QMessageBox msgBox;
        msgBox.setText("The document has been modified.");
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        switch (ret) {
            case QMessageBox::Save:
                slotSaveAs();
                break;
            case QMessageBox::Discard:
                removeTab(index);
                break;
            case QMessageBox::Cancel:
                // Cancel was clicked, do nothing
                break;
            default:
                // should never be reached
                break;
         }
    } else
        removeTab(index);
}

/* add "*" at the end of the current tab's text */
void MyTabWidget::insertStarAfter()
{
    if(!tabText(currentIndex()).endsWith("*"))
        setTabText(currentIndex(), tabText(currentIndex()) + QString("*"));
}

/* remove "*" from the end of the current tab's text (if there is) */
void MyTabWidget::removeStarAfter()
{
    if(tabText(currentIndex()).endsWith("*")) {
        QString textForTabSaved = tabText(currentIndex());
        textForTabSaved.chop(1);
        setTabText(currentIndex(), textForTabSaved);
    }
}

void MyTabWidget::slotBarchart()
{
    QWidget *currentTab = currentWidget();
    MyHorizontalLayoutWidget *currentLayoutWidget = dynamic_cast<MyHorizontalLayoutWidget*>(currentTab);
    if(currentLayoutWidget)
        currentLayoutWidget->slotBarchartFromCurrentTab();
}

void MyTabWidget::slotLinechart()
{
    QWidget *currentTab = currentWidget();
    MyHorizontalLayoutWidget *currentLayoutWidget = dynamic_cast<MyHorizontalLayoutWidget*>(currentTab);
    if(currentLayoutWidget)
        currentLayoutWidget->slotLinechartFromCurrentTab();
}

void MyTabWidget::slotPiechart()
{
    QWidget *currentTab = currentWidget();
    MyHorizontalLayoutWidget *currentLayoutWidget = dynamic_cast<MyHorizontalLayoutWidget*>(currentTab);
    if(currentLayoutWidget)
        currentLayoutWidget->slotPiechartFromCurrentTab();
}

void MyTabWidget::createConnections()
{
    connect(parentWidget(), SIGNAL(signalSaveAs()), currentWidget(), SLOT(slotSaveAsFromCurrentTab()));
    connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
}
