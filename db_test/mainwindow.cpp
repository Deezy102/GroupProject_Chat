#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    client_sock = new QTcpSocket(this);
    client_sock->connectToHost("26.53.118.97", 12345);
    connect(client_sock,SIGNAL(connected()),SLOT(slot_connected()));
    connect(client_sock,SIGNAL(readyRead()),SLOT(slot_readyRead()));
}

MainWindow::~MainWindow()
{
    delete ui;
    client_sock->close();
}

QByteArray auth_serv(string name, string password)
{
    QString message = "auth&"+QString::fromStdString(name)+"&"+QString::fromStdString(password);
    QByteArray array;
    array.append(message);
    return array;
}

void MainWindow::slot_connected()
{
    QMessageBox Msg;
    Msg.setText("Connected!!!");
    Msg.exec();
}

void MainWindow::slot_readyRead()
{
    QByteArray array;
    std::string message = "";

    while(client_sock->bytesAvailable()>0)
    {
        array = client_sock->readAll();
        message += array.toStdString();
    }

    QMessageBox Msg;
    Msg.setText(QString::fromStdString(message));
    Msg.exec();
}

void MainWindow::on_signin_but_clicked()
{
    QString login = ui->log_line->text();
    QString password = ui->pass_line->text();
    QMessageBox msg;
    client_sock->write(auth_serv(login.toStdString(),password.toStdString()));
}

void MainWindow::on_signup_but_clicked()
{
    hide();
    reg = new reg_w(this, client_sock);
    reg->show();
    this->show();
}

void MainWindow::slot_disconnected()
{
    client_sock->close();
}
