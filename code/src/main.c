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


void Key_Function(KEY_VALUE key_value);
int get_tp(void);
int get_ip(char *ip_name, char *ip_buff);
int uptime(char *str);
void Display_tp(void);
void Display_ip(void);
void Display_time(void);

void Key_Function(KEY_VALUE key_value)
{
    char temp_str[20];
    
    sprintf(temp_str,"Key_Value: %d", key_value);
    LCD_write_english_string(0,5,temp_str);
    if(key_value == K2_DOWN_SHORT)  Display_tp();
    if(key_value == K3_DOWN_SHORT)  Display_ip();
    if(key_value == K4_DOWN_LONG)   LCD_BL_ON;
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

void Display_tp()
{
    char str_tp[20];

    sprintf(str_tp, "CPU-TP:%d", get_tp());
    LCD_write_english_string(0, 3, str_tp);
}

int get_ip(char *ip_name, char *ip_buff)
{
    struct ifreq temp;
    struct sockaddr_in *myaddr;
    int fd = 0;
    int ret = -1;

    strcpy(ip_buff, "No ");
    strcat(ip_buff, ip_name);
    strcpy(temp.ifr_name, ip_name);
    if((fd=socket(AF_INET, SOCK_STREAM, 0))<0)	
	return -1;
    ret = ioctl(fd, SIOCGIFADDR, &temp);
    close(fd);
    if(ret < 0)	
	return -1;
    myaddr = (struct sockaddr_in *)&(temp.ifr_addr);
    strcpy(ip_buff, inet_ntoa(myaddr->sin_addr));
    return 0;
}

void Display_ip()
{
    char str_ip[20];

    get_ip("eth0", str_ip);
    LCD_write_english_string(0, 1, str_ip);
    get_ip("wlan0", str_ip);
    LCD_write_english_string(0, 2, str_ip);
}

void Display_time()
{
    char str_time[20];
    time_t now;
    struct tm *tmnow;
	
    time(&now);
    tmnow=localtime(&now);
    if(tmnow->tm_sec%10 < 2)
	strftime(str_time,100,"%F",tmnow);
    else
	strftime(str_time,100,"%X  ",tmnow);
    LCD_write_english_string(0,0,str_time);
}

int main(void) 
{
    int_clk();
    LCD_init();     
    LCD_clear();
    KeyInit();
    while(1)
    {
	Key_Function(KeyboardScan());
	Display_time();	
	delay(50);
    }
    return 0; 
}
