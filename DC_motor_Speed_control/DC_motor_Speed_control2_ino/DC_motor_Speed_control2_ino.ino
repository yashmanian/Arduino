int analoginput = A0;

int M1_A = 2;
int M1_PWM = 3;
int M1_B = 4;

int speed_val = 255;
int sensorValue=0;
void setup()
{
  Serial.begin(9600);
  
  pinMode(M1_A ,OUTPUT);
  pinMode(M1_PWM, OUTPUT);
  pinMode(M1_B, OUTPUT);
 
}

void loop()
{
  sensorValue = analogRead(analoginput);
  Serial.println(sensorValue);
  
  speed_val = map(sensorValue,0,1023,0,255);
  
  M1_start(speed_val);
  
}

void M1_start(int x)
{
  digitalWrite(M1_A, HIGH);
  digitalWrite(M1_B, LOW);
  digitalWrite(M1_PWM, x);
}
