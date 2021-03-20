#ifndef REG_W_H
#define REG_W_H

#include <QDialog>
#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <utility>
#include <QMessageBox>

using std::map;
using std::ifstream;
using std::ofstream;
using std::pair;
using std::cout;
using std::string;

namespace Ui {
class reg_w;
}

class reg_w : public QDialog
{
    Q_OBJECT

public:
    explicit reg_w(QWidget *parent = nullptr);
    ~reg_w();

private slots:
    void on_reg_but_clicked();

private:
    Ui::reg_w *ui;
    map <string,string> buf;
};

bool registration();
map<string, string> read_from_file();
bool write_to_file(map<string, string> &mp);

#endif // REG_W_H
