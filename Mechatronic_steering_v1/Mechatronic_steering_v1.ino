int sensorPin1 = A0;    // input pin for the potentiometer1
int sensorPin2 = A1;    // input pin for the potentiometer1
int ledPin = 13;      // select the pin for the LED
int sensorValue1 = 0;  // variable to store the value coming from the potentiometer1
int sensorValue2 = 0;  // variable to store the value coming from the potentiometer2
int modePin = 5;
int val = 0;        //if val is HIGH, turn on ratio 1,else turn on ratio 2
int M1 = 8;  //motor Pin 1
int M2 = 9;  //motor Pin 2
void setup()
{
    pinMode(ledPin,OUTPUT);
    pinMode(modePin,INPUT);
    pinMode(M1,OUTPUT);
    pinMode(M2,OUTPUT);
}
void loop()
{
     sensorValue1 = analogRead(sensorPin1);
     sensorValue2 = analogRead(sensorPin2);
     val = digitalRead(modePin);
     if(val == HIGH)
     {
       if(sensorValue1<512)
       {
         while(sensorValue1 != sensorValue2)
         {
           digitalWrite(M1,HIGH);
           digitalWrite(M2,LOW);
         }
       }
     }
     else
     {
       if(sensorValue1>512)
       {
         while(sensorValue1 != sensorValue2)
         {
           digitalWrite(M1,LOW);
           digitalWrite(M2,HIGH);
         }
       }
     }
}
   
