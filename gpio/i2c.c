#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include <wiringPi.h>
#include <wiringPiI2C.h>

int B2D (unsigned char byte)
{
  unsigned int bitL, bitH;
  bitL = byte & 0x0F;
  bitH = ((byte >> 4) & 0x0F) * 10;
  return bitH + bitL;
}

unsigned int D2B (unsigned int byte)
{
  return ((byte / 10) << 4) + (byte % 10);
}

void getTime (unsigned char clock [])
{
  char *day[7] = {"Sun", "Mon", "Tue", "Wed", "Thr", "Fri", "Sat"};

  printf("----------------------------------------\n");
  printf("Seconds: %4d\n", B2D(clock[0] & 0x7F));
  printf("Minutes: %4d\n", B2D(clock[1] & 0x7F));
  printf("Hours  : %4d\n", B2D(clock[2] & 0x3F));

  if (clock[3] != 0)
    printf("Day    :  %s\n", day[B2D(clock[3] & 0x07)-1]);
  else
    printf("Day    :    0\n");

  printf("Date   : %4d\n", B2D(clock[4] & 0x3F));
  printf("Month  : %4d\n", B2D(clock[5] & 0x1F));

  if (clock[6] != 0)
    printf("Year   : %4d\n", B2D(clock[6])+ 2000);
  else
    printf("Year   :    0\n");

  printf("----------------------------------------\n");
}

void setStop (int fd)
{
  unsigned char temp;

  temp = wiringPiI2CReadReg8(fd, 0x00);
  temp = (temp & 0x7F) | 0x80;

  printf("----------------------------------------\n");
  printf("Stop the clock\n") ;
  wiringPiI2CWriteReg8(fd, 0x00, temp);
}

void setStart (int fd)
{
  unsigned char temp;

  temp = wiringPiI2CReadReg8(fd, 0x00);
  temp = temp & 0x7F;

  printf("----------------------------------------\n");
  printf("Start the clock\n") ;
  wiringPiI2CWriteReg8(fd, 0x00, temp);
}

void setInit (int fd)
{
  unsigned char clock [8] ;
  int i ;

  setStop(fd);

  printf("----------------------------------------\n");
  printf("Set Init\n");

  clock [0] = 0;
  clock [1] = 0;
  clock [2] = 0;
  clock [3] = 0;
  clock [4] = 0;
  clock [5] = 0;
  clock [6] = 0;
  clock [7] = 0;

  for(i=0; i < 8; i++)
    wiringPiI2CWriteReg8(fd, i, clock[i]);

  setStart(fd);
}

void setClock (int fd)
{
  struct tm t ;
  time_t now ;
  unsigned char clock [8] ;
  int i ;

  setStop(fd);

  now = time (NULL);
  gmtime_r (&now, &t);

  printf("----------------------------------------\n");
  printf ("View UTC Time\n") ;

  printf ("UTC Seconds: %3d\n", t.tm_sec);
  printf ("UTC Minutes: %3d\n", t.tm_min);
  printf ("UTC Hours  : %3d\n", t.tm_hour);
  printf ("UTC Day    : %3d\n", t.tm_wday);
  printf ("UTC Date   : %3d\n", t.tm_mday);
  printf ("UTC Month  : %3d\n", t.tm_mon);
  printf ("UTC Year   : %3d\n", t.tm_year);

  printf("----------------------------------------\n");
  printf ("Set UTC + 9hours Time\n") ;

  clock [0] = D2B(t.tm_sec)    & 0x7F; // seconds
  clock [1] = D2B(t.tm_min)    & 0x7F; // mins
  clock [2] = D2B(t.tm_hour+9) & 0x3F; // UTC + 9 hour (24hour set)
  clock [3] = D2B(t.tm_wday+1) & 0x07; // weekdays (sun 0) -> ds1307
weekdays (sun 1)
  clock [4] = D2B(t.tm_mday)   & 0x3F; // date
  clock [5] = D2B(t.tm_mon +1) & 0x1F; // months 0-11 --> ds1307 months 1-12
  clock [6] = D2B(t.tm_year-100) ; // years 1xx -> ds1307 years xx
  clock [7] = 0x00; // CLKOUT control


  for(i=0; i < 8; i++)
    wiringPiI2CWriteReg8(fd, i, clock[i]);

  setStart(fd);
}

int main(int argc, char *argv [])
{
  int rtc;
  int i;
  unsigned char clock [10];

  if((rtc = wiringPiI2CSetup(0x68)) == -1)
  {
    fprintf(stderr, "rtc: Unable to initialise I2C: %s\n", strerror (errno));
    return 1;
  }

  if(argc == 2)
  {
    if(strcmp (argv [1], "-s") == 0)
      setClock(rtc);
    else if(strcmp (argv [1], "-i") == 0)
      setInit(rtc);
    else if(strcmp (argv [1], "-t") == 0)
      setStart(rtc);
    else if(strcmp (argv [1], "-p") == 0)
      setStop(rtc);
  }

  for(i=0; i < 7; i++)
    clock[i] = wiringPiI2CReadReg8(rtc, i);

  getTime(clock);

  printf("\n");

  return 0;
}
