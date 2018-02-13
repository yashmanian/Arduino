#include <LiquidCrystal.h>
LiquidCrystal lcd(3, 5, 9, 10, 11, 12);

volatile float time = 0;
volatile float time_last = 0;
volatile int rpm_array[5] = {0,0,0,0,0};
int ledpin = 13;

void setup()
{
  //Digital Pin 2 Set As An Interrupt
 attachInterrupt(0, fan_interrupt, FALLING);

  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Current RPM:");
  pinMode(ledpin,OUTPUT);
}

//Main Loop To Calculate RPM and Update LCD Display
void loop()
{
  int rpm = 0;
  
  while(1){    

     //Slow Down The LCD Display Updates
  delay(400);
  
  //Clear The Bottom Row
  lcd.setCursor(0, 1);
  lcd.print("                ");   
  
  //Update The Rpm Count
  lcd.setCursor(0, 1);
  lcd.print(rpm);   

  ////lcd.setCursor(4, 1);
  ////lcd.print(time);   

  //update the RPM
  if(time > 0)
  {
    //average of 5 samples of data
      rpm_array[0] = rpm_array[1];
      rpm_array[1] = rpm_array[2];
      rpm_array[2] = rpm_array[3];
      rpm_array[3] = rpm_array[4];
      rpm_array[4] = 60*(1000000/(time*6));    
    //Last 5 Average RPM Counts
      rpm = (rpm_array[0] + rpm_array[1] + rpm_array[2] + rpm_array[3] + rpm_array[4]) / 5;
      digitalWrite(ledpin,HIGH);
  }
 
 }
}

//IR Break-Beam Interrupt
void fan_interrupt()
{
   time = (micros() - time_last); 
   time_last = micros();
}
