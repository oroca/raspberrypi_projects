#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <wiringPi.h>

#define KEY0 7

int main(void) {
  if (wiringPiSetupGpio() == -1)
    return 1 ;

  pinMode(KEY0, INPUT);

  while (1) {
    if(digitalRead(KEY0) == 1) {
     system("aplay test.wav");    
    }
  }
  return 0;
}

