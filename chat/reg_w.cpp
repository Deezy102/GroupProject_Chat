#include "reg_w.h"
#include "ui_reg_w.h"

reg_w::reg_w(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::reg_w)
{
    ui->setupUi(this);
}

reg_w::~reg_w()
{
    delete ui;
}

map<string, string> read_from_file() {
    std::map<string, string> mp;
    ifstream file("D:\\chat\\build-chat-Desktop_Qt_5_15_2_MinGW_64_bit-Debug\\db.txt", std::ios::in);
    if (!file.is_open()) {
        cout << "try again\n";
    }
    else {
        while (!file.eof()) {
            string name;
            string pass;
            file >> name;
            file >> pass;
            mp.insert(make_pair(name, pass));
        }

    }
    file.close();
    return mp;
}

bool write_to_file(map<string, string> &mp)
{
    QMessageBox msg;
    map<string, string>::iterator iter;
    ofstream file;
    file.open("D:\\chat\\build-chat-Desktop_Qt_5_15_2_MinGW_64_bit-Debug\\db.txt", ofstream::out | ofstream::trunc);
    if (file.is_open() == true) {
        for (iter = mp.begin(); iter != mp.end(); iter++) {
            file << (*iter).first << " " << iter->second << std::endl;
        }
        file.close();
        return true;
    }
    else {

        return false;
    }

}

bool registration(string name, string password)
{
    QMessageBox msg;
    map<string,string> buf = read_from_file();
    map<string, string>::iterator iter;
    auto search = buf.find(name);
    if (search != buf.end())
    {
        msg.setWindowTitle("chat");
        msg.setText("choose another login");
        msg.exec();
        return false;
    }
    else
    {
        buf.insert(make_pair(name, password));
        write_to_file(buf);
        msg.setWindowTitle("chat");
        msg.setText("successful registration");
        msg.exec();
        return true;
    }
}

void reg_w::on_reg_but_clicked()
{
    QMessageBox msg;
    QString login = ui->login_reg->text();
    QString password = ui->pass_reg->text();
    QString conf_pass = ui->conf_reg->text();
    if (password == conf_pass)
    {
        if (registration(login.toStdString(), password.toStdString()))
            this->close();
    }
    else
    {
        msg.setWindowTitle("chat");
        msg.setText("invalid confirmation password");
        msg.exec();
    }

}
