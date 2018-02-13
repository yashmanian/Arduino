
int motor1Pin1 = 3;    // pin 2 on L293D
int motor1Pin2 = 4;    // pin 7 on L293D

void setup() {
  // set the switch as an input:

  // set all the other pins you're using as outputs:
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
}

void loop() {

    digitalWrite(motor1Pin1, LOW);   // set pin 2 on L293D low
    digitalWrite(motor1Pin2, HIGH);  // set pin 7 on L293D high
    delay(1000);  
    digitalWrite(motor1Pin1, HIGH);  // set pin 2 on L293D high
    digitalWrite(motor1Pin2, LOW);   // set pin 7 on L293D low
    delay(1000);
  
}
