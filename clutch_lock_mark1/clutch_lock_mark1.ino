int LED=13;
int motor1pin1=8;
int motor1pin2=9;
void setup() 
{

  Serial.begin(9600);
  pinMode(motor1pin1,OUTPUT);
  pinMode(motor1pin2,OUTPUT);
  pinMode(LED, OUTPUT);  
  Serial.println("Initialising....");
  delay(1000);
  Serial.println("Arduino_v_atmega328:");
  delay(1000);
    Serial.println("INPUT PASSWORD:");
}

void loop()  
{
  start:
const char passcode = 'manian';

    if (Serial.read() == passcode) 
    {
      const char l = 'lock';
      const char unl = 'unlock';
      Serial.println("lock or unlock?\n");
      if (Serial.read() == l)
      {
       digitalWrite(motor1pin1,HIGH);
       digitalWrite(motor1pin2,LOW);
       digitalWrite(LED,HIGH);
       delay(5000);
       Serial.println("locked");
      }
      else if (Serial.read() == unl)
      {
       digitalWrite(motor1pin1,LOW);
       digitalWrite(motor1pin2,HIGH);
       digitalWrite(LED,HIGH);
       delay(5000);
       Serial.println("unlocked");
      }
      else
      {
        Serial.println("incorrect password");
      }
  }
}
