/********************************************************************************
** Form generated from reading UI file 'auth_w.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTH_W_H
#define UI_AUTH_W_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_auth_w
{
public:
    QLineEdit *log_txt;
    QPushButton *enter;

    void setupUi(QDialog *auth_w)
    {
        if (auth_w->objectName().isEmpty())
            auth_w->setObjectName(QString::fromUtf8("auth_w"));
        auth_w->resize(400, 300);
        log_txt = new QLineEdit(auth_w);
        log_txt->setObjectName(QString::fromUtf8("log_txt"));
        log_txt->setGeometry(QRect(50, 90, 281, 20));
        enter = new QPushButton(auth_w);
        enter->setObjectName(QString::fromUtf8("enter"));
        enter->setGeometry(QRect(50, 120, 75, 23));

        retranslateUi(auth_w);

        QMetaObject::connectSlotsByName(auth_w);
    } // setupUi

    void retranslateUi(QDialog *auth_w)
    {
        auth_w->setWindowTitle(QCoreApplication::translate("auth_w", "Dialog", nullptr));
        enter->setText(QCoreApplication::translate("auth_w", "input", nullptr));
    } // retranslateUi

};

namespace Ui {
    class auth_w: public Ui_auth_w {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTH_W_H
