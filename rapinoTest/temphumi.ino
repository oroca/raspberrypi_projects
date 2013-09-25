const int analogPin0 = A0;      
const int analogPin1 = A1;      
const float volt = 0.001074219; 

float RH = 0;                  
float T1 = 0;                  

void setup() {
  Serial.begin(57600);   
  analogReference(INTERNAL);     
}

void loop() {
  RH = analogRead(analogPin0);   
  T1 = analogRead(analogPin1);   

  RH = RH * volt * 100;  
  T1 = (T1 * volt *200)-50;

  Serial.print("RH:" );
  Serial.println(RH,2);
  Serial.print("T:");
  Serial.println(T1,2);

  delay(2000);           
}
