// Bluetooth-bot v1
// Arduino Robotics unofficial chapter 14
// use Bluetooth Mate serial adapter to receive commands from PC
// Arduino decodes commands into motor movements
// Creates high-speed wireless serial link for robot control using keyboard
// Uses keys "i" = forward, "j" = left, "k" = reverse, and "l" = right
// speed control is also implemented using "," = speed down, "." = speed up, and "/" = max speed.


// L298 motor control variables
int M1_A = 8;    // if using Ardumoto, change to pin 13 
int M1_B = 9; // if using Ardumoto, remove this variable

int M2_A = 10;   // if using Ardumoto, change to pin 12
int M2_B = 11;    // if using Ardumoto, remove this variable


// LED pin attached to Arduino D13
int LED = 13;

// variable to store serial data
int incomingByte = 0;





void setup(){

// Start serial monitor at 115,200 bps
Serial.begin(115200);

// declare outputs
pinMode(LED, OUTPUT);

pinMode(M1_A, OUTPUT);
pinMode(M1_B, OUTPUT);

pinMode(M2_A, OUTPUT);
pinMode(M2_B, OUTPUT);

// turn motors Off by default
pinMode(M1_A, LOW);
pinMode(M1_B, LOW);

pinMode(M2_A, LOW);
pinMode(M2_B, LOW);


delay(500);

}

////////////////////////////////////

void loop(){


if (Serial.available() > 0) 
{
incomingByte = Serial.read();
digitalWrite(LED, HIGH);
Serial.print("I received: ");
Serial.println(incomingByte);
delay(10);

if (incomingByte == 105)
{
pinMode(M1_A, HIGH);
pinMode(M1_B, LOW);
pinMode(M2_A, HIGH);
pinMode(M2_B, LOW);
delay(25);
}
// if byte is equal to "106" or "j", go left
else if (incomingByte == 106)
{
pinMode(M1_A, LOW);
pinMode(M1_B, HIGH);
pinMode(M2_A, HIGH);
pinMode(M2_B, LOW);
delay(25);
}
// if byte is equal to "108" or "l", go right
else if (incomingByte == 108)
{
pinMode(M1_A, HIGH);
pinMode(M1_B, LOW);

pinMode(M2_A, LOW);
pinMode(M2_B, HIGH);
delay(25);
}
// if byte is equal to "107" or "k", go reverse
else if (incomingByte == 107)
{
pinMode(M1_A, LOW);
pinMode(M1_B, HIGH);

pinMode(M2_A, LOW);
pinMode(M2_B, HIGH);
delay(25);
}
// otherwise, stop both motors
else 
{
pinMode(M1_A, LOW);
pinMode(M1_B, LOW);

pinMode(M2_A, LOW);
pinMode(M2_B, LOW);
}


}

else 
{
pinMode(M1_A, LOW);
pinMode(M1_B, LOW);

pinMode(M2_A, LOW);
pinMode(M2_B, LOW);
digitalWrite(LED, LOW);
}
}


