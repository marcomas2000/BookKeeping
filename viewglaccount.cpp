#include <QSqlQuery>
#include <QDebug>
#include <QFont>
#include "viewglaccount.h"

viewGLaccount::viewGLaccount(QList<QString> accountNames, QDialog *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    QList<QString>::iterator it;

    for (it = accountNames.begin(); it != accountNames.end(); it++)
    {
        ui.comboBox->addItem(*it);
    }
    //ui.comboBox->setCurrentIndex(-1);
}

viewGLaccount::~viewGLaccount(void)
{
}

void viewGLaccount::on_pushButton_clicked()
{
    ui.comboBox->setCurrentIndex(-1);
    ui.tableWidget->clear();
    close();
}

void viewGLaccount::on_comboBox_currentIndexChanged(QString acct)
{
    QSqlQuery query;
    QString accountCode;
    double saldo = 0.00;


    ui.tableWidget->clear();
    ui.tableWidget->setColumnCount(5);
    if (acct != "")
    {
        ui.comboBox->setEnabled(false);
        QSqlQuery getAcctCode;
        //qDebug() << ui.comboBox->currentText().toStdString().c_str();
        getAcctCode.prepare("call getAcctCodeFromDesc(:descr)");
        getAcctCode.bindValue(":descr", ui.comboBox->currentText().toStdString().c_str());
        getAcctCode.exec();
        while (getAcctCode.next())
        {
            accountCode = getAcctCode.value(0).toString();
        }

        query.prepare("call getAccountEntries(:accountCode)");
        query.bindValue(":accountCode", accountCode);
        query.exec();
        int row = 0;
        while (query.next())
        {
            ui.tableWidget->setRowCount(row+1);
            QString entryCode = query.value(0).toString();
            QString dateEvent = query.value(1).toString();
            QString CDflag = query.value(2).toString();
            QString memo = query.value(3).toString();
            double amount = query.value(4).toDouble();
            QString amountStr = QString::number(amount, 'f', 2);
            QTableWidgetItem * item1 = new QTableWidgetItem(entryCode);
            ui.tableWidget->setItem(row,0, item1);
            QTableWidgetItem * item2 = new QTableWidgetItem(dateEvent);
            ui.tableWidget->setItem(row,1, item2);
            QTableWidgetItem * item3 = new QTableWidgetItem(memo);
            ui.tableWidget->setItem(row,2, item3);
            QTableWidgetItem * item4 = new QTableWidgetItem(amountStr);
            item4->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
            if (CDflag == "D")
            {
                ui.tableWidget->setItem(row,3, item4);
                saldo += amountStr.toDouble();
            }
            else
            {
                ui.tableWidget->setItem(row,4, item4);
                saldo -= amountStr.toDouble();
            }
            //qDebug() << query.value(0).toString() << "-"
            //         << query.value(1).toString() << "-"
            //        << query.value(2).toString() << "-"
            //        << query.value(3).toString() << "-"
            //        << query.value(4).toString();
            row++;
        }
        ui.tableWidget->setRowCount(row+1);
        QTableWidgetItem * item5 = new QTableWidgetItem("Balance:");
        QFont fnt = item5->font();
        fnt.setBold(true);
        item5->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        item5->setFont(fnt);
        ui.tableWidget->setItem(row, 2, item5);
        if (saldo >= 0)
        {
            QString saldoStr = QString::number(saldo, 'f', 2);
            QTableWidgetItem * itSaldo = new QTableWidgetItem(saldoStr);
            QFont fnt2 = itSaldo->font();
            fnt2.setBold(true);
            itSaldo->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
            itSaldo->setFont(fnt2);
            ui.tableWidget->setItem(row, 4, itSaldo);
        }
        else
        {
            saldo = -saldo;
            QString saldoStr = QString::number(saldo, 'f', 2);
            QTableWidgetItem * itSaldo = new QTableWidgetItem(saldoStr);
            QFont fnt2 = itSaldo->font();
            fnt2.setBold(true);
            itSaldo->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
            itSaldo->setFont(fnt2);
            ui.tableWidget->setItem(row, 3, itSaldo);
        }
        ui.comboBox->setEnabled(true);
    }
}
