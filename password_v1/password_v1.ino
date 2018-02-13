int LED=13;
void setup() 
{
pinMode(LED, OUTPUT);
  Serial.begin(9600);
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
        Serial.println("led on");
        digitalWrite(LED,HIGH);
        delay(1000);
        Serial.println("led off");
        digitalWrite(LED,LOW);
                delay(1000);
        Serial.println("led blink");
        digitalWrite(LED,HIGH); 
        delay(500);
        digitalWrite(LED,LOW); 
        delay(500);
        digitalWrite(LED,HIGH); 
        delay(500);
        digitalWrite(LED,LOW); 
        delay(500);
        digitalWrite(LED,HIGH); 
        delay(500);
        digitalWrite(LED,LOW); 
        delay(500);
    }
  }
