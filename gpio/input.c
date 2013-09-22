#include <stdio.h> 
#include <wiringPi.h>

#define LED1 23
#define LED2 24
#define SW   25

int main(void)
{
  if(wiringPiSetupGpio() == -1) 
    return 1;

  pinMode(LED1, OUTPUT); 
  pinMode(LED2, OUTPUT); 

  pinMode(SW, INPUT); 


  while(1)
  {
    digitalWrite(LED1, 0);
    digitalWrite(LED2, 0); 

    if(digitalRead(SW) == 1) 
    {
      digitalWrite(LED1, 1);
      digitalWrite(LED2, 1);
      delay(1000);
    }
  }
  return 0 ;
}
