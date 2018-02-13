char INBYTE;
int IRpin = 1;                                    // analog pin for reading the IR sensor
int ledPin=13;
void setup() {
  Serial.begin(9600);  // start the serial port
  pinMode( ledPin, OUTPUT );
}

void loop() 
{
    float volts = analogRead(IRpin)*0.0048828125;   // value from sensor * (5/1024) - if running 3.3.volts then change 5 to 3.3
    float distance = 65*pow(volts, -1.10);          // worked out from graph 65 = theretical distance / (1/Volts)S - luckylarry.co.uk
    delay(100);                                     // arbitary wait time.
    Serial.println(distance); //Write the value of the photoresistor to the serial monitor.
    while (!Serial.available());   // stay here so long as COM port is empty   
    INBYTE = Serial.read();        // read next available byte
    analogWrite(ledPin, distance);
                                                //you have  to divide the value. for example, 
                                                //with a 10k resistor divide the value by 2, for 100k resistor divide by 4.
    delay(1000); //short delay for faster response to light.

}
