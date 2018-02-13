#include <Servo.h> 

Servo leftservo;  // create servo object to control a servo
Servo rightservo;

int potpin0 = 1;  // analog pin used to connect the potentiometer
int left;    // variable to read the value from the analog pin 
int potpin1 = 2;
int right;
void setup() 
{ 
  leftservo.attach(7);  
  rightservo.attach(8);
  rightservo.write(90);
  leftservo.write(90);
  delay(1000);
}

void loop() 
{ 
  left = analogRead(potpin0);  
  right = analogRead(potpin1);
  
  if(left < right) 
  { leftservo.write(75);
  rightservo.write(90);}
  
  else if (left > right)
  { leftservo.write(90);
  rightservo.write(105);}
  
  else
  {leftservo.write(75);
  rightservo.write(105);}
 
}
