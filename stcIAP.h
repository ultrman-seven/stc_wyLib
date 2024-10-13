#ifndef E1EFB3E6_9045_411E_B0A5_B80EBAC22DAC
#define E1EFB3E6_9045_411E_B0A5_B80EBAC22DAC

// #define IAP_pageSize 512
#include "stcChip.h"
#define IAP_pageStartAdd(_n) ((_n) << 9)

#if __STC_LIB_IAP_USE_IAP_Read
unsigned char IAP_Read(unsigned int add);
#endif

#if __STC_LIB_IAP_USE_IAP_ReadBuf
void IAP_ReadBuf(unsigned int startAdd, unsigned char *datBuf, unsigned int len);
#endif

#if __STC_LIB_IAP_USE_IAP_ReadTill0xff
void IAP_ReadTill0xff(unsigned int startAdd, unsigned char *dat, unsigned int *offset);
#endif

#if __STC_LIB_IAP_USE_IAP_Erase
void IAP_Erase(unsigned int add);
#endif

#if __STC_LIB_IAP_USE_IAP_Write
void IAP_Write(unsigned int add, unsigned char dat);
#endif

#if __STC_LIB_IAP_USE_IAP_WriteBuf
void IAP_WriteBuf(unsigned int startAdd, unsigned char *datBuf, unsigned int len);
#endif

#if __STC_LIB_IAP_USE_IAP_WriteStr
unsigned int IAP_WriteStr(unsigned int startAdd, char *datBuf);
#endif

#if __STC_LIB_IAP_USE_IAP_Log
typedef struct
{
    unsigned int startAdd;
    unsigned int _currentLogAdd;
    unsigned int log;
    unsigned int maxLen;
    const char *password;

    unsigned int _pswLen;
} IAP_LogCore;

unsigned char IAP_LogInit(IAP_LogCore *);
unsigned char IAP_LogAdd(IAP_LogCore *);
#endif

#endif /* E1EFB3E6_9045_411E_B0A5_B80EBAC22DAC */
