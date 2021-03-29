#include "reg_w.h"
#include "ui_reg_w.h"


reg_w::reg_w(QWidget *parent, QTcpSocket *sock) :
    QDialog(parent),
    ui(new Ui::reg_w)
{
    ui->setupUi(this);

    client_sock = sock;
}

reg_w::~reg_w()
{
    delete ui;
}

void reg_w::slot_readyRead()
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

void reg_w::on_reg_but_clicked()
{
    QMessageBox msg;
    QString login = ui->login_reg->text();
    QString password = ui->pass_reg->text();
    QString conf_pass = ui->conf_reg->text();
    if (password == conf_pass)
    {
        QString message = "reg&"+login+"&"+password;
        QByteArray array;
        array.append(message);
        client_sock->write(array);
//        if (registration(login.toStdString(), password.toStdString()))
//            this->close();
    }
    else
    {
        msg.setWindowTitle("chat");
        msg.setText("invalid confirmation password");
        msg.exec();
    }

}
