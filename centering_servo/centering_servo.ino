#include<Servo.h>
Servo servoMain;
void setup()
{
  servoMain.attach(10);
}
void loop()
{
  servoMain.write(90);
}
