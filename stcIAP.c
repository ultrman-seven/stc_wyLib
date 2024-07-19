#include "stcChip.h"
#include "stcIAP.h"

unsigned char IAP_Read(unsigned int add)
{
    unsigned char dat;
    IAP_CONTR = 0x80;
    IAP_TPS = ChipSysClkFreq;
    IAP_CMD = 1;
    IAP_ADDRL = add;
    IAP_ADDRH = add >> 8;
    IAP_TRIG = 0x5a;
    IAP_TRIG = 0xa5;
    _nop_();
    dat = IAP_DATA;
    IAP_Disable();
    return dat;
}

void IAP_Write(int add, unsigned char dat)
{
    IAP_CONTR = 0x80;
    IAP_TPS = ChipSysClkFreq;
    IAP_CMD = 2;
    IAP_ADDRL = add;
    IAP_ADDRH = add >> 8;
    IAP_DATA = dat;
    IAP_TRIG = 0x5a;
    IAP_TRIG = 0xa5;
    _nop_();
    IAP_Disable();
}

void IAP_Erase(unsigned int add)
{
    IAP_CONTR = 0x80;
    IAP_TPS = ChipSysClkFreq;
    IAP_CMD = 3;
    IAP_ADDRL = add;
    IAP_ADDRH = add >> 8;
    IAP_TRIG = 0x5a;
    IAP_TRIG = 0xa5;
    _nop_();
    IAP_Disable();
}

void IAP_ReadBuf(unsigned int startAdd, unsigned char *datBuf, unsigned int len)
{
    unsigned char *addPtr;
    addPtr = (unsigned char *)&startAdd;

    IAP_CONTR = 0x80;
    IAP_TPS = ChipSysClkFreq;
    IAP_CMD = 1;
    while (len--)
    {
        IAP_ADDRL = addPtr[0];
        IAP_ADDRH = addPtr[1];
        IAP_TRIG = 0x5a;
        IAP_TRIG = 0xa5;
        ++startAdd;
        *datBuf = IAP_DATA;
        ++datBuf;
    }

    IAP_Disable();
}

void IAP_WriteBuf(unsigned int startAdd, unsigned char *datBuf, unsigned int len)
{
    unsigned char *addPtr;
    addPtr = (unsigned char *)&startAdd;
    IAP_CONTR = 0x80;
    IAP_TPS = ChipSysClkFreq;
    IAP_CMD = 2;
    while (len--)
    {
        IAP_ADDRL = addPtr[0];
        IAP_ADDRH = addPtr[1];
        IAP_DATA = *datBuf;
        IAP_TRIG = 0x5a;
        IAP_TRIG = 0xa5;
        ++startAdd;
        ++datBuf;
    }
    IAP_Disable();
}

unsigned int IAP_WriteStr(unsigned int startAdd, char *datBuf)
{
    unsigned char *addPtr;
    unsigned int tmp;
    tmp = startAdd;
    addPtr = (unsigned char *)&startAdd;
    IAP_CONTR = 0x80;
    IAP_TPS = ChipSysClkFreq;
    IAP_CMD = 2;
    while (*datBuf)
    {
        IAP_ADDRL = addPtr[0];
        IAP_ADDRH = addPtr[1];
        IAP_DATA = *datBuf;
        IAP_TRIG = 0x5a;
        IAP_TRIG = 0xa5;
        ++startAdd;
        ++datBuf;
    }
    IAP_Disable();
    return startAdd - tmp;
}

void IAP_ReadTill0xff(unsigned int startAdd, unsigned char *dat, unsigned int *offset)
{
    unsigned char *addPtr;
    unsigned char d0, d1 = 0;
    addPtr = (unsigned char *)&startAdd;
    *offset = startAdd;

    IAP_CONTR = 0x80;
    IAP_TPS = ChipSysClkFreq;
    IAP_CMD = 1;
    do
    {
        d0 = d1;
        IAP_ADDRL = addPtr[0];
        IAP_ADDRH = addPtr[1];
        IAP_TRIG = 0x5a;
        IAP_TRIG = 0xa5;
        ++startAdd;
        d1 = IAP_DATA;
    } while (d1 != 0xff);

    IAP_Disable();
    *dat = d0;
    *offset = startAdd - *offset - 1;
}

// TODO
void IAP_LogInit(IAP_LogCore *c)
{
    unsigned char *addPtr;
    char dat;
    char *pwPtr = c->password;
    unsigned int startAdd = c->startAdd;
    addPtr = (unsigned char *)&startAdd;
    IAP_CONTR = 0x80;
    IAP_TPS = ChipSysClkFreq;
    IAP_CMD = 1;
    c->_pswLen = 0;
    while (*pwPtr)
    {
        IAP_ADDRL = addPtr[0];
        IAP_ADDRH = addPtr[1];
        IAP_TRIG = 0x5a;
        IAP_TRIG = 0xa5;
        ++startAdd;
        dat = IAP_DATA;
        if (dat != *pwPtr)
            goto virginEEprom;
        ++pwPtr;
        ++(c->_pswLen);
    }
    IAP_Disable();

    return;
virginEEprom:
    c->log = 0;
    startAdd = c->startAdd;

    c->_pswLen = IAP_WriteStr(c->startAdd, c->password);
}

// TODO
void IAP_LogAdd(IAP_LogCore *c)
{
    ++c->log;
}
