/********************************************************************************
** Form generated from reading UI file 'reg_w.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REG_W_H
#define UI_REG_W_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_reg_w
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLineEdit *conf_reg;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *pass_reg;
    QLabel *label;
    QLineEdit *login_reg;
    QPushButton *reg_but;

    void setupUi(QDialog *reg_w)
    {
        if (reg_w->objectName().isEmpty())
            reg_w->setObjectName(QString::fromUtf8("reg_w"));
        reg_w->resize(658, 358);
        gridLayoutWidget = new QWidget(reg_w);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(210, 40, 371, 161));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        conf_reg = new QLineEdit(gridLayoutWidget);
        conf_reg->setObjectName(QString::fromUtf8("conf_reg"));

        gridLayout->addWidget(conf_reg, 2, 1, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        pass_reg = new QLineEdit(gridLayoutWidget);
        pass_reg->setObjectName(QString::fromUtf8("pass_reg"));

        gridLayout->addWidget(pass_reg, 1, 1, 1, 1);

        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        login_reg = new QLineEdit(gridLayoutWidget);
        login_reg->setObjectName(QString::fromUtf8("login_reg"));

        gridLayout->addWidget(login_reg, 0, 1, 1, 1);

        reg_but = new QPushButton(gridLayoutWidget);
        reg_but->setObjectName(QString::fromUtf8("reg_but"));

        gridLayout->addWidget(reg_but, 3, 1, 1, 1);


        retranslateUi(reg_w);

        QMetaObject::connectSlotsByName(reg_w);
    } // setupUi

    void retranslateUi(QDialog *reg_w)
    {
        reg_w->setWindowTitle(QCoreApplication::translate("reg_w", "Dialog", nullptr));
        label_2->setText(QCoreApplication::translate("reg_w", "password", nullptr));
        label_3->setText(QCoreApplication::translate("reg_w", "confirmation", nullptr));
        label->setText(QCoreApplication::translate("reg_w", "login", nullptr));
        reg_but->setText(QCoreApplication::translate("reg_w", "create account", nullptr));
    } // retranslateUi

};

namespace Ui {
    class reg_w: public Ui_reg_w {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REG_W_H
