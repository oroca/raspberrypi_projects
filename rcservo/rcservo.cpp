#include <stdlib.h>
#include <wiringPi.h>

#define RCSERVO  23

int main(void)
{
  if (wiringPiSetupGpio() == -1)
    return 1 ;

  softServoSetup(RCSERVO,-1,-1,-1,-1,-1,-1,-1);
  
  softServoWrite(RCSERVO, -250);
  delay(2);
  softServoWrite(RCSERVO,  500);
  delay(2);
  softServoWrite(RCSERVO, 1250);
  delay(2);
}
