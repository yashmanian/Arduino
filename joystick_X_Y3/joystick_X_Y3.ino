int sensorvalue_y = 0;
int P1 = A0;
int v_ref = 512;
int v_diff = 0;
int v1 = 0;
int speed_val = 0;
int M1_A = 3;
int M1_PWM = 9;
int M1_B = 4;

void setup()
{
  Serial.begin(9600);

  pinMode(M1_A,OUTPUT);
  pinMode(M1_PWM,OUTPUT);
  pinMode(M1_B,OUTPUT);
}

void loop()
{
  sensorvalue_y = analogRead(P1);
  
  v_diff = abs(sensorvalue_y - v_ref);
  
  speed_val = map(v_diff,0,512,0,255);
  
  if(sensorvalue_y > v_ref && v_diff > 15)
  {
    M1_forward(speed_val);
  }
  
  if(sensorvalue_y < v_ref && v_diff < 15)
  {
    M1_reverse(speed_val);
  }
  Serial.println("V_diff:");
  Serial.println(v_diff);
  Serial.println("/n");
  Serial.println("Speed_val");
  Serial.println(speed_val);
  Serial.println("/n");
  Serial.println("Sensorvalue");
  Serial.println(sensorvalue_y);
  Serial.println("/n");
  
}

void M1_forward(int x){
digitalWrite(M1_A, LOW);
digitalWrite(M1_B, HIGH);
analogWrite(M1_PWM, x);
}

void M1_reverse(int x){
digitalWrite(M1_B, LOW);
digitalWrite(M1_A, HIGH);
analogWrite(M1_PWM, x);
}
  
