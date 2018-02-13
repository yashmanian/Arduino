/*
  Digital servo control with feedback:
  Used to convert a standard high torque motor into a servo with position feedback. It can accept a range of angular values, from 0 to 695
  through the serial monitor. The feedback is printed onto the serial monitor
  
  Circuit:
  The motor control pins are connected to arduino pins 4 and 5. The PWM pin is connected to the pin 3 for speed control. The feedback from
  the potentiometer is connected to analog pin A0.
  Input supply : 12V
  
   Created: 5 May. 2014
   Modified: 7 May 2014
   By: Yash Manian
 */


//Motor control variables
int M1_A = 22;    // IN2
int M1_PWM = 4; //PWM
int M1_B = 24; // IN1

// variable to store speed value
int speed_val = 25;

//variables to store analog feedback
const int analogInPin = A0; 
double sensorValue = 0;        

//Servo command variable
double inputAngle;

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
if (Serial.available())
{
inputAngle = Serial.parseFloat();

Serial.print("Order Recieved:");

Serial.println(inputAngle);

ServoCommand(inputAngle);
}

ServoPosition(inputAngle);

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
