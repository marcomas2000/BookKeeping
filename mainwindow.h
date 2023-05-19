#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QList>
#include <viewgjentry.h>
#include <viewglaccount.h>
#include <viewgj.h>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QList<QString> getAccountNames();

protected:
    void changeEvent(QEvent *e);

private:
    void clearForm();
    bool submitEntry();
    Ui::MainWindow *ui;
    QSqlDatabase m_db;
    double m_sumCredit;
    double m_sumDebit;
    viewGJentry * m_viewGJentry;
    viewGLaccount * m_viewGLaccount;
    viewGJ * m_viewGJ;
    QList<QString> m_accountNames;


private slots:
    void on_actionView_GJ_triggered();
    void on_actionView_GL_Account_triggered();
    void on_actionView_GJ_Entry_triggered();
    void on_checkBox_stateChanged(int );
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_actionAbout_Books_triggered();
    void on_actionOpen_triggered();
    void on_actionExit_triggered();
};

inline QList<QString> MainWindow::getAccountNames()
{
    return m_accountNames;
}

#endif // MAINWINDOW_H
