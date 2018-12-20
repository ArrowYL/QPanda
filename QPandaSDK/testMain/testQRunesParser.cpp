#include "head.h"

class TesttQRunesParser : public testing::Test
{
protected:

};

TEST_F(TesttQRunesParser, testQRunesParser)
{
    string sTest;
    QList qlist;
    /*
    * ���Կ��ַ���
    */
    EXPECT_EQ(-1, QRunesParser(sTest, qlist));

    /*
    * ������Ч�ı���ַ
    */
    sTest.append("hahah");
    EXPECT_EQ(-1, QRunesParser(sTest, qlist));

    /*
    * ������ȷ���ӳ����ı���ַ
    */
    string sTest2("shor_15.txt");
    EXPECT_NE(-1, QRunesParser(sTest2, qlist));

    /*
    * ���Դ������ӳ����ı���ַ
    */
    string sTest3("testfile.txt");
    EXPECT_EQ(-1, QRunesParser(sTest3, qlist));
}