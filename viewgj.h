#ifndef VIEWGJ_H
#define VIEWGJ_H

#include <QDialog>
#include "ui_viewGJ.h"

class viewGJ : public QDialog
{
    Q_OBJECT
public:
    viewGJ(QDialog *parent = 0);
    virtual ~viewGJ(void);

private:
        Ui::viewGJ ui;


private slots:
    void on_tableWidget_cellDoubleClicked(int row, int column);
    void on_pushButton_clicked();
};

#endif // VIEWGJ_H
