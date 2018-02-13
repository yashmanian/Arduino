int M1_A = 12;    // if using Ardumoto, change to pin 13
int M1_PWM = 11; 
int M1_B = 10; // if using Ardumoto, remove this variable

int M2_A = 4;   // if using Ardumoto, change to pin 12
int M2_PWM = 3;
int M2_B = 2;    // if using Ardumoto, remove this variable
int speed_val = 255;

int ledPin = 13;                // LED connected to digital pin 13

void setup()                    // run once, when the sketch starts
{

  pinMode(M1_A, OUTPUT);
pinMode(M1_PWM, OUTPUT);
pinMode(M1_B, OUTPUT);

pinMode(M2_A, OUTPUT);
pinMode(M2_PWM, OUTPUT);
pinMode(M2_B, OUTPUT);

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
        M1_reverse(speed_val);
        M2_forward(speed_val);
         }

      //detects more light on right side of robot
      else if(sensor_right > sensor_left && (sensor_right - sensor_left) > threshold)
         {//go right
         M1_forward(speed_val);
         M2_reverse(speed_val);
         }
         
      //detects no light on both left and right side of robot
      else if(sensor_right == sensor_left && (sensor_right - sensor_left) < threshold)
         {//go right
         M1_forward(speed_val);
         M2_reverse(speed_val);
         }

      //light is about equal on both sides
      else
         {//go straight
        M1_forward(speed_val);
M2_forward(speed_val);
         }
   delay(25);                       // waits 25ms for a small delay to prevent crazy oscillations    
   digitalWrite(ledPin, LOW);    // sets the LED off   
}
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

void M2_forward(int y){
digitalWrite(M2_B, LOW);
digitalWrite(M2_A, HIGH);
analogWrite(M2_PWM, y);
}

void M2_reverse(int y){
digitalWrite(M2_A, LOW);
digitalWrite(M2_B, HIGH);
analogWrite(M2_PWM, y);
}

void M2_stop(){
digitalWrite(M2_B, LOW);
digitalWrite(M2_A, LOW);
digitalWrite(M2_PWM, LOW);
}




