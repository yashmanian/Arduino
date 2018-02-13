// L298 motor control variables
int M1_A = 3;    
int M1_PWM = 9; 
int M1_B = 4; //pwm


// LED pin attached to Arduino D13
int LED = 13;

//Potentiometer pins
int analogPin = A0;
int sensorValue = 0;  

// variable to store speed value
int speed_val = 255;

void setup()
{
// Start serial monitor at 9600 bps
Serial.begin(9600);

// declare outputs
pinMode(M1_A, OUTPUT);
pinMode(M1_PWM, OUTPUT);
pinMode(M1_B, OUTPUT);


}

void loop()
{
  sensorValue = analogRead(analogPin);
    Serial.println(sensorValue);
  
  speed_val = map(sensorValue,0,1023,0,255);
  M1_forward(speed_val);
  delay(25);
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
