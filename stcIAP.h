#ifndef E1EFB3E6_9045_411E_B0A5_B80EBAC22DAC
#define E1EFB3E6_9045_411E_B0A5_B80EBAC22DAC

// #define IAP_pageSize 512
#define IAP_pageStartAdd(_n) ((_n) << 9)

unsigned char IAP_Read(unsigned int add);
void IAP_ReadBuf(unsigned int startAdd, unsigned char *datBuf, unsigned int len);
void IAP_ReadTill0xff(unsigned int startAdd, unsigned char *dat, unsigned int *offset);

void IAP_Erase(unsigned int add);

void IAP_Write(int add, unsigned char dat);
void IAP_WriteBuf(unsigned int startAdd, unsigned char *datBuf, unsigned int len);
unsigned int IAP_WriteStr(unsigned int startAdd, char *datBuf);

typedef struct
{
    unsigned int startAdd;
    unsigned int log;
    unsigned int maxLen;
    const char *password;

    unsigned int _pswLen;
}IAP_LogCore;


void IAP_LogInit(IAP_LogCore*);
void IAP_LogAdd(IAP_LogCore*);
#endif /* E1EFB3E6_9045_411E_B0A5_B80EBAC22DAC */
