#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QErrorMessage>
#include <QString>
#include <QMessageBox>
#include <reg_w.h>
#include <QTcpSocket>


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

    void slot_connected();
    void slot_readyRead();
    //void slot_send_to_server(QString message);
    void slot_disconnected();

private:
    Ui::MainWindow *ui;
    reg_w *reg;
    QTcpSocket *client_sock;
};

//QByteArray check(string name, string password);
QByteArray auth_serv(string name, string password);

#endif // MAINWINDOW_H
