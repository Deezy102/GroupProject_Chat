#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QMessageBox>
#include <reg_w.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_signin_but_clicked();

    void on_signup_but_clicked();

private:
    Ui::MainWindow *ui;
    reg_w *reg;
};

void check(map<string,string> mp);

#endif // MAINWINDOW_H
