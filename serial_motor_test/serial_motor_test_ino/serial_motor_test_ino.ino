// L298 motor control variables
int M1_A = 3;    
int M1_PWM = 9; 
int M1_B = 4; //pwm


// LED pin attached to Arduino D13
int LED = 13;

// variable to store serial data
int incomingByte = 0;

// variable to store speed value
int speed_val = 255;

void setup(){

// Start serial monitor at 115,200 bps
Serial.begin(9600);

// declare outputs
pinMode(LED, OUTPUT);

pinMode(M1_A, OUTPUT);
pinMode(M1_PWM, OUTPUT);
pinMode(M1_B, OUTPUT);


// turn motors Off by default
M1_stop();

delay(500);

}

////////////////////////////////////

void loop(){

// check for serial data
if (Serial.available() > 0) 
{
// read the incoming byte:
incomingByte = Serial.read();
// if available, blink LED and print serial data received.
digitalWrite(LED, HIGH);
// say what you got:
Serial.print("received: ");
Serial.println(incomingByte);
// delay 10 milliseconds to allow serial update time
delay(10);

// check incoming byte for direction
// if byte is equal to "46" or "w" - raise speed
if (incomingByte == 119){
speed_val = speed_val + 5;
test_speed();
Serial.println(speed_val);
}
// if byte is equal to "44" or "s" - lower speed
else if (incomingByte == 115){
speed_val = speed_val - 5;
test_speed();
Serial.println(speed_val);
}
// if byte is equal to "47" or "m" - max speed
else if (incomingByte == 109){
speed_val = 255;
test_speed();
}

// if byte is equal to "105" or "a", go forward
else if (incomingByte == 97){
M1_forward(speed_val);
delay(25);
}
// if byte is equal to "106" or "d", go left
else if (incomingByte == 100){
M1_reverse(speed_val);
delay(25);
}
// otherwise, stop both motors
else {
M1_stop();
}


}

else {
M1_stop();
digitalWrite(LED, LOW);
}
}

void test_speed(){
// constrain speed value to between 0-255
if (speed_val > 250){
speed_val = 255;
Serial.println(" MAX ");
}
if (speed_val < 0){
speed_val = 0;
Serial.println(" MIN ");
}

}

/////////// motor functions ////////////////

void M1_reverse(int x){
digitalWrite(M1_B, LOW);
digitalWrite(M1_A, HIGH);
analogWrite(M1_PWM, x);
}

void M1_forward(int x){
digitalWrite(M1_A, LOW);
digitalWrite(M1_B, HIGH);
analogWrite(M1_PWM, x);
}

void M1_stop(){
digitalWrite(M1_B, LOW);
digitalWrite(M1_A, LOW);
digitalWrite(M1_PWM, LOW);
}



