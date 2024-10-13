#include "stcChip.h"
#include "stcIAP.h"
#include "INTRINS.H"
// extern void          _nop_     (void);

#if __STC_LIB_IAP_USE_IAP_Read |         \
    __STC_LIB_IAP_USE_IAP_ReadBuf |      \
    __STC_LIB_IAP_USE_IAP_ReadTill0xff | \
    __STC_LIB_IAP_USE_IAP_Erase |        \
    __STC_LIB_IAP_USE_IAP_Write |        \
    __STC_LIB_IAP_USE_IAP_WriteBuf |     \
    __STC_LIB_IAP_USE_IAP_WriteStr |     \
    __STC_LIB_IAP_USE_IAP_Log

void IAP_Disable()
{
    IAP_CONTR = 0;
    IAP_CMD = 0;
    IAP_TRIG = 0;
    IAP_ADDRH = 0x80;
    IAP_ADDRL = 0;
}
#endif

#if __STC_LIB_IAP_USE_IAP_Read
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
#endif

#if __STC_LIB_IAP_USE_IAP_Write
void IAP_Write(unsigned int add, unsigned char dat)
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
#endif

#if __STC_LIB_IAP_USE_IAP_Erase
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
#endif

#if __STC_LIB_IAP_USE_IAP_ReadBuf
void IAP_ReadBuf(unsigned int startAdd, unsigned char *datBuf, unsigned int len)
{
    // unsigned char *addPtr;
    // addPtr = (unsigned char *)&startAdd;

    IAP_CONTR = 0x80;
    IAP_TPS = ChipSysClkFreq;
    IAP_CMD = 1;
    while (len--)
    {
        // IAP_ADDRL = addPtr[1];
        // IAP_ADDRH = addPtr[0];
        // IAP_ADDRL = addPtr[0];
        // IAP_ADDRH = addPtr[1];
        IAP_ADDRL = startAdd;
        IAP_ADDRH = startAdd >> 8;
        IAP_TRIG = 0x5a;
        IAP_TRIG = 0xa5;
        ++startAdd;
        // _nop_();
        *datBuf = IAP_DATA;
        ++datBuf;
    }

    IAP_Disable();
}
#endif

#if __STC_LIB_IAP_USE_IAP_WriteBuf
void IAP_WriteBuf(unsigned int startAdd, unsigned char *datBuf, unsigned int len)
{
    // unsigned char *addPtr;
    // addPtr = (unsigned char *)&startAdd;
    IAP_CONTR = 0x80;
    IAP_TPS = ChipSysClkFreq;
    IAP_CMD = 2;
    while (len--)
    {
        // IAP_ADDRL = addPtr[0];
        // IAP_ADDRH = addPtr[1];
        // IAP_ADDRL = addPtr[1];
        // IAP_ADDRH = addPtr[0];
        IAP_ADDRL = startAdd;
        IAP_ADDRH = startAdd >> 8;
        IAP_DATA = *datBuf;
        IAP_TRIG = 0x5a;
        IAP_TRIG = 0xa5;
        ++startAdd;
        ++datBuf;
    }
    IAP_Disable();
}
#endif

#if __STC_LIB_IAP_USE_IAP_WriteStr
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
        IAP_ADDRL = addPtr[1];
        IAP_ADDRH = addPtr[0];
        // IAP_ADDRL = addPtr[0];
        // IAP_ADDRH = addPtr[1];
        IAP_DATA = *datBuf;
        IAP_TRIG = 0x5a;
        IAP_TRIG = 0xa5;
        ++startAdd;
        ++datBuf;
    }
    IAP_Disable();
    return startAdd - tmp;
}
#endif

// void IAP_ReadBuffTill0xff(unsigned int startAdd, unsigned char *buf,unsigned int len, unsigned int *offset)
// {
// unsigned char *addPtr;
// unsigned char d0, d1 = 0;
// addPtr = (unsigned char *)&startAdd;
// *offset = startAdd;

// IAP_CONTR = 0x80;
// IAP_TPS = ChipSysClkFreq;
// IAP_CMD = 1;
// do
// {
//     d0 = d1;
//     IAP_ADDRL = addPtr[0];
//     IAP_ADDRH = addPtr[1];
//     IAP_TRIG = 0x5a;
//     IAP_TRIG = 0xa5;
//     ++startAdd;
//     d1 = IAP_DATA;
// } while (d1 != 0xff);

// IAP_Disable();
// *buf = d0;
// *offset = startAdd - *offset - 1;
// }

#if __STC_LIB_IAP_USE_IAP_ReadTill0xff
void IAP_ReadTill0xff(unsigned int startAdd, unsigned char *dat, unsigned int *offset)
{
    // unsigned char *addPtr;
    unsigned char d0, d1 = 0;
    // addPtr = (unsigned char *)&startAdd;
    *offset = startAdd;

    IAP_CONTR = 0x80;
    IAP_TPS = ChipSysClkFreq;
    IAP_CMD = 1;
    do
    {
        d0 = d1;
        // IAP_ADDRL = addPtr[0];
        // IAP_ADDRH = addPtr[1];
        // IAP_ADDRL = addPtr[1];
        // IAP_ADDRH = addPtr[0];
        IAP_ADDRL = startAdd;
        IAP_ADDRH = startAdd >> 8;
        IAP_TRIG = 0x5a;
        IAP_TRIG = 0xa5;
        ++startAdd;
        d1 = IAP_DATA;
    } while (d1 != 0xff);

    IAP_Disable();
    *dat = d0;
    *offset = startAdd - *offset - 1;
}
#endif

#if __STC_LIB_IAP_USE_IAP_Log
// TODO
unsigned char IAP_LogInit(IAP_LogCore *c)
{
    unsigned char *addPtr;
    unsigned char dat, d0;
    char *pwPtr = c->password;
    unsigned int startAdd_ = c->startAdd;
    addPtr = (unsigned char *)&startAdd_;
    IAP_CONTR = 0x80;
    IAP_TPS = ChipSysClkFreq;
    IAP_CMD = 1;
    c->_pswLen = 0;
    c->log = 0;
    while (*pwPtr)
    {
        IAP_ADDRL = addPtr[1];
        IAP_ADDRH = addPtr[0];
        // IAP_ADDRL = addPtr[0];
        // IAP_ADDRH = addPtr[1];

        IAP_TRIG = 0x5a;
        IAP_TRIG = 0xa5;
        ++startAdd_;
        dat = IAP_DATA;
        if (dat != *pwPtr)
            goto virginEEprom;
        ++pwPtr;
        ++(c->_pswLen);
    }
    do
    {
        IAP_ADDRL = addPtr[1];
        IAP_ADDRH = addPtr[0];
        // IAP_ADDRL = addPtr[0];
        // IAP_ADDRH = addPtr[1];
        IAP_TRIG = 0x5a;
        IAP_TRIG = 0xa5;
        ++startAdd_;
        d0 = dat;
        dat = IAP_DATA;
    } while (dat != 0xff);
    // c->_currentLogAdd = startAdd_ - 2;
    c->_currentLogAdd = startAdd_ - 1;
    c->log = startAdd_ - c->startAdd - c->_pswLen - 1;

    IAP_Disable();
    if (c->log)
    {
        --(c->log);
        c->log *= 8;
        dat = 8;
        while (dat--)
        {
            if (d0 & 0x01)
                return 0;
            ++(c->log);
            d0 >>= 1;
        }
    }
    return 0;
virginEEprom:
    startAdd_ = c->startAdd;
    IAP_Erase(c->startAdd);
    c->_pswLen = IAP_WriteStr(c->startAdd, c->password);
    c->_currentLogAdd = c->startAdd + c->_pswLen;
    return 1;
}

// TODO
unsigned char IAP_LogAdd(IAP_LogCore *c)
{
    unsigned char dat;
    // if (c->log > 4000)
    //     return 1;
    ++c->log;

    dat = IAP_Read(c->_currentLogAdd);
    if (dat == 0)
    {
        dat = 0xfe;
        ++(c->_currentLogAdd);
    }
    else
    {
        dat <<= 1;
        dat &= 0xfe;
    }
    IAP_Write(c->_currentLogAdd, dat);
    // ++c->_currentLogAdd;
    return 0;
}
#endif
