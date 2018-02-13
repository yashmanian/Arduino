float voltage = 0;
float LastVoltage = 0;
float rate = 0;
float diff = 0;
unsigned long lastTime = 0;
unsigned long dt = 100; // dt in milliseconds
int M1_A = 4;    
int M1_PWM = 11; 
int M1_B = 5; //pwm
// LED pin attached to Arduino D13
int LED = 13;
int sensorValue = 0;
// variable to store speed value
int speed_val = 255;
void setup() 
{
  Serial.begin(9600);
  // declare outputs
pinMode(LED, OUTPUT);

pinMode(M1_A, OUTPUT);
pinMode(M1_PWM, OUTPUT);
pinMode(M1_B, OUTPUT);



}

void loop() 
{
  if (millis() - lastTime  >= dt)   // wait for dt milliseconds
  {
    lastTime = millis();
    sensorValue = analogRead(A0);
    voltage = sensorValue * (5.0 / 1023.0); // this line changed !!

    Serial.print("SensorValue: ");
    Serial.println(sensorValue);
    Serial.print("Last voltage: ");
    Serial.println(LastVoltage, 4);
    Serial.print("Current voltage: ");
    Serial.println(voltage, 4 );

    rate = (voltage-LastVoltage);
    diff = (1000*rate/dt);
    Serial.print("dV/dt: ");
    Serial.println(diff, 4); 
   Serial.println(); 

    LastVoltage = voltage;
  }

//control code here
if(sensorValue>=128)
{
  if(diff!=0.0000)
  {
  M1_reverse(speed_val);
  delay(25);
  digitalWrite(LED, HIGH);
  }
}
else if(sensorValue<=128)
{
  if(diff!=0.0000)
  {
  M1_forward(speed_val);
  delay(25);
  digitalWrite(LED, HIGH);
  }
}


}
/////////// motor functions ////////////////

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

