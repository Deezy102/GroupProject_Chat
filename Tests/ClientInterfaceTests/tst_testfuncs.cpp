#include <QtTest>
#include <QString>
#include <vector>
//#include <QTcpSocket>

#include "D:\Code\GroupProject_Chat\ClientInterface\Funcs.h"

// add necessary includes here

class TestFuncs : public QObject
{
    Q_OBJECT

public:
    TestFuncs();
    ~TestFuncs();

private slots:
    void test_Funcs_checkText_qwerty_pass_truereturned();
    void test_Funcs_checkText_5spaces_pass_truereturned();
    void test_Funcs_checkText_ampersand_pass_falsereturned();
    void test_Funcs_checkText_underline_log_truereturned();
    void test_Funcs_checkText_qwerty_random_falsereturned();
};

TestFuncs::TestFuncs()
{

}

TestFuncs::~TestFuncs()
{

}

void TestFuncs::test_Funcs_checkText_qwerty_pass_truereturned()
{
    //add
    QString str = "qwerty";
    QString fswitch = "pass";
    bool result = checkText(str, fswitch);

    //assert
    QVERIFY2(result == true, "checkText failed");
}

void TestFuncs::test_Funcs_checkText_5spaces_pass_truereturned()
{
    //add
    QString str = "     ";
    QString fswitch = "pass";
    bool result = checkText(str, fswitch);

    //assert
    QVERIFY2(result == true, "checkText with 5x' ' failed");
}

void TestFuncs::test_Funcs_checkText_ampersand_pass_falsereturned()
{
    //add
    QString str = "zxc&zxc";
    QString fswitch = "pass";
    bool result = checkText(str, fswitch);

    //assert
    QVERIFY2(result == false, "checkText with &'s failed");
}

void TestFuncs::test_Funcs_checkText_underline_log_truereturned()
{
    //add
    QString str = "Ha_Masse";
    QString fswitch = "log";
    bool result = checkText(str, fswitch);

    //assert
    QVERIFY2(result == true, "checkText with -'s failed");
}

void TestFuncs::test_Funcs_checkText_qwerty_random_falsereturned()
{
    //add
    QString str = "qwerty";
    QString fswitch = "random";
    bool result = checkText(str, fswitch);

    //assert
    QVERIFY2(result == false, "checkText with random fswitch failed");
}





QTEST_APPLESS_MAIN(TestFuncs)

#include "tst_testfuncs.moc"
