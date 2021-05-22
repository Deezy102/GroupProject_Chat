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
    void test_Funcs_checkText_xytrxqwerty_truereturned();
    void test_Funcs_checkText_xytrxampersandqwerty_falsereturned();
};

TestFuncs::TestFuncs()
{

}

TestFuncs::~TestFuncs()
{

}

void TestFuncs::test_Funcs_checkText_xytrxqwerty_truereturned()
{
    //add
    QString str = "xytrxqwerty";
    bool result = checkText(str);

    //assert
    QVERIFY2(result == true, "checkTest failed");
}

void TestFuncs::test_Funcs_checkText_xytrxampersandqwerty_falsereturned()
{
    //add
    QString str = "xytrx&qwerty";
    bool result = checkText(str);

    //assert
    QVERIFY2(result == true, "checkTest failed");

}


QTEST_APPLESS_MAIN(TestFuncs)

#include "tst_testfuncs.moc"
