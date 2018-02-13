// Motor Controls
const int PWMELPin = 9; //	Enable PWM Left Motor
const int PWMERPin = 10; //	Enable PWM Right Motor
const int L1Pin = 7; // 	L1 = Left Motor Lead 1
const int L2Pin = 8; // 	L2 = Left Motor Lead 2
const int L3Pin = 4; // 	L3 = Right Motor Lead 1
const int L4Pin = 5; // 	L4 = Right Motor Lead 2
const int LEDPin = 13; // LED
const int Duration = 1000;
void setup()
    {
    pinMode(PWMELPin, OUTPUT);
    pinMode(PWMERPin, OUTPUT);
    pinMode(L1Pin, OUTPUT);
    pinMode(L2Pin, OUTPUT);
    pinMode(L3Pin, OUTPUT);
    pinMode(L4Pin, OUTPUT);
    pinMode(LEDPin, OUTPUT);
    }
//Main Loop 
void loop()
    {
    while (true)
        {
        MotorL(0, 1);
        MotorR(0, 1);
        digitalWrite(LEDPin, LOW);
        delay(5000);
        MotorL(1, 1);
        MotorR(1, 1);
        digitalWrite(LEDPin, HIGH);
        delay(5000);
        MotorL(0, 0);
        MotorR(0, 0);
        digitalWrite(LEDPin, LOW);
        delay(5000);
        MotorL(1, 0);
        MotorR(1, 0);
        digitalWrite(LEDPin, HIGH);
        delay(5000);
        continue;
        }
    }
// ***********************************************************************
// Motor Driver Routines**************************************************
// ***********************************************************************
// (Direction, Speed)
// Direction
// 1=Forward
// 0= Reverse
// Speed
// 1 = High/250
// 0 = Low/50
// ***********************************************************************
void MotorL(int Direction, int Speed)
    {
    // Left Motor 
    if (Speed = 1)
        {
        analogWrite(PWMELPin, 250);
        }
    else
        {
        analogWrite(PWMELPin, 50);
        }
    if (Direction = 1)
        {
        digitalWrite(L1Pin, HIGH);
        digitalWrite(L2Pin, LOW);
        }
    else
        {
        digitalWrite(L1Pin, LOW);
        digitalWrite(L2Pin, HIGH);
        }
    }
// ***********************************************************************
void MotorR(int Direction, int Speed)
    {
    // Left Motor 
    if (Speed = 1)
        {
        analogWrite(PWMELPin, 250);
        }
    else
        {
        analogWrite(PWMELPin, 50);
        }
    if (Direction = 1)
        {
        digitalWrite(L1Pin, HIGH);
        digitalWrite(L2Pin, LOW);
        }
    else
        {
        digitalWrite(L1Pin, LOW);
        digitalWrite(L2Pin, HIGH);
        }
    }
