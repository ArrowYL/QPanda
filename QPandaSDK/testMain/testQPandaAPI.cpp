#include "head.h"
#include "../QuantumInstructionHandle/GPUQuantumGates.h"
class TestQPandaAPI : public testing::Test
{
protected:

};
#define CPU 1
#define GPU 2

TEST_F(TestQPandaAPI, testLoadFile)
{
    QPandaSDK mQpandaAPI;
    string sTest;
    
    /*
    * ���Կ��ַ���
    */
    EXPECT_EQ(qParameterError, mQpandaAPI.loadFile(sTest));

    /*
    * ������Ч�ı���ַ
    */
    sTest.append("hahah");
    EXPECT_EQ(qbitError, mQpandaAPI.loadFile(sTest));
    mQpandaAPI.msFileName.clear();

    /*
    * ������ȷ���ӳ����ı���ַ
    */
    string sTest2("shor_15.txt");
    EXPECT_EQ(qErrorNone, mQpandaAPI.loadFile(sTest2));
}

TEST_F(TestQPandaAPI, testSetComputeUnit)
{

    {
        /*
        * ���Դ�������
        */
        QPandaSDK mQpandaAPI;
        for(int i = -100;i<1;i++)
            EXPECT_EQ(qParameterError, mQpandaAPI.setComputeUnit(i));

        for (int i = 3; i<10000; i++)
            EXPECT_EQ(qParameterError, mQpandaAPI.setComputeUnit(i));

        /*
        * ������ȷ����
        */
        EXPECT_EQ(qErrorNone, mQpandaAPI.setComputeUnit(CPU));
    }
    QPandaSDK mQpandaAPI;
    auto mGPUDll = dllLoad("GPUEmulator.dll");
    /*
    * ���Դ���GPUEmulator.dll�Ͳ�����GPUEmulator.dllʱ��
    * ����GPU�ķ������
    */
    if(nullptr == mGPUDll)
        EXPECT_EQ(setComputeUnitError, mQpandaAPI.setComputeUnit(GPU));
    else
        EXPECT_EQ(qErrorNone, mQpandaAPI.setComputeUnit(GPU));

}

TEST_F(TestQPandaAPI, testRun)
{
    /*
    * ����û�ж�ȡ�ļ�ʱ�ķ������
    */
    QPandaSDK mQpandaAPI;
    EXPECT_EQ(notReadFileError, mQpandaAPI.run(1));

    /*
    * ����iRepeat�ڴ���Χʱ�ķ������
    */
    string sTest("shor_15.txt");
    EXPECT_EQ(qErrorNone, mQpandaAPI.loadFile(sTest));
    EXPECT_EQ(qParameterError, mQpandaAPI.run(-1));

    /*
    * ������ȷ����ķ���ֵ
    */
    EXPECT_EQ(qErrorNone, mQpandaAPI.setComputeUnit(CPU));
    EXPECT_EQ(qErrorNone, mQpandaAPI.run(100));
}


TEST_F(TestQPandaAPI, testGetResult)
{
    /*
    * ����û������ʱ�����ķ���ֵ
    */
    QPandaSDK mQpandaAPI;
    string temp = mQpandaAPI.getResult();
    EXPECT_EQ(0, temp.size());

    /*
    * �������к����ķ���ֵ
    */
    string sTest("shor_15.txt");
    EXPECT_EQ(qErrorNone, mQpandaAPI.loadFile(sTest));
    EXPECT_EQ(qErrorNone, mQpandaAPI.setComputeUnit(CPU));
    EXPECT_EQ(qErrorNone, mQpandaAPI.run(100));
    string sResult = mQpandaAPI.getResult();
    EXPECT_LT(0, sResult.size());
}

TEST_F(TestQPandaAPI, testGetQuantumState)
{
    /*
    * ����û������ʱ�����ķ���ֵ
    */
    QPandaSDK mQpandaAPI;
    string temp = mQpandaAPI.getQuantumState();
    EXPECT_EQ(0, temp.size());

    /*
    * �������к����ķ���ֵ
    */
    string sTest("shor_15.txt");
    EXPECT_EQ(qErrorNone, mQpandaAPI.loadFile(sTest));
    EXPECT_EQ(qErrorNone, mQpandaAPI.setComputeUnit(CPU));
    EXPECT_EQ(qErrorNone, mQpandaAPI.run(100));
    string sResult = mQpandaAPI.getQuantumState();
    EXPECT_LT(0, sResult.size());
}
