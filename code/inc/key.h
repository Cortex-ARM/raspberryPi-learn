#ifndef KEY_H_
#define KEY_H_

#define S1 24
#define S2 27
#define S3 25
#define S4 28 

typedef enum 
{
    ALL_UP,
    K1_DOWN_SHORT,
    K1_DOWN_LONG,
    K2_DOWN_SHORT,
    K2_DOWN_LONG,
    K3_DOWN_SHORT,
    K3_DOWN_LONG,
    K4_DOWN_SHORT,
    K4_DOWN_LONG
}KEY_VALUE;

typedef struct 
{
    unsigned char tri;
    unsigned char short_press;
    unsigned char long_press;
    unsigned char press_count;
    unsigned char lead_count;
}KEY_STA;

extern void KeyInit(void);
extern KEY_VALUE KeyboardScan(void);

#endif 
