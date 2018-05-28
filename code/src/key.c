#include "key.h"
#include <wiringPi.h>

KEY_STA KEY[4];

#define LONG_COUNT    7
#define SHORT_COUNT   1
#define LEAD_COUNT    1

void KeyInit()
{
    pinMode(S1, INPUT);
    pinMode(S2, INPUT);
    pinMode(S3, INPUT);
    pinMode(S4, INPUT);
    pullUpDnControl(S1, PUD_UP);
    pullUpDnControl(S2, PUD_UP);
    pullUpDnControl(S3, PUD_UP);
    pullUpDnControl(S4, PUD_UP);
}

static void KeyScan(KEY_STA *Sn, int value)
{
    if(Sn->tri)    //if tri KEY
    {
	if(value)   //if let go
	{
	    if((Sn->long_press == 0)&&(Sn->press_count >= SHORT_COUNT))
		Sn->short_press = 1;
	    Sn->tri  = 0;
	}
	else	//if press 
	{
	    if(Sn->press_count < LONG_COUNT) 
		Sn->press_count++;
	    else 
		Sn->long_press = 1;
	}
    }
    else
    {
	if(value)
	{
	    Sn->lead_count++;
	}
	else if(Sn->lead_count >= LEAD_COUNT)
	{    
	    Sn->tri = 1;
	    Sn->lead_count = 0;
	}
	Sn->press_count = 0;
	Sn->short_press = 0;
	Sn->long_press = 0;
    }
}

int KeyboardScan()
{
    int key_value = 0;

    KeyScan(&KEY[0], digitalRead(S1));
    KeyScan(&KEY[1], digitalRead(S2));
    KeyScan(&KEY[2], digitalRead(S3));
    KeyScan(&KEY[3], digitalRead(S4));
    if(KEY[0].short_press) key_value |= K1_DOWN_SHORT;
    if(KEY[0].long_press)  key_value |= K1_DOWN_LONG;
    if(KEY[1].short_press) key_value |= K2_DOWN_SHORT;
    if(KEY[1].long_press)  key_value |= K2_DOWN_LONG;
    if(KEY[2].short_press) key_value |= K3_DOWN_SHORT;
    if(KEY[2].long_press)  key_value |= K3_DOWN_LONG;
    if(KEY[3].short_press) key_value |= K4_DOWN_SHORT;
    if(KEY[3].long_press)  key_value |= K4_DOWN_LONG;
    
    return key_value;
}
