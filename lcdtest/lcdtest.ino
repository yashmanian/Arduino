#include<LiquidCrystal.h>
LiquidCrystal lcd(3,8,9,10,11,12);
int ledpin=13;
void setup()
{
  lcd.begin(16,2);
  lcd.print("DAY 7, TEST 27:");
}
void loop()
{
  lcd.print("akdnaj");
  delay(1000);
  lcd.print("kefpsd");
  delay(1000);
  lcd.print("dascas");
  delay(1000);
}
  
  
