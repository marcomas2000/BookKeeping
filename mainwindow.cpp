#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QDateTime>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QSqlError>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
     m_sumCredit(0.00), m_sumDebit(0.00)
{
    ui->setupUi(this);
    ui->lineEdit->setMaxLength(6);
    ui->lineEdit_2->setMaxLength(200);
    ui->dateEdit->setDisplayFormat("yyyy-MM-dd");
    ui->dateEdit_2->setDisplayFormat("yyyy-MM-dd");
    ui->dateEdit->setDate(QDateTime::currentDateTime().date());
    ui->dateEdit_2->setDate(QDateTime::currentDateTime().date());
    ui->pushButton_2->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::on_actionExit_triggered()
{
    m_db.close();
    close();
}

void MainWindow::on_actionOpen_triggered()
{
    bool ret;

    m_db = QSqlDatabase::addDatabase("QODBC");
    //qDebug() << "Drivers: " << m_db.drivers();
    QSettings odbcConnData("books.ini", QSettings::IniFormat);

    m_db.setHostName(odbcConnData.value("ODBC_Connection/hostName", "localhost").toString());
    m_db.setUserName(odbcConnData.value("ODBC_Connection/userName").toString());
    m_db.setPassword(odbcConnData.value("ODBC_Connection/password").toString());
    m_db.setDatabaseName(odbcConnData.value("ODBC_Connection/databaseName").toString());
    bool ok = m_db.open();
    if (ok == true)
    {
        QSqlQuery query;
        query.prepare("call getAccountDesc");
        ret = query.exec();
        if (ret == true)
        {
            while (query.next())
            {
                QString accountDescription = query.value(0).toString();
                ui->comboBox->addItem(accountDescription);
                ui->comboBox_2->addItem(accountDescription);
                ui->comboBox_3->addItem(accountDescription);
                ui->comboBox_4->addItem(accountDescription);
                ui->comboBox_5->addItem(accountDescription);
                m_accountNames.append(accountDescription);
            }
            ui->pushButton_2->setEnabled(true);
            ui->actionOpen->setEnabled(false);
            ui->actionView_GJ_Entry->setEnabled(true);
            ui->actionView_GL_Account->setEnabled(true);
            ui->actionView_GJ->setEnabled(true);
            ui->comboBox->setCurrentIndex(-1);
            ui->comboBox_2->setCurrentIndex(-1);
            ui->comboBox_3->setCurrentIndex(-1);
            ui->comboBox_4->setCurrentIndex(-1);
            ui->comboBox_5->setCurrentIndex(-1);
            QMessageBox::information(this, "Books - Bookkeeping Software", "Connected to remote database");
        }
        else
        {
            QMessageBox::information(this, "Books - Bookkeeping Software", "Could not execute query");
        }
    }
    else
    {
        qDebug() << "Error:" << m_db.lastError().text();
        QMessageBox::critical(this, "Books - Bookkeeping Software", "Not connected to remote database");
    }
}

void MainWindow::on_actionAbout_Books_triggered()
{
    QMessageBox::information(this, "Books - Bookkeeping Software", "Books\n\nCopyright 2010-2011, Methos Consulting Ltd");
}

void MainWindow::on_pushButton_2_clicked()
{
    // Check before submiting data
    m_sumDebit = 0.00;
    m_sumCredit = 0.00;
    //qDebug() << "Entry Code:" << ui->lineEdit->text().toStdString().c_str();
    //qDebug() << "Date Posted:" << ui->dateEdit->text().toStdString().c_str();
    //qDebug() << "Date Event:" << ui->dateEdit_2->text().toStdString().c_str();
    //qDebug() << "Description:" << ui->lineEdit_2->text().toStdString().c_str();
    if ((ui->doubleSpinBox->value() > 0.0) && (ui->comboBox->currentIndex() != -1))
    {
        //qDebug() << "1-Debit" << ui->doubleSpinBox->value();
        m_sumDebit += ui->doubleSpinBox->value();
    }
    if ((ui->doubleSpinBox_5->value() > 0.0) && (ui->comboBox_2->currentIndex() != -1))
    {
        //qDebug() << "2-Debit" << ui->doubleSpinBox_5->value();
        m_sumDebit += ui->doubleSpinBox_5->value();
    }
    if ((ui->doubleSpinBox_6->value() > 0.0) && (ui->comboBox_3->currentIndex() != -1))
    {
        //qDebug() << "3-Debit" << ui->doubleSpinBox_6->value();
        m_sumDebit += ui->doubleSpinBox_6->value();
    }
    if ((ui->doubleSpinBox_8->value() > 0.0) && (ui->comboBox_4->currentIndex() != -1))
    {
        //qDebug() << "4-Debit" << ui->doubleSpinBox_8->value();
        m_sumDebit += ui->doubleSpinBox_8->value();
    }
    if ((ui->doubleSpinBox_10->value() > 0.0) && (ui->comboBox_5->currentIndex() != -1))
    {
        //qDebug() << "5-Debit" << ui->doubleSpinBox_10->value();
        m_sumDebit += ui->doubleSpinBox_8->value();
    }
    if ((ui->doubleSpinBox_2->value() > 0.0) && (ui->comboBox->currentIndex() != -1))
    {
        //qDebug() << "1-Credit" << ui->doubleSpinBox_2->value();
        m_sumCredit += ui->doubleSpinBox_2->value();
    }
    if ((ui->doubleSpinBox_4->value() > 0.0) && (ui->comboBox_2->currentIndex() != -1))
    {
        //qDebug() << "2-Credit" << ui->doubleSpinBox_4->value();
        m_sumCredit += ui->doubleSpinBox_4->value();
    }
    if ((ui->doubleSpinBox_7->value() > 0.0) && (ui->comboBox_3->currentIndex() != -1))
    {
        //qDebug() << "3-Credit" << ui->doubleSpinBox_7->value();
        m_sumCredit += ui->doubleSpinBox_7->value();
    }
    if ((ui->doubleSpinBox_9->value() > 0.0) && (ui->comboBox_4->currentIndex() != -1))
    {
        //qDebug() << "4-Credit" << ui->doubleSpinBox_9->value();
        m_sumCredit += ui->doubleSpinBox_9->value();
    }
    if ((ui->doubleSpinBox_11->value() > 0.0) && (ui->comboBox_5->currentIndex() != -1))
    {
        //qDebug() << "5-Credit" << ui->doubleSpinBox_11->value();
        m_sumCredit += ui->doubleSpinBox_11->value();
    }
    if (m_sumDebit != m_sumCredit)
    {
        QMessageBox::information(this, "Books - Bookkeeping Software", "The amounts in Debit in Credit do not balance.\n Please check.");
    }
    else
    {
        if (ui->lineEdit->text() == "")
        {
            QMessageBox::information(this, "Books - Bookkeeping Software", "Please enter a value for the Entry No.");
        }
        else
        {
            if (ui->lineEdit_2->text() == "")
            {
                QMessageBox::StandardButton answer = QMessageBox::question(this, "Books - Bookkeeping Software",
                                         "Description has not been entered.\nPlease consider entering it.\nDo you want to do it?",
                                         QMessageBox::Yes|QMessageBox::No,
                                         QMessageBox::Yes);
                if (answer == QMessageBox::No)
                {
                    // write records
                    if (submitEntry() == true)
                    {
                        QMessageBox::information(this, "Books - Bookkeeping Software", "Entry submitted. Insertion confirmed.");
                        clearForm();
                    }
                    else
                    {
                        QMessageBox::information(this, "Books - Bookkeeping Software", "Error occurred on the database. Entry not inserted.\nDuplicate Entry No.?");
                    }
                }
            }
            else
            {
                // write records
                if (submitEntry() == true)
                {
                    QMessageBox::information(this, "Books - Bookkeeping Software", "Entry submitted. Insertion confirmed.");
                    clearForm();
                }
                else
                {
                    QMessageBox::information(this, "Books - Bookkeeping Software", "Error occurred on the database. Entry not inserted.\nDuplicate Entry No.?");
                }
            }
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    // clean form
    clearForm();
}

void MainWindow::on_checkBox_stateChanged(int state)
{
    if (state == Qt::Checked)
    {
        if (ui->comboBox->currentIndex() != -1)
        {
            ui->lineEdit_3->setText(ui->lineEdit_2->text());
        }
        if (ui->comboBox_2->currentIndex() != -1)
        {
            ui->lineEdit_4->setText(ui->lineEdit_2->text());
        }
        if (ui->comboBox_3->currentIndex() != -1)
        {
            ui->lineEdit_5->setText(ui->lineEdit_2->text());
        }
        if (ui->comboBox_4->currentIndex() != -1)
        {
            ui->lineEdit_6->setText(ui->lineEdit_2->text());
        }
        if (ui->comboBox_5->currentIndex() != -1)
        {
            ui->lineEdit_7->setText(ui->lineEdit_2->text());
        }
    }
    else
    {
        ui->lineEdit_3->setText("");
        ui->lineEdit_4->setText("");
        ui->lineEdit_5->setText("");
        ui->lineEdit_6->setText("");
        ui->lineEdit_7->setText("");
    }
}

void MainWindow::clearForm()
{
    ui->lineEdit->setText("");
    ui->dateEdit->setDate(QDateTime::currentDateTime().date());
    ui->dateEdit_2->setDate(QDateTime::currentDateTime().date());
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");
    ui->lineEdit_4->setText("");
    ui->lineEdit_5->setText("");
    ui->lineEdit_6->setText("");
    ui->lineEdit_7->setText("");
    ui->doubleSpinBox->setValue(0.00);
    ui->doubleSpinBox_2->setValue(0.00);
    ui->doubleSpinBox_4->setValue(0.00);
    ui->doubleSpinBox_5->setValue(0.00);
    ui->doubleSpinBox_6->setValue(0.00);
    ui->doubleSpinBox_7->setValue(0.00);
    ui->doubleSpinBox_8->setValue(0.00);
    ui->doubleSpinBox_9->setValue(0.00);
    ui->doubleSpinBox_10->setValue(0.00);
    ui->doubleSpinBox_11->setValue(0.00);
    ui->comboBox->setCurrentIndex(-1);
    ui->comboBox_2->setCurrentIndex(-1);
    ui->comboBox_3->setCurrentIndex(-1);
    ui->comboBox_4->setCurrentIndex(-1);
    ui->comboBox_5->setCurrentIndex(-1);
    ui->checkBox->setCheckState(Qt::Unchecked);
    m_sumDebit = 0.00;
    m_sumCredit = 0.00;
}

bool MainWindow::submitEntry()
{
    bool ret = false;
    QSqlQuery query;
    QSqlQuery acct1, acct2, acct3, acct4, acct5;
    QString accountCode;
    QSqlDriver * odbc;
    bool transactionError = false;

    odbc = m_db.driver();
    bool transact = odbc->hasFeature(QSqlDriver::Transactions);
    //qDebug() << "Are transactions available?" << transact;
    if (transact == true)
    {
        odbc->beginTransaction();
    }
    query.prepare("call insertEntry(:entryCode, :descr, :datePosted, :dateEvent)");
    query.bindValue(":entryCode", ui->lineEdit->text().toStdString().c_str());
    query.bindValue(":descr", ui->lineEdit_2->text().toStdString().c_str());
    query.bindValue(":datePosted",ui->dateEdit->text().toStdString().c_str());
    query.bindValue(":dateEvent",ui->dateEdit_2->text().toStdString().c_str());
    //qDebug() << query.lastQuery().toStdString().c_str();
    ret = query.exec();

    if (ret == true)
    {
        if (ui->comboBox->currentIndex() != -1)
        {
            QSqlQuery getAcctCode;
            //qDebug() << ui->comboBox->currentText().toStdString().c_str();
            getAcctCode.prepare("call getAcctCodeFromDesc(:descr)");
            getAcctCode.bindValue(":descr", ui->comboBox->currentText().toStdString().c_str());
            getAcctCode.exec();
            while (getAcctCode.next())
            {
                accountCode = getAcctCode.value(0).toString();
            }
            if (ui->doubleSpinBox->value() > 0.0)
            {
                acct1.prepare("call insertEntryAcctDeb(:entryCode, :acctCode, :amount, :memo)");
                acct1.bindValue(":entryCode", ui->lineEdit->text().toStdString().c_str());
                acct1.bindValue(":acctCode", accountCode);
                acct1.bindValue(":amount",ui->doubleSpinBox->value());
                acct1.bindValue(":memo", ui->lineEdit_3->text().toStdString().c_str());
                ret = acct1.exec();
                if (ret != true)
                {
                    transactionError = true;
                }
            }
            else
            {
                if (ui->doubleSpinBox_2->value() > 0.0)
                {
                    acct1.prepare("call insertEntryAcctCred(:entryCode, :acctCode, :amount, :memo)");
                    acct1.bindValue(":entryCode", ui->lineEdit->text().toStdString().c_str());
                    acct1.bindValue(":acctCode", accountCode);
                    acct1.bindValue(":amount",ui->doubleSpinBox_2->value());
                    acct1.bindValue(":memo", ui->lineEdit_3->text().toStdString().c_str());
                    ret = acct1.exec();
                    if (ret != true)
                    {
                        transactionError = true;
                    }
                }
            }
        }
        if (ui->comboBox_2->currentIndex() != -1)
        {
            QSqlQuery getAcctCode;
            //qDebug() << ui->comboBox_2->currentText().toStdString().c_str();
            getAcctCode.prepare("call getAcctCodeFromDesc(:descr)");
            getAcctCode.bindValue(":descr", ui->comboBox_2->currentText().toStdString().c_str());
            getAcctCode.exec();
            while (getAcctCode.next())
            {
                accountCode = getAcctCode.value(0).toString();
            }
            if (ui->doubleSpinBox_5->value() > 0.0)
            {
                acct2.prepare("call insertEntryAcctDeb(:entryCode, :acctCode, :amount, :memo)");
                acct2.bindValue(":entryCode", ui->lineEdit->text().toStdString().c_str());
                acct2.bindValue(":acctCode", accountCode);
                acct2.bindValue(":amount",ui->doubleSpinBox_5->value());
                acct2.bindValue(":memo", ui->lineEdit_4->text().toStdString().c_str());
                ret = acct2.exec();
                if (ret != true)
                {
                    transactionError = true;
                }
            }
            else
            {
                if (ui->doubleSpinBox_4->value() > 0.0)
                {
                    acct2.prepare("call insertEntryAcctCred(:entryCode, :acctCode, :amount, :memo)");
                    acct2.bindValue(":entryCode", ui->lineEdit->text().toStdString().c_str());
                    acct2.bindValue(":acctCode", accountCode);
                    acct2.bindValue(":amount",ui->doubleSpinBox_4->value());
                    acct2.bindValue(":memo", ui->lineEdit_4->text().toStdString().c_str());
                    ret = acct2.exec();
                    if (ret != true)
                    {
                        transactionError = true;
                    }
                }
            }
        }
        if (ui->comboBox_3->currentIndex() != -1)
        {
            QSqlQuery getAcctCode;
            //qDebug() << ui->comboBox_3->currentText().toStdString().c_str();
            getAcctCode.prepare("call getAcctCodeFromDesc(:descr)");
            getAcctCode.bindValue(":descr", ui->comboBox_3->currentText().toStdString().c_str());
            getAcctCode.exec();
            while (getAcctCode.next())
            {
                accountCode = getAcctCode.value(0).toString();
            }
            if (ui->doubleSpinBox_6->value() > 0.0)
            {
                acct3.prepare("call insertEntryAcctDeb(:entryCode, :acctCode, :amount, :memo)");
                acct3.bindValue(":entryCode", ui->lineEdit->text().toStdString().c_str());
                acct3.bindValue(":acctCode", accountCode);
                acct3.bindValue(":amount",ui->doubleSpinBox_6->value());
                acct3.bindValue(":memo", ui->lineEdit_5->text().toStdString().c_str());
                ret = acct3.exec();
                if (ret != true)
                {
                    transactionError = true;
                }
            }
            else
            {
                if (ui->doubleSpinBox_7->value() > 0.0)
                {
                    acct3.prepare("call insertEntryAcctCred(:entryCode, :acctCode, :amount, :memo)");
                    acct3.bindValue(":entryCode", ui->lineEdit->text().toStdString().c_str());
                    acct3.bindValue(":acctCode", accountCode);
                    acct3.bindValue(":amount",ui->doubleSpinBox_7->value());
                    acct3.bindValue(":memo", ui->lineEdit_5->text().toStdString().c_str());
                    ret = acct3.exec();
                    if (ret != true)
                    {
                        transactionError = true;
                    }
                }
            }
        }
        if (ui->comboBox_4->currentIndex() != -1)
        {
            QSqlQuery getAcctCode;
            //qDebug() << ui->comboBox_4->currentText().toStdString().c_str();
            getAcctCode.prepare("call getAcctCodeFromDesc(:descr)");
            getAcctCode.bindValue(":descr", ui->comboBox_4->currentText().toStdString().c_str());
            getAcctCode.exec();
            while (getAcctCode.next())
            {
                accountCode = getAcctCode.value(0).toString();
            }
            if (ui->doubleSpinBox_8->value() > 0.0)
            {
                acct4.prepare("call insertEntryAcctDeb(:entryCode, :acctCode, :amount, :memo)");
                acct4.bindValue(":entryCode", ui->lineEdit->text().toStdString().c_str());
                acct4.bindValue(":acctCode", accountCode);
                acct4.bindValue(":amount",ui->doubleSpinBox_8->value());
                acct4.bindValue(":memo", ui->lineEdit_6->text().toStdString().c_str());
                ret = acct4.exec();
                if (ret != true)
                {
                    transactionError = true;
                }
            }
            else
            {
                if (ui->doubleSpinBox_9->value() > 0.0)
                {
                    acct4.prepare("call insertEntryAcctCred(:entryCode, :acctCode, :amount, :memo)");
                    acct4.bindValue(":entryCode", ui->lineEdit->text().toStdString().c_str());
                    acct4.bindValue(":acctCode", accountCode);
                    acct4.bindValue(":amount",ui->doubleSpinBox_9->value());
                    acct4.bindValue(":memo", ui->lineEdit_6->text().toStdString().c_str());
                    ret = acct4.exec();
                    if (ret != true)
                    {
                        transactionError = true;
                    }
                }
            }
        }
        if (ui->comboBox_5->currentIndex() != -1)
        {
            QSqlQuery getAcctCode;
            //qDebug() << ui->comboBox_5->currentText().toStdString().c_str();
            getAcctCode.prepare("call getAcctCodeFromDesc(:descr)");
            getAcctCode.bindValue(":descr", ui->comboBox_5->currentText().toStdString().c_str());
            getAcctCode.exec();
            while (getAcctCode.next())
            {
                accountCode = getAcctCode.value(0).toString();
            }
            if (ui->doubleSpinBox_10->value() > 0.0)
            {
                acct5.prepare("call insertEntryAcctDeb(:entryCode, :acctCode, :amount, :memo)");
                acct5.bindValue(":entryCode", ui->lineEdit->text().toStdString().c_str());
                acct5.bindValue(":acctCode", accountCode);
                acct5.bindValue(":amount",ui->doubleSpinBox_10->value());
                acct5.bindValue(":memo", ui->lineEdit_7->text().toStdString().c_str());
                ret = acct5.exec();
                if (ret != true)
                {
                    transactionError = true;
                }
            }
            else
            {
                if (ui->doubleSpinBox_11->value() > 0.0)
                {
                    acct5.prepare("call insertEntryAcctCred(:entryCode, :acctCode, :amount, :memo)");
                    acct5.bindValue(":entryCode", ui->lineEdit->text().toStdString().c_str());
                    acct5.bindValue(":acctCode", accountCode);
                    acct5.bindValue(":amount",ui->doubleSpinBox_11->value());
                    acct5.bindValue(":memo", ui->lineEdit_7->text().toStdString().c_str());
                    ret = acct5.exec();
                    if (ret != true)
                    {
                        transactionError = true;
                    }
                }
            }
        }
    }
    else
    {
        transactionError = true;
    }

    if (transactionError == false)
    {
        //qDebug() << "COMMIT";
        if (transact == true)
        {
            odbc->commitTransaction();
        }
    }
    else
    {
        //qDebug() << "ROLLBACK";
        if (transact == true)
        {
            odbc->rollbackTransaction();
        }
    }

    return !transactionError;
}

void MainWindow::on_actionView_GJ_Entry_triggered()
{
    m_viewGJentry = new viewGJentry();
    m_viewGJentry->exec();
}

void MainWindow::on_actionView_GL_Account_triggered()
{
    m_viewGLaccount = new viewGLaccount(m_accountNames);
    m_viewGLaccount->exec();
}

void MainWindow::on_actionView_GJ_triggered()
{
    m_viewGJ = new viewGJ();
    m_viewGJ->exec();
}
