#include "key.h"

key_sta KEY[4];

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

void KeyScan(key_sta *Sn, int value)
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
