

#include <Servo.h>
char INBYTE;
int motor1pin1=6;
int motor1pin2=7;
int motor2pin1=8;
int motor2pin2=9;
Servo scanner;

int distance = 0;  //holds value from IR scanner
int scan_threshold = 0;  //threshold for detecting an object
int scan_angle = 90;  //angle that the scanning servo is at
int led_pin = 13;  //pin that status LED is connnected to
int scanner_pin = 1;

//scans for target
void scan()
{
  distance = analogRead(scanner_pin);
  
  if(distance > scan_threshold)  //object detected
  {
    if(scan_angle > 0)  //overflow protection
      scan_angle -= 1;  //turn scanner left
  }
  else  //no object detected
  {
    if(scan_angle < 180)  //overflow protection
      scan_angle += 1;  //turn right
  }
  
  scanner.write(scan_angle);  //set servo angle to scan_angle
}

void auto_calibrate()  //automatically find the target sensing threshold
{
  scan_threshold = analogRead(scanner_pin);
}

void setup()
{
  pinMode(motor1pin1,OUTPUT);
  pinMode(motor1pin2,OUTPUT);
  pinMode(motor2pin1,OUTPUT);
  pinMode(motor2pin2,OUTPUT);
  scanner.attach(3);
  pinMode(led_pin, OUTPUT);
  Serial.begin(9600);  //Begin serial communcation
  pinMode( led_pin, OUTPUT );
  
  //Turn LED on to signal autocalibration, 
  //wait 2 seconds, autocalibrate, then turn LED off
  digitalWrite(led_pin, HIGH);
  delay(2000);
  auto_calibrate();
  digitalWrite(led_pin, LOW);
}

void loop()
{
   Serial.println(analogRead(scanner_pin)); //Write the value of the photoresistor to the serial monitor.
   while (!Serial.available());   // stay here so long as COM port is empty   
   INBYTE = Serial.read();        // read next available byte
   analogWrite(led_pin, analogRead(scanner_pin));  //send the value to the ledPin. Depending on value of resistor 
                                                //you have  to divide the value. for example, 
                                                //with a 10k resistor divide the value by 2, for 100k resistor divide by 4.
   delay(1000); //short delay for faster response to light.
   scan();
    
  //if object detected on left, turn left
  if(scan_angle <= 50)
  {
    digitalWrite(motor1pin1,LOW);
    digitalWrite(motor1pin2,HIGH);
    digitalWrite(motor2pin1,HIGH); 
    digitalWrite(motor2pin2,LOW);
  }
  //if object detected on right, turn right
  else if(scan_angle >= 130)
  {
    digitalWrite(motor1pin1,HIGH);
    digitalWrite(motor1pin2,LOW);
    digitalWrite(motor2pin1,LOW); 
    digitalWrite(motor2pin2,HIGH);
  }
  //object is centered, go strait
  else
  {
    digitalWrite(motor1pin1,HIGH);
    digitalWrite(motor1pin2,LOW);
    digitalWrite(motor2pin1,HIGH); 
    digitalWrite(motor2pin2,LOW);
  }
  delay(15);  //small delay to prevent crazy oscillations
}
