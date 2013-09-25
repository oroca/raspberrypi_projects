#include <stdio.h>
#include <stdlib.h>
#include <sys/sysinfo.h>
#include <wiringPi.h>

#include "lcd.h"

#define RS  7
#define EN  8
#define DB4 22
#define DB5 23
#define DB6 24
#define DB7 25

int main (void) {
  FILE  *fp;
  int    fd;

  struct sysinfo sys_info;

  char uptimeInfo[15];
  char tempInfo[10];
  char cpuUsageInfo[10];
  char freeRamInfo[10];

  char  buf[10];
  int   buf_size = 10;
  float shiftfloat = (float)(1<<SI_LOAD_SHIFT);

  if (wiringPiSetupGpio() == -1)
    return 1 ;

  fd=lcdInit(2,16,4,RS,EN,DB4,DB5,DB6,DB7,0,0,0,0);

  while (1) {
    lcdClear(fd);

    if(sysinfo(&sys_info) != 0)
      printf("sysinfo Error\n");

    unsigned int days  = sys_info.uptime / 86400;
    unsigned int hours = (sys_info.uptime / 3600) - (days * 24);
    unsigned int mins  = (sys_info.uptime / 60) - (days * 1440) - (hours * 60);
    sprintf(uptimeInfo, "Run %dD%dH%dM", days, hours, mins);

    if (fp = fopen( "/sys/class/thermal/thermal_zone0/temp", "r")) {
      fgets(buf, buf_size, fp);
      fclose(fp);
    } else printf("fopen Error\n");

    unsigned int temperature = atoi(buf)/1000;
    sprintf(tempInfo, "%d'C",temperature);

    float cpuUsage = (((float)sys_info.loads[0]) / shiftfloat);
    sprintf(cpuUsageInfo, "Load%.2f", cpuUsage);

    unsigned long freeRam = sys_info.freeram / 1024 / 1024;
    sprintf(freeRamInfo, "RAM%ldMB", freeRam);

    lcdPosition(fd, 0,0); lcdPuts(fd,uptimeInfo);
    lcdPosition(fd,12,0); lcdPuts(fd,tempInfo);
    lcdPosition(fd, 0,1); lcdPuts(fd,cpuUsageInfo);
    lcdPosition(fd, 8,1); lcdPuts(fd,freeRamInfo);

    delay(1000);
  }
  return 0;
}
