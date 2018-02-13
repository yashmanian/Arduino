float Voltage0 = 0;
float Voltage1 = 0;
float rate_of_change = 0;
float diff = 0;
unsigned long lastTime = 0;
unsigned long dt = 100; // dt in milliseconds
int M1_A = 4;    
int M1_PWM = 3; //PWM
int M1_B = 5; 
// LED pin attached to Arduino D13
int LED = 13;

// variable to store speed value
int speed_val = 135;
void setup() 
{
  Serial.begin(9600);
  // declare outputs
  pinMode(LED, OUTPUT);
  
  pinMode(M1_A, OUTPUT);
  pinMode(M1_PWM, OUTPUT);
  pinMode(M1_B, OUTPUT);
  
  
  // turn motors off by default
  M1_stop();
}

void loop() 
{
  if (millis() - lastTime  >= dt)   // delay for dt milliseconds
  {
    lastTime = millis();
    int sensorValue = analogRead(A0);
    Voltage0 = sensorValue * (5.0 / 1023.0); // convert ADC value to voltage

    Serial.print("SensorValue: ");
    Serial.println(sensorValue);
    Serial.print("Last voltage: ");
    Serial.println(Voltage1, 4);
    Serial.print("Current voltage: ");
    Serial.println(Voltage0, 4 );

    rate_of_change = (Voltage0-Voltage1);
    diff = (1000*rate_of_change/dt);
    Serial.print("dV/dt: ");
    Serial.println(diff, 4); 
    Serial.println(); 

    Voltage1 = Voltage0;
  }

//control code here
if(diff<=-0.05)
{
  M1_reverse(speed_val);
  delay(20);
  digitalWrite(LED, HIGH);
}
else if(diff>=0.05)
{
  M1_forward(speed_val);
  delay(20);
  digitalWrite(LED, HIGH);
}
else if(diff<-0.05 && diff>0.05)
{
  M1_stop();
  delay(20);
}

}
/////////// motor functions ////////////////

void M1_reverse(int x)
{
digitalWrite(M1_B, LOW);
digitalWrite(M1_A, HIGH);
analogWrite(M1_PWM, x);
}

void M1_forward(int x)
{
digitalWrite(M1_A, LOW);
digitalWrite(M1_B, HIGH);
analogWrite(M1_PWM, x);
}

void M1_stop()
{
digitalWrite(M1_B, LOW);
digitalWrite(M1_A, LOW);
digitalWrite(M1_PWM, LOW);
}

