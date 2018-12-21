#include "head.h"
#include "../QuantumInstructionHandle/GPUQuantumGates.h"
class TestQuantumInstructionHandle : public testing::Test
{
protected:
};

TEST_F(TestQuantumInstructionHandle, testSetComputeUnit)
{
    {
        /*
        * ���Դ�������
        */
        QuantumInstructionHandleAPI mHandle;
        for (int i = -100; i<1; i++)
            EXPECT_EQ(false, mHandle.setComputeUnit(i));

        for (int i = 3; i<10000; i++)
            EXPECT_EQ(false, mHandle.setComputeUnit(i));

        /*
        * ������ȷ����
        */
        EXPECT_EQ(true, mHandle.setComputeUnit(CPU));
    }
    QuantumInstructionHandleAPI mHandle;
    auto mGPUDll = dllLoad("GPUEmulator.dll");
    /*
    * ���Դ���GPUEmulator.dll�Ͳ�����GPUEmulator.dllʱ��
    * ����GPU�ķ������
    */
    if (nullptr == mGPUDll)
        EXPECT_EQ(false, mHandle.setComputeUnit(GPU));
    else
        EXPECT_EQ(true, mHandle.setComputeUnit(GPU));

}

TEST_F(TestQuantumInstructionHandle, testInitState)
{
    /*
    * ����δ���ü��㵥ԪʱinitState�����
    */
    QuantumInstructionHandleAPI mHandle;
    QuantumGateParam param;
    EXPECT_EQ(false, mHandle.initState(&param));

    /*
    * ����û������qbit��ʱinitState�����
    */
    EXPECT_EQ(true, mHandle.setComputeUnit(1));
    EXPECT_EQ(false, mHandle.initState(&param));
    
    /*
    * ����qbit����Χ���ô���ʱinitState�����
    */
    param.setQBitNum(-1);
    EXPECT_EQ(false, mHandle.initState(&param));

    /*
    * ����qbit����Χ����ʱinitState�����
    */
    param.setQBitNum(40);
    EXPECT_EQ(false, mHandle.initState(&param));

    /*
    * ���Գɹ������µ�������
    */
    param.setQBitNum(10);
    EXPECT_EQ(true, mHandle.initState(&param));

}


TEST_F(TestQuantumInstructionHandle, testDestroyState)
{
    /*
    * ���Դ������Ϊ��ʱinitState�����
    */
    QuantumInstructionHandleAPI mHandle;
    EXPECT_EQ(true, mHandle.destroyState(nullptr));
    /*
    * ����δ���ü��㵥ԪʱinitState�����
    */
    QuantumGateParam param;
    EXPECT_EQ(true, mHandle.destroyState(&param));

    /*
    * ����û������qbit��ʱinitState�����
    */
    EXPECT_EQ(true, mHandle.setComputeUnit(1));
    EXPECT_EQ(true, mHandle.destroyState(&param));

    /*
    * ���Գɹ������µ�������
    */
    EXPECT_EQ(true, mHandle.setComputeUnit(1));
    param.setQBitNum(10);
    EXPECT_EQ(true, mHandle.initState(&param));
    EXPECT_EQ(true, mHandle.destroyState(&param));
}

TEST_F(TestQuantumInstructionHandle, testTransmit)
{
    QuantumInstructionHandleAPI mHandle;
    QuantumGateParam param;
    QList qlist;
    /*
    * ���Դ������Ϊ��ʱtransmit�����
    */
    EXPECT_EQ(false, mHandle.transmit(qlist, nullptr));

    /*
    * ����δ���ü��㵥Ԫʱtransmit�����
    */
    EXPECT_EQ(false, mHandle.transmit(qlist, &param));

    /*
    * ����û������qbit��ʱtransmit�����
    */
    EXPECT_EQ(true, mHandle.setComputeUnit(1));
    EXPECT_EQ(false, mHandle.transmit(qlist, &param));

    /*
    * ����û��initStateʱtransmit�����
    */
    param.setQBitNum(10);
    EXPECT_EQ(false, mHandle.transmit(qlist, &param));
    
    /*
    * ������ȷ���ʱtransmit�����
    */
    EXPECT_EQ(true, mHandle.initState(&param));
    EXPECT_EQ(true, mHandle.transmit(qlist, &param));

    /*
    * ����qbitnumԽ��ʱtransmit�����
    */
    qlist.gateInsert(HADAMARD_GATE, 20);
    EXPECT_EQ(false, mHandle.transmit(qlist,&param));
    EXPECT_EQ(true, mHandle.destroyState(&param));
}

TEST_F(TestQuantumInstructionHandle, testGetQState)
{
    QuantumInstructionHandleAPI mHandle;
    QuantumGateParam param;
    string temp;
    /*
    * ���Դ������Ϊ��ʱgetState�����
    */
    EXPECT_EQ(false, mHandle.getState(temp,nullptr));

    /*
    * ����δ���ü��㵥ԪʱgetState�����
    */
    EXPECT_EQ(false, mHandle.getState(temp, &param));

    /*
    * ����û������qbit��ʱgetState�����
    */
    EXPECT_EQ(true, mHandle.setComputeUnit(1));
    EXPECT_EQ(false, mHandle.getState(temp, &param));

    /*
    * ����û��initStateʱgetState�����
    */
    param.setQBitNum(10);
    EXPECT_EQ(false, mHandle.getState(temp, &param));

    /*
    * ������ȷ���ʱtransmit�����
    */
    EXPECT_EQ(true, mHandle.initState(&param));
    EXPECT_EQ(true, mHandle.getState(temp, &param));
    EXPECT_EQ(true, mHandle.destroyState(&param));

}