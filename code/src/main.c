#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <net/if.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <time.h>
#include "lcd5110.h"
#include "key.h"

void KeyboardScan()
{
    char temp_str[20];

    KeyScan(&KEY[0], digitalRead(S1));
    KeyScan(&KEY[1], digitalRead(S2));
    KeyScan(&KEY[2], digitalRead(S3));
    KeyScan(&KEY[3], digitalRead(S4));
    sprintf(temp_str,"S1:%d %d  S2:%d %d", KEY[0].short_press, KEY[0].long_press, KEY[1].short_press, KEY[1].long_press);
    LCD_write_english_string(0,4,temp_str);
    sprintf(temp_str,"S3:%d %d  S4:%d %d", KEY[2].short_press, KEY[2].long_press, KEY[3].short_press, KEY[3].long_press);
    LCD_write_english_string(0,5,temp_str);
    if(KEY[3].long_press) LCD_BL_ON;
    else LCD_BL_OFF;
}

int get_tp()
{
    int fd;
    int temp = 0;
    char buf[32];

    fd = open("/sys/class/thermal/thermal_zone0/temp", O_RDONLY);
    if(fd < 0) return -1;
    if(read(fd, buf, 32) < 0) return -1;
    temp = atol(buf)/1000;
    close(fd);
    return temp;
}

char* get_eth0_ip(char* ip_buf)
{
    struct ifreq temp;
    struct sockaddr_in *myaddr;
    int fd = 0;
    int ret = -1;
    strcpy(temp.ifr_name, "eth0");
    if((fd=socket(AF_INET, SOCK_STREAM, 0))<0)
    {
        return NULL;
    }
    ret = ioctl(fd, SIOCGIFADDR, &temp);
    close(fd);
    if(ret < 0)
    {
        return NULL;
    }
    myaddr = (struct sockaddr_in *)&(temp.ifr_addr);
    strcpy(ip_buf, inet_ntoa(myaddr->sin_addr));
    return ip_buf;
} 
char* get_wlan0_ip(char* ip_buf)
{
    struct ifreq temp;
    struct sockaddr_in *myaddr;
    int fd = 0;
    int ret = -1;
    strcpy(temp.ifr_name, "wlan0");
    if((fd=socket(AF_INET, SOCK_STREAM, 0))<0)
    {
        return NULL;
    }
    ret = ioctl(fd, SIOCGIFADDR, &temp);
    close(fd);
    if(ret < 0)
    {
        return NULL;
    }
    myaddr = (struct sockaddr_in *)&(temp.ifr_addr);
    strcpy(ip_buf, inet_ntoa(myaddr->sin_addr));
    return ip_buf;
}
int uptime(char *str)
{
	time_t now;
	struct tm *tmnow;
	static time_t old;
	
	time(&now);
	if(old != now)
	{
		tmnow=localtime(&now);
		if(tmnow->tm_sec%10 < 2)
			strftime(str,100,"%F",tmnow);
		else
			strftime(str,100,"%X  ",tmnow);
		old = now;

		if(tmnow->tm_sec == 0)
		    return 2;
		else
		    return 1;
	}
	else 
		return 0;
}

int main(void) 
{
    char temp_str[20];

    int_clk();
    LCD_init();     
    LCD_clear();
    KeyInit();
    while(1)
    {
	//function for key
	KeyboardScan();
	
	//update to time
	switch(uptime(temp_str))
        {
	    case 1:
	    {
		LCD_write_english_string(0,0,temp_str);
		break;
	    }
	    case 2:
	    {
		if(get_eth0_ip(temp_str) != NULL)
		    LCD_write_english_string(0,1,temp_str);
		else
		    LCD_write_english_string(0,1,"No eth0       ");
		if(get_wlan0_ip(temp_str) != NULL)
		    LCD_write_english_string(0,2,temp_str);
		else
		    LCD_write_english_string(0,2,"No wlan0      ");
		sprintf(temp_str,"CPU_TP:%d",get_tp());
		LCD_write_english_string(0,3,temp_str);
		break;
	    }
	    default:break;
        }

	//delay
	delay(30);
    }
    return 0; 
}
