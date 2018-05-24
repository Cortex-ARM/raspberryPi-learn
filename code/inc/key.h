#ifndef KEY_H_
#define KEY_H_

#include <wiringPi.h>
#define S1 24
#define S2 27
#define S3 25
#define S4 28 

typedef struct KEY_STA
{
    unsigned char tri;
    unsigned char short_press;
    unsigned char long_press;
    unsigned char press_count;
    unsigned char lead_count;
}key_sta;

extern key_sta KEY[4];

extern void KeyInit(void);
extern void KeyScan(key_sta *Sn, int value);

#endif 
