#ifndef REG_W_H
#define REG_W_H

#include <QDialog>
#include <string>
#include <map>
#include <QMessageBox>
#include <fstream>
#include <utility>
#include <QDebug>

#include <QTcpSocket>

using std::map;
using std::ifstream;
using std::ofstream;
using std::pair;
using std::string;

namespace Ui {
class reg_w;
}

class reg_w : public QDialog
{
    Q_OBJECT

public:
    explicit reg_w(QWidget *parent = nullptr, QTcpSocket *sock = nullptr);
    ~reg_w();

private slots:
    void on_reg_but_clicked();

    void slot_readyRead();
    //void slot_send_to_server(QString message);
private:
    Ui::reg_w *ui;
    map <string,string> buf;
    QTcpSocket *client_sock;

};


#endif // REG_W_H
