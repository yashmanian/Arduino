void setup() {
  Serial.begin(9600);      // open the serial port at 9600 bps:
}

void loop() {
    if( byte( Serial.read() == 'a' )) {
        Serial.print("\nHey!");       // print Hey
    }
}
