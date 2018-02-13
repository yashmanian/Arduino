#include<SD.h> 
#define LED 8           // status LED for SD operations
#define BUFF_MAX 100   // size of GPS & SD buffers

File GPSlog;

void setup()
{
  Serial.begin(4800); // The LS20031 GPS receiver must be set to 4800 for program to work

  // You can use the statements below to send configuration commands to the LS20031 GPS.
  // But for this to work, the baud rate must be set on the LS20031 GPS receiver to 4800.
  // You can use the MiniGPS 1.4 utility to configure or query the LS20031 GPS receiver.
  //
  // LS20031 COMMANDS:
  // Serial.print("$PMTK251,4800*27\r\n");  // Set GPS baud rate
  // Serial.print("$PMTK314,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*2C\r\n"); // Set RMC to 5 fixes/second. 
  // Serial.print("$PMTK220,200*2C\r\n");  // GPS update rate at 5Hz
 
  pinMode(10, OUTPUT);   // Per SD library notes, pin 10 must be set to output
  pinMode(LED, OUTPUT);

  if (!SD.begin(4)) {        // SD card detected?
    digitalWrite(LED,LOW);   // turn off status LED if SD detection fails
    return;
  }
  else   digitalWrite(LED, HIGH); // turn on LED if SD detection is OK

  GPSlog = SD.open("GPS.log", O_CREAT | O_WRITE);  // open/append to a file GPS.log
  if (!GPSlog) {               // test if file can be opened
    digitalWrite(LED,LOW);     // turn off status LED if file open fails
    return;
  }
  else digitalWrite(LED, HIGH);  // turn on status LED if file open is OK
}

void loop()
{
  char inBuffer[BUFF_MAX];    // buffer used to read NMEA lines from GPS
  byte outBuffer[BUFF_MAX];   // buffer used to write NMEA lines to SD card
  int sizeBuffer = 0;        // counter of how many chars per line

// HERE WE DECLARE MORE OR LESS ANALOG SENSOR VARIABLES
  char an0[4], an1[4], an2[4];  // char variables to store analog pin values. Total 6 pins from 0-5

  while (Serial.available()>0)  // if serial data available from GPS
  {         
    sizeBuffer = Serial.readBytesUntil('\n', inBuffer, BUFF_MAX);  // read one NMEA line from GPS until end of line

//  THIS IS WHERE WE READ SENSOR VALUES
    itoa (analogRead(A0),  an0, 10);    // X read and convert numeric analog pin to char
    itoa (analogRead(A1),  an1, 10);    // Y  ..
    itoa (analogRead(A2),  an2, 10);    // Z  ..
    for (int i = 0; i < BUFF_MAX; i++) outBuffer[i] = inBuffer[i];   // create CSV file on SD 
    int j = 0;

    // THIS IS WHERE WE WRITE SENSOR DATA TO THE SD FILE
    if (GPSlog) {
      GPSlog.print(an0);    // write ANALOG0 (X) to SD
      GPSlog.print(" , ");      
      GPSlog.print(an1);    // write ANALOG1 (Y) to SD     
      GPSlog.print(" , ");      
      GPSlog.print(an2);    // write ANALOG2 (Z) to SD
      GPSlog.print(" , ");     
      // If you only want NMEA output logged, comment out all above GPSlog.print statements
      GPSlog.write(outBuffer, sizeBuffer);  // write GPS NMEA output to SD
      GPSlog.print("\r\n");     
      GPSlog.flush();
      digitalWrite(LED, HIGH);  // Keep LED on so long as SD logging is working.
    }
    else {
      // if the file didn't open, turn LED off
      digitalWrite(LED, LOW);  // turn LED off if writing to file fails
    }
  }
}
