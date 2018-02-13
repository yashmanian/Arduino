int M1_A = 4;    
int M1_PWM = 3; 
int M1_B = 5; //pwm
int potpin0 = A0;
int potpin1 = A1;
int sensorValue0 = 0;
int sensorValue1 = 0;


// LED pin attached to Arduino D13
int LED = 13;
// variable to store speed value
int speed_val = 255;
void setup()
{

// declare outputs
pinMode(LED, OUTPUT);

pinMode(M1_A, OUTPUT);
pinMode(M1_PWM, OUTPUT);
pinMode(M1_B, OUTPUT);


// turn motors Off by default
M1_stop();

delay(500);

}
void loop()
{
}

/////////// motor functions ////////////////

void M1_reverse(int x){
digitalWrite(M1_B, LOW);
digitalWrite(M1_A, HIGH);
analogWrite(M1_PWM, x);
}

void M1_forward(int x){
digitalWrite(M1_A, LOW);
digitalWrite(M1_B, HIGH);
analogWrite(M1_PWM, x);
}

void M1_stop(){
digitalWrite(M1_B, LOW);
digitalWrite(M1_A, LOW);
digitalWrite(M1_PWM, LOW);
}



  
