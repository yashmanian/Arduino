int sensorvalue = 0;
int p1 = A0;
int M1_A = 3;    // if using Ardumoto, change to pin 13
int M1_PWM = 9; 
int M1_B = 4; // if using Ardumoto, remove this variable
signed int x_direc = 0;
unsigned int x_speed = 0;
int speed_val = 255;

void setup()
{
  Serial.begin(9600);
  
  pinMode(M1_A, OUTPUT);
  pinMode(M1_PWM, OUTPUT);
  pinMode(M1_B, OUTPUT);
}

void loop()
{
  sensorvalue = analogRead(p1);
  x_direc = map(sensorvalue,0,1023,-20,20);
  x_speed =abs(x_direc);
  speed_val = map(x_speed,0,20,0,255);
   if(x_direc>0)
   {
     M1_right(speed_val);
     Serial.println("Right");
   }
   else if(x_direc<0)
   {
     M1_left(speed_val);
     Serial.println("Left");
   }
   Serial.println("Sensor Value:");
   Serial.println(sensorvalue);
   Serial.println("\n");
   Serial.println("Direction:");
   Serial.println(x_direc);
   Serial.println("\n");
   Serial.println("Xspeed:");
   Serial.println(x_speed);
   Serial.println("\n");
   Serial.println("Speed:");
   Serial.println(speed_val);
   Serial.println("\n");
}

void M1_right(int x)
{
  digitalWrite(M1_B, LOW);
  digitalWrite(M1_A, HIGH);
  analogWrite(M1_PWM, x);
}

void M1_left(int x)
{
  digitalWrite(M1_A, LOW);
  digitalWrite(M1_B, HIGH);
  analogWrite(M1_PWM, x);
}
