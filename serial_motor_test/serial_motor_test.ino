int motorpin1=4;
int motorpin2=5;
int LED=13;
int incomingByte=0;
int pwmpin = 3;
int x =127;

void setup()
{
  Serial.begin(9600);
  
  pinMode(motorpin1,OUTPUT);
  pinMode(motorpin2,OUTPUT);
  pinMode(pwmpin,OUTPUT);
  pinMode(LED,OUTPUT);
  Serial.println("Serial Recieve enabled");
 }
void loop()
{
if (Serial.available()>0)
{
     incomingByte = Serial.read();
     Serial.println(incomingByte);
     if (incomingByte == 119)
  {
    digitalWrite(motorpin1,HIGH); 
    digitalWrite(motorpin2,LOW);
    digitalWrite(LED,HIGH);
    delay(2000);
  }
 
    
    else if(incomingByte == 115)
  {
    digitalWrite(motorpin1,LOW); 
    digitalWrite(motorpin2,HIGH);
    digitalWrite(LED,HIGH);
    delay(2000);
  }
   else if(incomingByte == 97)
  {
    x = x + 5;
    analogWrite(pwmpin,x);
  }
  else if(incomingByte == 100)
  {
    x = x - 5;
    analogWrite(pwmpin,x);
  }

 else
 {
    digitalWrite(motorpin1,LOW); 
    digitalWrite(motorpin2,LOW);
    digitalWrite(LED,LOW);
 }
 }
}
