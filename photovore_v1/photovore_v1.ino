#include <Servo.h> 

Servo servo_left;   // create servo object to control a servo 
                    // a maximum of eight servo objects can be created 
Servo servo_right;  // create servo object to control a servo 

int ledPin = 13;                // LED connected to digital pin 13

void setup()                    // run once, when the sketch starts
{

  servo_left.attach(9);  // attaches the servo on pin 9 to the servo object 
  servo_right.attach(10);  // attaches the servo on pin 10 to the servo object 
  pinMode(ledPin, OUTPUT);      // sets the digital pin as output

} 
 
   int sensor_left=1;//left photoresistor
   int sensor_right=2;//right photoresistor
   int threshold=8;//the larger this number, the more likely your robot will drive straight
   
void loop() 
{ 
   digitalWrite(ledPin, HIGH);   // sets the LED on
//store sensor data
   sensor_left = analogRead(0);            // reads the value of the left photoresistor (value between 0 and 1023) 
   sensor_left = map(sensor_left, 0, 1023, 0, 255);     // scale it to use it with the 8bits (value between 0 and 255) 
   sensor_right = analogRead(1);            // reads the value of the right photoresistor (value between 0 and 1023) 
   sensor_right = map(sensor_right, 0, 1023, 0, 255);     // scale it to use it with the 8bits (value between 0 and 255) 

      //detects more light on left side of robot
      if(sensor_left > sensor_right && (sensor_left - sensor_right) > threshold)
         {//go left
         servo_left.write(0);     
         servo_right.write(150);
         }

      //detects more light on right side of robot
      else if(sensor_right > sensor_left && (sensor_right - sensor_left) > threshold)
         {//go right
         servo_left.write(150);
         servo_right.write(0);
         }
         
      //detects no light on both left and right side of robot
      else if(sensor_right == sensor_left && (sensor_right - sensor_left) < threshold)
         {//go right
         servo_left.write(90);
         servo_right.write(90);
         }

      //light is about equal on both sides
      else
         {//go straight
         servo_left.write(150);
         servo_right.write(150);
         }
   delay(25);                       // waits 25ms for a small delay to prevent crazy oscillations    
   digitalWrite(ledPin, LOW);    // sets the LED off   
}



