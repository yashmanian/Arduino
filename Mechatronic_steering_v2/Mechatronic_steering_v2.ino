/*
  Mechatronic Steering Mark2
  The angular displacement of the steering wheel in is measured by the potentiometer meshed with the front rack and pinion assembly. The calibrated
  range of values are then mapped to the calculated range of angular displacement of the motor controlling the rear steering assembly. Feedback from another rack and pinion
  assembly controls the motion of the motor
  
  Circuit:
  The motor control pins are connected to arduino pins 4 and 5. The PWM pin is connected to the pin 3 for speed control. The feedback from
  the potentiometer meshed with the rear pinion is connected to analog pin A0.The feedback from the potentiometer meshed with the front pinion is connected to analog pin A1.
  Input Power supply Controller : 12V
  Input Power supply Motor : 12V
  Power supply voltage to potentiomters: 5V
  Analog Refernce voltage: 5V
  
  Created: 5 May. 2014
  Modified: 7 May 2014
  By: Yash Manian
 */


//Motor control variables
int M1_A = 4;    // IN2
int M1_PWM = 11; //PWM
int M1_B = 5; // IN1

// variable to store speed value
int speed_val = 255;

//variables to store analog feedback
const int analogInPin = A0; 
double sensorValue = 0;        

//Servo command variable
double inputAngle;


int potpin = A1;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin 
 
void setup() 
{ 
 // Start serial monitor at 9600 bps
  Serial.begin(9600);
  
  // declare outputs
  pinMode(M1_A, OUTPUT);
  pinMode(M1_PWM, OUTPUT);
  pinMode(M1_B, OUTPUT);
  
  
  // turn motor off by default
  M1_stop();
 
} 
 
void loop() 
{ 
  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023) 
  val = map(val, 100, 283, 0, 695);     // scale it to use it with the servo (value between 0 and 180) 
  ServoCommand(val);
  delay(15);                           // waits for the servo to get there 
}

void ServoCommand(double inputAngle)
{
sensorValue = analogRead(analogInPin);

double currAngle = map(analogInPin,106,283,0,695); //explained below....

//map values from adc, after pinion has been meshed
//to motor shaft angles of 0 to 695 degrees

//make sure the ordered angle is within limits(0 to 695 degrees)

inputAngle = constrain(inputAngle,0,695);

while (abs(inputAngle - currAngle) > 15) //there is a posn error. error tolerance = 15 degrees
{
sensorValue = analogRead(analogInPin);

double currAngle = map(analogInPin,106,283,0,695); 

if (inputAngle > currAngle)
{
//turn right
Serial.print("Current:");
Serial.print(currAngle);
Serial.print(",Order:");
Serial.print(inputAngle);
Serial.println(",Turning Right");
M1_forward(speed_val);
delay(25);
} 
else
{
//turn left
Serial.print("Current:");
Serial.print(currAngle);
Serial.print(",Order:");
Serial.print(inputAngle);
Serial.println(",Turning Left");
M1_reverse(speed_val);
delay(25);
}

}

M1_stop(); //if there is no error, stop the motor

}

void ServoPosition(double inputAngle)
{
sensorValue = analogRead(analogInPin);

double currAngle = map(analogInPin,283,106,0,695); 

Serial.print("Ordered Angle:");
Serial.print(inputAngle);
Serial.print(" ,Position:");
Serial.println(currAngle);

delay(50);
}

/////////// motor functions ////////////////

void M1_reverse(int x)
{
digitalWrite(M1_B, LOW);
digitalWrite(M1_A, HIGH);
analogWrite(M1_PWM, x);
}

void M1_forward(int x)
{
digitalWrite(M1_A, LOW);
digitalWrite(M1_B, HIGH);
analogWrite(M1_PWM, x);
}

void M1_stop()
{
digitalWrite(M1_B, LOW);
digitalWrite(M1_A, LOW);
digitalWrite(M1_PWM, LOW);
}
