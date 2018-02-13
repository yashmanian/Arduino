int motor1pin1=6;
int motor1pin2=7;
int motor2pin1=8;
int motor2pin2=9;
int ledPin = 13;                // LED connected to digital pin 13

void setup()                    // run once, when the sketch starts
{
pinMode(motor1pin1,OUTPUT);
pinMode(motor1pin2,OUTPUT);
pinMode(motor2pin1,OUTPUT);
pinMode(motor2pin2,OUTPUT);

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
       digitalWrite(motor1pin1,LOW);
       digitalWrite(motor1pin2,HIGH);
       digitalWrite(motor2pin1,HIGH); 
       digitalWrite(motor2pin2,LOW);
         }

      //detects more light on right side of robot
      else if(sensor_right > sensor_left && (sensor_right - sensor_left) > threshold)
         {//go right
          digitalWrite(motor1pin1,HIGH);
          digitalWrite(motor1pin2,LOW);
          digitalWrite(motor2pin1,LOW); 
          digitalWrite(motor2pin2,HIGH);
         }
         
      //detects no light on both left and right side of robot
      else if(sensor_right == sensor_left && (sensor_right - sensor_left) < threshold)
         {//go right
           digitalWrite(motor1pin1,HIGH);
           digitalWrite(motor1pin2,LOW);
           digitalWrite(motor2pin1,LOW); 
           digitalWrite(motor2pin2,HIGH);
         }

      //light is about equal on both sides
      else
         {//go straight
         digitalWrite(motor1pin1,HIGH);
         digitalWrite(motor1pin2,LOW);
         digitalWrite(motor2pin1,HIGH); 
         digitalWrite(motor2pin2,LOW);
         }
   delay(25);                       // waits 25ms for a small delay to prevent crazy oscillations    
   digitalWrite(ledPin, LOW);    // sets the LED off   
}




