#include <QSqlQuery>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QSqlDriver>
#include <QDebug>
#include "viewgjentry.h"

viewGJentry::viewGJentry(QString entryCode, QDialog *parent)
        : QDialog(parent)
{
        ui.setupUi(this);
        if (entryCode == "")
        {
            m_search = true;
            ui.pushButton_2->setEnabled(false);
        }
        else
        {
            m_search = false;
            ui.pushButton_3->setEnabled(false);
            bool ret;
            QSqlQuery query, query1, query2, query3, query4;
            int row;

            ui.lineEdit->setText(entryCode);
            ui.lineEdit_2->setText("");
            ui.lineEdit_3->setText("");
            ui.lineEdit_4->setText("");
            ui.tableWidget->clear();
            ui.tableWidget_2->clear();
            ui.tableWidget_3->clear();
            ui.tableWidget_4->clear();
            ui.pushButton_2->setEnabled(false);
            query.prepare("call getEntryGenData(:entryCode)");
            query.bindValue(":entryCode", ui.lineEdit->text().toStdString().c_str());
            ret = query.exec();
            if (ret == true)
            {
                if (query.next())
                {
                    QString dateEvent = query.value(0).toString();
                    QString datePosted = query.value(1).toString();
                    QString description = query.value(2).toString();

                    ui.lineEdit_2->setText(dateEvent);
                    ui.lineEdit_3->setText(datePosted);
                    ui.lineEdit_4->setText(description);
                    query1.prepare("call getEntryAcctDebitData(:entryCode)");
                    query1.bindValue(":entryCode", ui.lineEdit->text().toStdString().c_str());
                    ret = query1.exec();
                    if (ret == true)
                    {
                        row = 0;
                        while (query1.next())
                        {
                            QString accountCode = query1.value(0).toString();
                            QString memo = query1.value(1).toString();
                            double amount = query1.value(2).toDouble();
                            QString amountStr = QString::number(amount, 'f', 2);

                            query2.prepare("call getAccountName(:accountCode)");
                            query2.bindValue(":accountCode", accountCode.toStdString().c_str());
                            query2.exec();
                            QString accountName;
                            while (query2.next())
                            {
                                accountName = query2.value(0).toString();
                            }

                            QTableWidgetItem * item1 = new QTableWidgetItem(accountName);
                            ui.tableWidget->setItem(row,0, item1);
                            QTableWidgetItem * item2 = new QTableWidgetItem(memo);
                            ui.tableWidget_2->setItem(row, 0, item2);
                            QTableWidgetItem * item3 = new QTableWidgetItem(amountStr);
                            item3->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
                            ui.tableWidget_3->setItem(row, 0, item3);
                            row++;
                        }
                        query3.prepare("call getEntryAcctCreditData(:entryCode)");
                        query3.bindValue(":entryCode", ui.lineEdit->text().toStdString().c_str());
                        ret = query3.exec();
                        if (ret == true)
                        {
                            while (query3.next())
                            {
                                QString accountCode = query3.value(0).toString();
                                QString memo = query3.value(1).toString();
                                double amount = query3.value(2).toDouble();
                                QString amountStr = QString::number(amount, 'f', 2);

                                query4.prepare("call getAccountName(:accountCode)");
                                query4.bindValue(":accountCode", accountCode.toStdString().c_str());
                                query4.exec();
                                QString accountName;
                                while (query4.next())
                                {
                                    accountName = query4.value(0).toString();
                                }

                                QTableWidgetItem * item1 = new QTableWidgetItem(accountName);
                                ui.tableWidget->setItem(row,0, item1);
                                QTableWidgetItem * item2 = new QTableWidgetItem(memo);
                                ui.tableWidget_2->setItem(row, 0, item2);
                                QTableWidgetItem * item3 = new QTableWidgetItem(amountStr);
                                item3->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
                                ui.tableWidget_4->setItem(row, 0, item3);
                                row++;
                            }
                            ui.pushButton_2->setEnabled(true);
                        }
                        else
                        {
                            QMessageBox::information(this, "Books - Bookkeeping Software", "Credit Accounts for the GJ entry not found.");
                        }
                    }
                    else
                    {
                        QMessageBox::information(this, "Books - Bookkeeping Software", "Debit Accounts for the GJ entry not found.");
                    }
                }
                else
                {
                    QMessageBox::information(this, "Books - Bookkeeping Software", "GJ entry not found.");
                }
            }
            else
            {
                QMessageBox::information(this, "Books - Bookkeeping Software", "Cannot access database. Please check.");
            }
        }
}

viewGJentry::~viewGJentry(void)
{
}

void viewGJentry::on_pushButton_clicked()
{
    ui.lineEdit->setText("");
    ui.lineEdit_2->setText("");
    ui.lineEdit_3->setText("");
    ui.lineEdit_4->setText("");
    ui.tableWidget->clear();
    ui.tableWidget_2->clear();
    ui.tableWidget_3->clear();
    ui.tableWidget_4->clear();
    close();
}

void viewGJentry::on_pushButton_3_clicked()
{
    bool ret;
    QSqlQuery query, query1, query2, query3, query4;
    int row;

    ui.lineEdit_2->setText("");
    ui.lineEdit_3->setText("");
    ui.lineEdit_4->setText("");
    ui.tableWidget->clear();
    ui.tableWidget_2->clear();
    ui.tableWidget_3->clear();
    ui.tableWidget_4->clear();
    ui.pushButton_2->setEnabled(false);
    query.prepare("call getEntryGenData(:entryCode)");
    query.bindValue(":entryCode", ui.lineEdit->text().toStdString().c_str());
    ret = query.exec();
    if (ret == true)
    {
        if (query.next())
        {
            QString dateEvent = query.value(0).toString();
            QString datePosted = query.value(1).toString();
            QString description = query.value(2).toString();

            ui.lineEdit_2->setText(dateEvent);
            ui.lineEdit_3->setText(datePosted);
            ui.lineEdit_4->setText(description);
            query1.prepare("call getEntryAcctDebitData(:entryCode)");
            query1.bindValue(":entryCode", ui.lineEdit->text().toStdString().c_str());
            ret = query1.exec();
            if (ret == true)
            {
                row = 0;
                while (query1.next())
                {
                    QString accountCode = query1.value(0).toString();
                    QString memo = query1.value(1).toString();
                    double amount = query1.value(2).toDouble();
                    QString amountStr = QString::number(amount, 'f', 2);

                    query2.prepare("call getAccountName(:accountCode)");
                    query2.bindValue(":accountCode", accountCode.toStdString().c_str());
                    query2.exec();
                    QString accountName;
                    while (query2.next())
                    {
                        accountName = query2.value(0).toString();
                    }

                    QTableWidgetItem * item1 = new QTableWidgetItem(accountName);
                    ui.tableWidget->setItem(row,0, item1);
                    QTableWidgetItem * item2 = new QTableWidgetItem(memo);
                    ui.tableWidget_2->setItem(row, 0, item2);
                    QTableWidgetItem * item3 = new QTableWidgetItem(amountStr);
                    item3->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
                    ui.tableWidget_3->setItem(row, 0, item3);
                    row++;
                }
                query3.prepare("call getEntryAcctCreditData(:entryCode)");
                query3.bindValue(":entryCode", ui.lineEdit->text().toStdString().c_str());
                ret = query3.exec();
                if (ret == true)
                {
                    while (query3.next())
                    {
                        QString accountCode = query3.value(0).toString();
                        QString memo = query3.value(1).toString();
                        double amount = query3.value(2).toDouble();
                        QString amountStr = QString::number(amount, 'f', 2);

                        query4.prepare("call getAccountName(:accountCode)");
                        query4.bindValue(":accountCode", accountCode.toStdString().c_str());
                        query4.exec();
                        QString accountName;
                        while (query4.next())
                        {
                            accountName = query4.value(0).toString();
                        }

                        QTableWidgetItem * item1 = new QTableWidgetItem(accountName);
                        ui.tableWidget->setItem(row,0, item1);
                        QTableWidgetItem * item2 = new QTableWidgetItem(memo);
                        ui.tableWidget_2->setItem(row, 0, item2);
                        QTableWidgetItem * item3 = new QTableWidgetItem(amountStr);
                        item3->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
                        ui.tableWidget_4->setItem(row, 0, item3);
                        row++;
                    }
                    ui.pushButton_2->setEnabled(true);
                }
                else
                {
                    QMessageBox::information(this, "Books - Bookkeeping Software", "Credit Accounts for the GJ entry not found.");
                }
            }
            else
            {
                QMessageBox::information(this, "Books - Bookkeeping Software", "Debit Accounts for the GJ entry not found.");
            }
        }
        else
        {
            QMessageBox::information(this, "Books - Bookkeeping Software", "GJ entry not found.");
        }
    }
    else
    {
        QMessageBox::information(this, "Books - Bookkeeping Software", "Cannot access database. Please check.");
    }
}

void viewGJentry::on_pushButton_2_clicked()
{
    bool ret = false;
    QSqlQuery query, query1, query2;
    bool transactionError = false;
    QSqlDriver * odbc;

    QSqlDatabase db = QSqlDatabase::database("QODBC");
    odbc = db.driver();
    bool transact = odbc->hasFeature(QSqlDriver::Transactions);

    QMessageBox::StandardButton answer = QMessageBox::question(this, "Books - Bookkeeping Software",
                             "If you click on the Yes button, the entry will be deleted.\nDo you REALLY want to do it?\nThis action is IRREVERSIBLE\n(well, unless someone enters data again, of course!)",
                             QMessageBox::Yes|QMessageBox::No,
                             QMessageBox::No);
    if (answer == QMessageBox::Yes)
    {
        QString entryCode = ui.lineEdit->text().toStdString().c_str();
        if (entryCode.size() > 0)
        {
            if (transact == true)
            {
                odbc->beginTransaction();
            }
            query.prepare("call deleteEntry(:entryCode)");
            query.bindValue(":entryCode", entryCode);
            ret = query.exec();
            if (ret == true)
            {
                query1.prepare("call deleteEntryDebit(:entryCode)");
                query1.bindValue(":entryCode", entryCode);
                ret = query1.exec();
                if (ret == true)
                {
                    query2.prepare("call deleteEntryCredit(:entryCode)");
                    query2.bindValue(":entryCode", entryCode);
                    ret = query2.exec();
                    if (ret == true)
                    {
                        QMessageBox::information(this, "Books - Bookkeeping Software", "GJ Entry deleted from the database.");
                        ui.lineEdit->setText("");
                        ui.lineEdit_2->setText("");
                        ui.lineEdit_3->setText("");
                        ui.lineEdit_4->setText("");
                        ui.tableWidget->clear();
                        ui.tableWidget_2->clear();
                        ui.tableWidget_3->clear();
                        ui.tableWidget_4->clear();
                        ui.pushButton_2->setEnabled(false);
                    }
                    else
                    {
                        transactionError = true;
                        QMessageBox::information(this, "Books - Bookkeeping Software", "Error in performing the deletion.\n Please check database status.");
                    }
                }
                else
                {
                    transactionError = true;
                    QMessageBox::information(this, "Books - Bookkeeping Software", "Error in performing the deletion.\n Please check database status.");
                }
            }
            else
            {
                transactionError = true;
                QMessageBox::information(this, "Books - Bookkeeping Software", "Error in performing the deletion.\n Please check database status.");
            }
            if (transactionError == false)
            {
                if (transact == true)
                {
                    //qDebug() << "COMMIT";
                    odbc->commitTransaction();
                }
            }
            else
            {
                if (transact == true)
                {
                    //qDebug() << "ROLLBACK";
                    odbc->rollbackTransaction();
                }
            }
        }
        else
        {
            QMessageBox::information(this, "Books - Bookkeeping Software", "GJ Entry field empty.\n Please check.");
        }
    }
}
