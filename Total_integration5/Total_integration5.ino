/*
 Example sketch for the PS3 Bluetooth library - developed by Kristian Lauszus
 For more information visit my blog: http://blog.tkjelectronics.dk/ or
 send me an e-mail:  kristianl@tkjelectronics.com
 */

#include <PS3BT.h>       // PS3 headers
#include <usbhub.h>       // PS3 headers
// Satisfy IDE, which only needs to see the include statment in the ino.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
USB Usb; 
//USBHub Hub1(&Usb); // Some dongles have a hub inside

BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
/* You can create the instance of the class in two ways */
PS3BT PS3(&Btd); // This will just create the instance
//PS3BT PS3(&Btd, 0x00, 0x15, 0x83, 0x3D, 0x0A, 0x57); // This will also store the bluetooth address - this can be obtained from the dongle when running the sketch


int M1_A = 26;  //BROWN
int M1_PWM = 2; 
int M1_B = 28;  //GREEN

int M2_A = 30;  //GREEN
int M2_PWM = 3;
int M2_B = 32;  //BROWN

int M3_A = 34;  //BROWN
int M3_PWM = 4;
int M3_B=  36;  //GREEN

int M4_A = 38;  //BROWN
int M4_PWM = 5;
int M4_B=  40;  //GREEN     `

int GATE_SERVE = 42;

int GATE_RALLY_1 = 22;
int GATE_RALLY_2 = 24;


void M1_ccw(int a){
digitalWrite(M1_B, LOW);
digitalWrite(M1_A, HIGH);
analogWrite(M1_PWM,a);
}

void M1_cw(int a){
digitalWrite(M1_A, LOW);
digitalWrite(M1_B, HIGH);
analogWrite(M1_PWM,a);
}

void M2_cw(int b){
digitalWrite(M2_B, LOW);
digitalWrite(M2_A, HIGH);
analogWrite(M2_PWM,b);
}

void M2_ccw(int b){
digitalWrite(M2_A, LOW);
digitalWrite(M2_B, HIGH);
analogWrite(M2_PWM,b);
}

void M3_ccw(int c){
digitalWrite(M3_B, LOW);
digitalWrite(M3_A, HIGH);
analogWrite(M3_PWM,c);
}

void M3_cw(int c){
digitalWrite(M3_A, LOW);
digitalWrite(M3_B, HIGH);
analogWrite(M3_PWM,c);
}

void M4_ccw(int d){
digitalWrite(M4_B, LOW);
digitalWrite(M4_A, HIGH);
analogWrite(M4_PWM,d);
}

void M4_cw(int d){
digitalWrite(M4_A, LOW);
digitalWrite(M4_B, HIGH);
analogWrite(M4_PWM,d);
}

void M1_stop(){
digitalWrite(M1_B, LOW);
digitalWrite(M1_A, LOW);
analogWrite(M1_PWM, 0);
}
void M2_stop(){
digitalWrite(M2_B, LOW);
digitalWrite(M2_A, LOW);
analogWrite(M2_PWM, 0);
}
void M3_stop(){
digitalWrite(M3_B, LOW);
digitalWrite(M3_A, LOW);
analogWrite(M3_PWM, 0);
}

void M4_stop(){
digitalWrite(M4_B, LOW);
digitalWrite(M4_A, LOW);
analogWrite(M4_PWM, 0);
}

boolean printTemperature;
boolean printAngle;

void setup() {
  pinMode(GATE_RALLY_1,OUTPUT); // rally solenoid valve 1
  pinMode(GATE_RALLY_2,OUTPUT); // rally solenoid valve 2

  
  pinMode(GATE_SERVE,OUTPUT);  //Solenoid Valve pin service ka
  Serial.begin(115200);
  
  pinMode(M1_A, OUTPUT);
  pinMode(M1_PWM, OUTPUT);
  pinMode(M1_B, OUTPUT);

  pinMode(M2_A, OUTPUT);
  pinMode(M2_PWM, OUTPUT);
  pinMode(M2_B, OUTPUT);

  pinMode(M3_A, OUTPUT);
  pinMode(M3_PWM, OUTPUT);
  pinMode(M3_B, OUTPUT);
  
  pinMode(M4_A, OUTPUT);
  pinMode(M4_PWM, OUTPUT);
  pinMode(M4_B, OUTPUT);

  
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));
}
void loop() {
  Usb.Task();
  
  if (PS3.PS3Connected || PS3.PS3NavigationConnected) {
    if (PS3.getAnalogHat(LeftHatX) > 137 || PS3.getAnalogHat(LeftHatX) < 117 || PS3.getAnalogHat(LeftHatY) > 137 || PS3.getAnalogHat(LeftHatY) < 117 || PS3.getAnalogHat(RightHatX) > 137 || PS3.getAnalogHat(RightHatX) < 117 || PS3.getAnalogHat(RightHatY) > 137 || PS3.getAnalogHat(RightHatY) < 117) {
      Serial.print(F("\r\nLeftHatX: "));
      Serial.print(PS3.getAnalogHat(LeftHatX));
      Serial.print(F("\tLeftHatY: "));
      Serial.print(PS3.getAnalogHat(LeftHatY));
      if (PS3.PS3Connected) { // The Navigation controller only have one joystick
        Serial.print(F("\tRightHatX: "));
        Serial.print(PS3.getAnalogHat(RightHatX));
        Serial.print(F("\tRightHatY: "));
        Serial.print(PS3.getAnalogHat(RightHatY));
        
        int x = PS3.getAnalogHat(LeftHatX);
        int y = PS3.getAnalogHat(LeftHatY);
        
        x=x-127; //center it at 0
        y=y-127; //for range 1000 - 2000
       
    float theta = atan2(y, x);
    float magnitude = sqrt((x*x)+(y*y));
    
    float vx = magnitude * cos(theta);
    float vy = magnitude * sin(theta);
    const float sqrt3o2 = 1.0*sqrt(3)/2;
    
    //STEP 3. Find wheel vecotrs
    float w0 = -vx;                   // v dot [-1, 0] / 25mm
    float w1 = 0.5*vx - sqrt3o2 * vy*2; // v dot [1/2, -sqrt(3)/2] / 25mm
    float w2 = 0.5*vx + sqrt3o2 * vy*2; // v dot [1/2, +sqrt(3)/2] / 25mm
    
    boolean w0_ccw = w0 < 0 ? true : false;
    boolean w1_ccw = w1 < 0 ? true : false;
    boolean w2_ccw = w2 < 0 ? true : false;
   
    byte w0_speed = (byte) map(abs(w0), 0, 255, 0, 255);
    byte w1_speed = (byte) map(abs(w1), 0, 255, 0, 255);
    byte w2_speed = (byte) map(abs(w2), 0, 255, 0, 255);
    
    if(x>=-17 && x<36 && y<=-121)
    {
      w1_speed=255;
      w2_speed=255;
    }
      
    if(y>=123 && x>=-17 && x<36)
    {
       w1_speed=255;
       w2_speed=255;
    }
     
    if(x<-115 && y >-42 && y<26)
    {
     w0_speed = 2*w0_speed;
     w1_speed = 2*w1_speed; 
     w2_speed = 2*w2_speed;
    }
       
    if(x>124 && y >-39 && y<26)
    {
     w0_speed = 2*w0_speed;
     w1_speed = 2*w1_speed; 
     w2_speed = 2*w2_speed;
     if(w0_speed==0)
     {
       w0_speed=254;
     }
    }
    
    Serial.print(" w0: ");
    Serial.print(w0_speed);
    if(w0_ccw) Serial.print(" CCW"); else Serial.print(" CW");
    Serial.print(" w1: ");
    Serial.print(w1_speed);
    if(w1_ccw) Serial.print(" CCW"); else Serial.print(" CW");
    Serial.print(" w2: ");
    Serial.print(w2_speed);
    if(w2_ccw) Serial.print(" CCW"); else Serial.print(" CW"); 
    
    Serial.println();
   // for motor 1 
   if (w0_ccw)
   {
    M1_ccw(w0_speed);
   }
   else
   {
     M1_cw(w0_speed);
   }
   
   //for motor 2
   if (w1_ccw)
   {
     M2_ccw(w1_speed);
   }
   else
   {
     M2_cw(w1_speed);
   }
   
   //for motor 3
   if (w2_ccw)
   {
     M3_ccw(w2_speed);
   }
   else
   {
     M3_cw(w2_speed);
   }
  }
 }

    //Analog button values can be read from almost all buttons
    /*if (PS3.getAnalogButton(L2) || PS3.getAnalogButton(R2)) {
      Serial.print(F("\r\nL2: "));
      Serial.print(PS3.getAnalogButton(L2));
      if (PS3.PS3Connected) {
        Serial.print(F("\tR2: "));
        Serial.print(PS3.getAnalogButton(R2));
      }
    }*/
    
    if(PS3.getAnalogButton(L2)){
        Serial.print(F("\r\nL2: "));
        Serial.print(PS3.getAnalogButton(L2));
        M1_cw(PS3.getAnalogButton(L2));
        M2_cw(PS3.getAnalogButton(L2));
        M3_cw(PS3.getAnalogButton(L2));
    }
    
    if(PS3.getAnalogButton(R2)){
        Serial.print(F("\r\nR2: "));
        Serial.print(PS3.getAnalogButton(R2));
        M1_ccw(PS3.getAnalogButton(R2));
        M2_ccw(PS3.getAnalogButton(R2));
        M3_ccw(PS3.getAnalogButton(R2));
    }
    
    if (PS3.getButtonClick(PS)) {
      Serial.print(F("\r\nPS"));
      PS3.disconnect();
    }
    else {
      if (PS3.getButtonClick(TRIANGLE))  // Rally actuation
      { 
        digitalWrite(GATE_RALLY_1,HIGH);
        delay(500);
        digitalWrite(GATE_RALLY_1,LOW);
        Serial.print(F("\r\nTraingle"));
      }
      if (PS3.getButtonClick(CIRCLE))  // Rally actuation
      {
        digitalWrite(GATE_RALLY_2,HIGH);
        delay(500);
        digitalWrite(GATE_RALLY_2,LOW);
        Serial.print(F("\r\nCircle"));
      }

      if (PS3.getButtonClick(SQUARE))  
        {
         Serial.print(F("\r\nSquare"));
         digitalWrite(23,LOW);
         digitalWrite(25,HIGH);
        
        delay(140);
        
        
         digitalWrite(23,HIGH);
         digitalWrite(25,LOW);
         delay(123);
         
         digitalWrite(23,LOW);
         digitalWrite(25,LOW);

         
         digitalWrite(GATE_SERVE,HIGH); // Solenoid activates
         
         delay(1500);
         digitalWrite(23,LOW);
         digitalWrite(25,LOW);
         digitalWrite(GATE_SERVE,LOW);  // bring it back to its original position

        }
      }
              
       if(PS3.getButtonPress(CROSS))
       {
        M1_stop();
        M2_stop();
        M3_stop();
        M4_stop();
        Serial.println(F("Motors Stopped"));
       }
      if (PS3.getButtonClick(UP)) {
        Serial.print(F("\r\nUp"));
        if (PS3.PS3Connected) {
          PS3.setLedOff();
          PS3.setLedOn(LED4);
        }
      }
      if (PS3.getButtonClick(RIGHT)) {
        Serial.print(F("\r\nRight"));
        if (PS3.PS3Connected) {
          PS3.setLedOff();
          PS3.setLedOn(LED1);
        }
      }
      if (PS3.getButtonClick(DOWN)) {
        Serial.print(F("\r\nDown"));
        if (PS3.PS3Connected) {
          PS3.setLedOff();
          PS3.setLedOn(LED2);
        }
      }
      if (PS3.getButtonClick(LEFT)) {
        Serial.print(F("\r\nLeft"));
        if (PS3.PS3Connected) {
          PS3.setLedOff();
          PS3.setLedOn(LED3);
        }
      }
      if (PS3.getButtonPress(L1)) // Rally motor rotation
      {
        Serial.println("Left rotation");
        M4_cw(75);
        delay(20);
        M4_stop();
      }
      if (PS3.getButtonPress(R1)) // Rally motor rotation
      {
        Serial.println("Right rotation");
        M4_ccw(75);
        delay(20);
        M4_stop();
      }
     /* if (PS3.getButtonPress(L2)) // Robot rotation
       {
        Serial.print(F("\r\nClockwise"));
        M1_cw(95);
        M2_cw(95);
        M3_cw(95);
        
        delay(20);
        M1_stop();
        M2_stop();
        M3_stop();
       }
      
      if (PS3.getButtonPress(R2)) //Robot rotation
      {
        Serial.print(F("\r\nCounter Clockwise"));
        M1_ccw(95);
        M2_ccw(95);
        M3_ccw(95);
        
        delay(20);
        M1_stop();
        M2_stop();
        M3_stop();  
      }*/

      if (PS3.getButtonClick(L3))
        Serial.print(F("\r\nL3"));
      
      if (PS3.getButtonClick(R3))
        Serial.print(F("\r\nR3"));

      if (PS3.getButtonClick(SELECT)) {
        Serial.print(F("\r\nSelect - "));
        PS3.printStatusString();
      }
      if (PS3.getButtonClick(START)) {
        Serial.print(F("\r\nStart"));
        printAngle = !printAngle;
      }
    
    }
#if 1 // Set this to 1 in order to see the angle of the controller
    if (printAngle) {
      Serial.print(F("\r\nPitch: "));
      Serial.print(PS3.getAngle(Pitch));
      Serial.print(F("\tRoll: "));
      Serial.print(PS3.getAngle(Roll));
    }
#endif
  }
