#ifndef VIEWGJENTRY_H
#define VIEWGJENTRY_H

#include "ui_viewGJentry.h"
#include <QDialog>

class viewGJentry : public QDialog
{
    Q_OBJECT
public:
    viewGJentry(QString entryCode = "", QDialog *parent = 0);
    virtual ~viewGJentry(void);

private:
        Ui::Dialog ui;
        bool m_search;

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_clicked();
};

#endif // VIEWGJENTRY_H
