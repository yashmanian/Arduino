#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


void setup()
{
  lcd.clear(); 
  lcd.begin(16, 2);
  lcd.setCursor(0,0); 
  lcd.print("Value is"); 
}

void loop()
{
  int val = analogRead(0);
  lcd.setCursor(0, 1);  
  lcd.print(val);              

  delay(500);
}
