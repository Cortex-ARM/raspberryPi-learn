#ifndef KEY_H_
#define KEY_H_

#define S1 24
#define S2 27
#define S3 25
#define S4 28 

#define  K1_DOWN_SHORT ((int)0x01)
#define  K1_DOWN_LONG  ((int)0x10)
#define  K2_DOWN_SHORT ((int)0x02)
#define  K2_DOWN_LONG  ((int)0x20)
#define  K3_DOWN_SHORT ((int)0x04)
#define  K3_DOWN_LONG  ((int)0x40)
#define  K4_DOWN_SHORT ((int)0x08)
#define  K4_DOWN_LONG  ((int)0x80)

typedef struct 
{
    unsigned char tri;
    unsigned char short_press;
    unsigned char long_press;
    unsigned char press_count;
    unsigned char lead_count;
}KEY_STA;

extern void KeyInit(void);
extern int KeyboardScan(void);

#endif 
