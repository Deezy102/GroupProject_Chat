#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void check(string name, string password)
{
    QMessageBox msg;
    map<string,string> buf = read_from_file();
    map<string, string>::iterator iter;
    auto search = buf.find(name);
    if (search != buf.end() && (*search).second == password)
    {
        msg.setWindowTitle("chat");
        msg.setText("entry...");
        msg.exec();
    }
    else
    {
        msg.setWindowTitle("chat");
        msg.setText("incorrect login or password");
        msg.exec();
    }
}

void MainWindow::on_signin_but_clicked()
{
    QString login = ui->log_line->text();
    QString password = ui->pass_line->text();
    QMessageBox msg;
    check(login.toStdString(),password.toStdString());
}

void MainWindow::on_signup_but_clicked()
{
    hide();
    reg = new reg_w(this);
    reg->show();
    this->show();
}
