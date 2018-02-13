int motor1pin1=6;
int motor1pin2=7;
int motor2pin1=8;
int motor2pin2=9;
int LED=13;
void setup()
{
pinMode(motor1pin1,OUTPUT);
pinMode(motor1pin2,OUTPUT);
pinMode(motor2pin1,OUTPUT);
pinMode(motor2pin2,OUTPUT);
pinMode(LED,OUTPUT);
}
void loop()
{
  digitalWrite(motor1pin1,HIGH);
  digitalWrite(motor1pin2,LOW);
  digitalWrite(motor2pin1,HIGH); 
  digitalWrite(motor2pin2,LOW);
  digitalWrite(LED,HIGH);
  delay(1000);
  digitalWrite(motor1pin1,LOW);
  digitalWrite(motor1pin2,HIGH);
  digitalWrite(motor2pin1,HIGH); 
  digitalWrite(motor2pin2,LOW);
  digitalWrite(LED,LOW);
  delay(1000);
  digitalWrite(motor1pin1,HIGH);
  digitalWrite(motor1pin2,LOW);
  digitalWrite(motor2pin1,LOW); 
  digitalWrite(motor2pin2,HIGH);
  digitalWrite(LED,HIGH);
  delay(1000);
  digitalWrite(motor1pin1,LOW);
  digitalWrite(motor1pin2,LOW);
  digitalWrite(motor2pin1,HIGH); 
  digitalWrite(motor2pin2,LOW);
  digitalWrite(LED,LOW);
  delay(1000);
  digitalWrite(motor1pin1,HIGH);
  digitalWrite(motor1pin2,LOW);
  digitalWrite(motor2pin1,LOW); 
  digitalWrite(motor2pin2,LOW);
  digitalWrite(LED,HIGH);
  delay(1000);
  digitalWrite(motor1pin1,LOW);
  digitalWrite(motor1pin2,HIGH);
  digitalWrite(motor2pin1,LOW); 
  digitalWrite(motor2pin2,HIGH);
  digitalWrite(LED,LOW);
  delay(1000);
  digitalWrite(motor1pin1,LOW);
  digitalWrite(motor1pin2,LOW);
  digitalWrite(motor2pin1,LOW); 
  digitalWrite(motor2pin2,LOW);
  digitalWrite(LED,HIGH);
  delay(1000);
}
