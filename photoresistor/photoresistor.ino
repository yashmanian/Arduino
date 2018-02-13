
int lightPin = 0;  //define a pin for Photo resistor
int ledPin=13;     //define a pin for LED

void setup()
{
    Serial.begin(115200);  //Begin serial communcation
    pinMode( ledPin, OUTPUT );
}

void loop()
{
    Serial.println(analogRead(lightPin)); //Write the value of the photoresistor to the serial monitor.
    analogWrite(ledPin, analogRead(lightPin));  //send the value to the ledPin. Depending on value of resistor 
                                                //you have  to divide the value. for example, 
                                                //with a 10k resistor divide the value by 2, for 100k resistor divide by 4.
   delay(100); //short delay for faster response to light.
}
