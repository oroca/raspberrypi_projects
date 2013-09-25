#include <stdlib.h>
#include <wiringPi.h>

#define KEY1 17
#define KEY2 27
#define KEY3 22
#define KEY4  4
#define KEY5 10
#define KEY6  9
#define KEY7 11
#define LED  18

int main(void) {
  if (wiringPiSetupGpio() == -1)
    return 1 ;

  pinMode(KEY1, INPUT);
  pinMode(KEY2, INPUT);
  pinMode(KEY3, INPUT);
  pinMode(KEY4, INPUT);
  pinMode(KEY5, INPUT);
  pinMode(KEY6, INPUT);
  pinMode(KEY7, INPUT);
  
  pinMode(LED,  PWM_OUTPUT);
  
  while (1) {
    if(digitalRead(KEY1) == 1) {
      system("aplay do.wav");
      pwmWrite(LED, 150);
    } else if(digitalRead(KEY2) == 1) {
      system("aplay re.wav");
      pwmWrite(LED, 300);
    } else if(digitalRead(KEY3) == 1) {
      system("aplay mi.wav");
      pwmWrite(LED, 450);
    } else if(digitalRead(KEY4) == 1) {
      system("aplay fa.wav");
      pwmWrite(LED, 600);
    } else if(digitalRead(KEY5) == 1) {
      system("aplay sl.wav");
      pwmWrite(LED, 750);
    } else if(digitalRead(KEY6) == 1) {
      system("aplay la.wav");
      pwmWrite(LED, 1000);
    } else if(digitalRead(KEY7) == 1) {
      system("aplay ti.wav");
      pwmWrite(LED, 1023);
    } else { pwmWrite(LED, 0) };
  }
  return 0;
}
