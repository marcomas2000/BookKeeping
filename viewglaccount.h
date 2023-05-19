#ifndef VIEWGLACCOUNT_H
#define VIEWGLACCOUNT_H

#include "ui_viewGLaccount.h"
#include <QDialog>
#include <QList>

class viewGLaccount : public QDialog
{
    Q_OBJECT
public:
    viewGLaccount(QList<QString> accountNames, QDialog *parent = 0);
    virtual ~viewGLaccount(void);

private:
        Ui::ViewGLAccount ui;
        QList<QString> m_acctNames;

private slots:
    void on_comboBox_currentIndexChanged(QString acct);
    void on_pushButton_clicked();
};

#endif // VIEWGLACCOUNT_H
