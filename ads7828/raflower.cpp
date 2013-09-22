#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include <wiringPi.h>
#include <wiringPiI2C.h>

// Binary Number -> Decimal Number
int B2D (unsigned char byte)
{
  unsigned int bitL, bitH;
  bitL = byte & 0x0F;
  bitH = ((byte >> 4) & 0x0F) * 10;
  return bitH + bitL;
}

// Decimal Number -> Binary Number
unsigned int D2B (unsigned int byte)
{
  return ((byte / 10) << 4) + (byte % 10);
}

unsigned int convert(int add,unsigned char ch)
{
   unsigned int adc=0;
   ch = (((ch>>1) | (ch&0x01)<<2)<<4) | 0x80;
   ch &= 0xF0;
   ch |= 0x00; // Power Down Between A/D Converter Conversions
   wiringPiI2CWriteReg8(add, 0x90, ch);
   adc = wiringPiI2CReadReg16(add, 0x91) & 0x0FFF;
   sleep(0.5);
   return adc;
}

// Main Function
int main(int argc, char *argv [])
{
  int ads7828;
  int i;
  int adcvaule[8];

  if((ads7828 = wiringPiI2CSetup(0x48)) == -1)
  {
    fprintf(stderr, "ads7828: Unable to initialise I2C: %s\n", strerror (errno));
    return 1;
  }

/*
  if(argc == 2)
  {
    if(strcmp (argv [1], "-s") == 0)
      setInit(ads7828);
    else if(strcmp (argv [1], "-i") == 0)
      setInit(ads7828);
  }
*/
  printf("ads7828 =  %d\n",ads7828);


 // for(i=0; i < 7; i++)

  //getTime(clock);

  for(;;)
  {
    adcvaule[0] = convert(ads7828,0);
    adcvaule[1] = convert(ads7828,1);
    adcvaule[2] = convert(ads7828,2);
    adcvaule[3] = convert(ads7828,3);

    printf("adc =  %5d, %5d, %5d, %5d\n",adcvaule[0],adcvaule[1],adcvaule[2],adcvaule[3]);
  }


  return 0;
}

