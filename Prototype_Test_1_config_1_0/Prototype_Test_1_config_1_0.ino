int motor1pin1=6;
int motor1pin2=7;
int incomingByte = 0;
int LED=13;
void setup()
{
Serial.begin(9600);  
pinMode(motor1pin1,OUTPUT);
pinMode(motor1pin2,OUTPUT);
pinMode(LED,OUTPUT);
Serial.println("Initialising....");
delay(3000);
Serial.println("Atmega_328_30720_bytes");
delay(1000);
Serial.println("Clutch_lock_OS_v_2.0");
delay(1000);
Serial.println("Setting up communications....");
delay(3000);
Serial.println("press i to lock, j to unlock");
delay(1000);

}
void loop()
{
  if (Serial.available()>0)
{
  incomingByte=Serial.read();
  Serial.println(incomingByte);
  delay(10);
  if (incomingByte == 105)
  {
    digitalWrite(motor1pin1,HIGH);
    digitalWrite(motor1pin2,LOW);
    digitalWrite(LED,HIGH);
    delay(5000);
    digitalWrite(motor1pin1,LOW);
    digitalWrite(motor1pin2,LOW);
    Serial.println("Locked");
  }
  else if (incomingByte == 106)
  {
    digitalWrite(motor1pin1,LOW);
    digitalWrite(motor1pin2,HIGH);
    digitalWrite(LED,HIGH);
    delay(5000);
    digitalWrite(motor1pin1,LOW);
    digitalWrite(motor1pin2,LOW);
    Serial.println("UnLocked");
  }
  else
 {
    digitalWrite(motor1pin1,LOW);
    digitalWrite(motor1pin2,LOW);
    digitalWrite(LED,LOW);
    delay(25);
    Serial.println("Invalid function");
    }
 }
}
  
  
