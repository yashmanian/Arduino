#include <Password.h>

Password password = Password( "1234" );
int motor1pin1=8;
int motor1pin2=9;

byte currentLength = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(motor1pin1,OUTPUT);
  pinMode(motor1pin2,OUTPUT);
  Serial.println("Initialising....");
  delay(3000);
  Serial.println("clutch_lock_mechanism_os_v1.6: ");
  delay(1000);
  Serial.print("Atmega_328_30720_bytes\n ");
  delay(1000);
  Serial.print("Lock commannd : l\n");
  Serial.print("UnLock commannd : u\n");
  Serial.print("Enter Password \n");
}

void loop()
{
  if (Serial.available())
  {
    char input = Serial.read();
    switch (input)
    {
      case '!': //reset password
        password.reset();
        currentLength = 0;
        Serial.println("\tPassword is reset!");
      break;
      case '?': //evaluate password
        if (password.evaluate())
        {
          Serial.println("\tlock or unlock?");
          char command=Serial.read();
          switch (command)
        {
          case 'l':
          digitalWrite(motor1pin1,HIGH);
          digitalWrite(motor1pin2,LOW);
          delay(5000);
          Serial.println("\tLocked");
          break;
          case 'u':
          digitalWrite(motor1pin1,LOW);
          digitalWrite(motor1pin2,HIGH);
          delay(5000);
          Serial.println("\tUnlocked");
          break;
        }
        }
        else
        {
          Serial.println("\tincorrect password");
        }
      break;
      default: 
        password.append(input);
        currentLength++;
        
        //Print some feedback.
        Serial.print("Enter password: ");
        for (byte i=0; i<currentLength; i++)
        {
          Serial.print('*');
        }
        Serial.println();
     }
  }
}

