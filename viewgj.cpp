#include <QSqlQuery>
#include <QString>
#include <QDebug>
#include "viewgj.h"
#include "viewgjentry.h"

viewGJ::viewGJ(QDialog *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    QSqlQuery query;

    ui.tableWidget->clear();
    ui.tableWidget->setColumnCount(4);
    query.prepare("call getEntryGenDataList");
    query.exec();
    int row = 0;
    while (query.next())
    {
        ui.tableWidget->setRowCount(row+1);
        QString dateEvent = query.value(0).toString();
        QString entryCode = query.value(1).toString();
        QString memo = query.value(2).toString();
        QString datePosted = query.value(3).toString();
        QTableWidgetItem * item1 = new QTableWidgetItem(dateEvent);
        ui.tableWidget->setItem(row,0, item1);
        QTableWidgetItem * item2 = new QTableWidgetItem(entryCode);
        ui.tableWidget->setItem(row, 1, item2);
        QTableWidgetItem * item3 = new QTableWidgetItem(memo);
        ui.tableWidget->setItem(row, 2, item3);
        QTableWidgetItem * item4 = new QTableWidgetItem(datePosted);
        ui.tableWidget->setItem(row, 3, item4);
        row++;
    }
}

viewGJ::~viewGJ()
{
}

void viewGJ::on_pushButton_clicked()
{
    close();
}

void viewGJ::on_tableWidget_cellDoubleClicked(int row, int column)
{
    column = 1;
    //qDebug() << ui.tableWidget->item(row, column)->text();
    viewGJentry * viewEntry = new viewGJentry(ui.tableWidget->item(row, column)->text());
    viewEntry->exec();
}
