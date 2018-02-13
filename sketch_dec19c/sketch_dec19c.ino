int cnt = 0;    // Counter
 
 void setup() {
   Serial.begin(9600);   // Initialization
 }
 
 void loop() {
   cnt++;
   Serial.print("Hello BB from Arduino! Counter:");  // print message
   Serial.println(cnt);    // print counter
   delay(1000);   // wait 1 sec
 }
