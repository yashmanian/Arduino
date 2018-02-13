#include <Servo.h> 

Servo leftservo;  // create servo object to control a servo
Servo rightservo;

int potpin0 = 1;  // analog pin used to connect the potentiometer
int left;    // variable to read the value from the analog pin 
int potpin1 = 2;
int right;
int motor1pin1=6;
int motor1pin2=7;
int motor2pin1=8;
int motor2pin2=9;
void setup() 
{ 
pinMode(motor1pin1,OUTPUT);
pinMode(motor1pin2,OUTPUT);
pinMode(motor2pin1,OUTPUT);
pinMode(motor2pin2,OUTPUT);
}

void loop() 
{ 
  left = analogRead(potpin0);  
  right = analogRead(potpin1);
  
  if(left < right) 
  {  digitalWrite(motor1pin1,HIGH);
  digitalWrite(motor1pin2,LOW);
  digitalWrite(motor2pin1,LOW); 
  digitalWrite(motor2pin2,HIGH);}
  
  else if (left > right)
  { digitalWrite(motor1pin1,LOW);
  digitalWrite(motor1pin2,HIGH);
  digitalWrite(motor2pin1,HIGH); 
  digitalWrite(motor2pin2,LOW);}
  
  else
  {digitalWrite(motor1pin1,HIGH);
  digitalWrite(motor1pin2,LOW);
  digitalWrite(motor2pin1,HIGH); 
  digitalWrite(motor2pin2,LOW);}
 
}
