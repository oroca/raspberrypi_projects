#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <wiringPi.h>
#include <wiringPiSPI.h>

#define CS_MCP3208  8        // BCM_GPIO_8

#define SPI_CHANNEL 0
#define SPI_SPEED   1000000   // 1MHz

int read_mcp3208_adc(unsigned char adcChannel)
{
  unsigned char buff[3];
  int adcValue = 0;

  buff[0] = 0x06 | ((adcChannel & 0x07) >> 7);
  buff[1] = ((adcChannel & 0x07) << 6);
  buff[2] = 0x00;

  digitalWrite(CS_MCP3208, 0);  // Low : CS Active

  wiringPiSPIDataRW(SPI_CHANNEL, buff, 3);

  buff[1] = 0x0F & buff[1];
  adcValue = ( buff[1] << 8) | buff[2];

  digitalWrite(CS_MCP3208, 1);  // High : CS Inactive

  return adcValue;
}


int main (void)
{
  int adcChannel  = 0;
  int adcValue[8] = {0};

  if(wiringPiSetupGpio() == -1)
  {
    fprintf (stdout, "Unable to start wiringPi: %s\n", strerror(errno));
    return 1 ;
  }

  if(wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED) == -1)
  {
    fprintf (stdout, "wiringPiSPISetup Failed: %s\n", strerror(errno));
    return 1 ;
  }

  pinMode(CS_MCP3208, OUTPUT);

  while(1)
  {
    adcValue[0] = read_mcp3208_adc(0); // Humidity Sensor
    adcValue[0] = ((adcValue[0]*0.001172161 - 0.48)/3.84) * 100;
    adcValue[1] = read_mcp3208_adc(1); // Temperature Sensor
    adcValue[1] = ((adcValue[1]*0.001172161 - 0.48)/3.84) * 200 - 50;
    adcValue[2] = read_mcp3208_adc(2); // Moisture Sensor
    printf("hum= %5d, tem= %5d, moi= %5d\n", adcValue[0], adcValue[1], adcValue[2]);
  }

  return 0;
}
