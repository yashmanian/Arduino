int sensorvalue_y = 0;
int P1 = A0;
int v_ref = 512;
int v_diff = 0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  sensorvalue_y = analogRead(P1);
  
  v_diff = abs(sensorvalue_y - v_ref);
  
  Serial.println("V_diff:");
  Serial.println(v_diff);
  Serial.println("/n");
  delay(800);
}
