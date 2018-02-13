
/*
 Example sketch for the PS3 USB library - developed by Kristian Lauszus
 For more information visit my blog: http://blog.tkjelectronics.dk/ or
 send me an e-mail:  kristianl@tkjelectronics.com
 */

#include <PS3USB.h>
// Satisfy IDE, which only needs to see the include statment in the ino.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif

USB Usb;
/* You can create the instance of the class in two ways */
PS3USB PS3(&Usb); // This will just create the instance
//PS3USB PS3(&Usb,0x00,0x15,0x83,0x3D,0x0A,0x57); // This will also store the bluetooth address - this can be obtained from the dongle when running the sketch

int M1_A = 24;  //BROWN
int M1_PWM = 2; 
int M1_B = 22;  //GREEN

int M2_A = 26;  //GREEN
int M2_PWM = 3;
int M2_B = 28;  //BROWN

int M3_A = 32;  //BROWN
int M3_PWM = 4;
int M3_B=  30;  //GREEN

int M4_A = 34;  //BROWN
int M4_PWM = 5;
int M4_B=  36;  //GREEN


int count=0;    // for pneumatics
int count3=0; //for  inc cw and ccw speed
int flag=0; //inc cw and ccw speed
int i; // speed of cw and ccw
int axislen = 0; // Signal for standalone for axes

int servo_gate = 42;
int gripper =44 ;
int extension = 40;
int clamp = 38; 

void M1_ccw(int a)
{
digitalWrite(M1_B, LOW);
digitalWrite(M1_A, HIGH);
analogWrite(M1_PWM,a);
}

void M1_cw(int a)
{
digitalWrite(M1_A, LOW);
digitalWrite(M1_B, HIGH);
analogWrite(M1_PWM,a);
}

void M2_cw(int b)
{
digitalWrite(M2_B, LOW);
digitalWrite(M2_A, HIGH);
analogWrite(M2_PWM,b);
}

void M2_ccw(int b)
{
digitalWrite(M2_A, LOW);
digitalWrite(M2_B, HIGH);
analogWrite(M2_PWM,b);
}

void M3_ccw(int c)
{
digitalWrite(M3_B, LOW);
digitalWrite(M3_A, HIGH);
analogWrite(M3_PWM,c);
}

void M3_cw(int c)
{
digitalWrite(M3_A, LOW);
digitalWrite(M3_B, HIGH);
analogWrite(M3_PWM,c);
}

void M4_cw(int d)
{
digitalWrite(M4_B, LOW);
digitalWrite(M4_A, HIGH);
analogWrite(M4_PWM,d);
}

void M4_ccw(int d)
{
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

boolean printAngle;
uint8_t state = 0;

void setup() {
  Serial.begin(115200);
  Serial1.begin(9600);
  
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

  pinMode(servo_gate,OUTPUT);
  pinMode(gripper,OUTPUT);
  pinMode(extension,OUTPUT);
 pinMode(clamp,OUTPUT);

  digitalWrite(clamp,LOW);
   
  
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nPS3 USB Library Started"));
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
      
       float x = PS3.getAnalogHat(RightHatX);
       
        float y = PS3.getAnalogHat(LeftHatY);
        
        x=x-127.5; //center it at 0
        y=y-127.5; //for range 1000 - 2000
       
    float theta = atan2(y, x);
    float magnitude = sqrt((x*x)+(y*y));
    
    float vx = magnitude * cos(theta);
    float vy = magnitude * sin(theta);
    //const float sqrt3o2 = 1.0*sqrt(3)/2;
    
    //STEP 3. Find wheel vecotrs
    float w0 =  (1.3*vx + 1.3*vy)+20;                   // v dot [-1, 0] / 25mm
    float w1 =  (1.3*vx - 1.3*vy)-50; // v dot [1/2, -sqrt(3)/2] / 25mm
    float w2 =  (-1.3*vx - 1.3*vy)+20; // v dot [1/2, +sqrt(3)/2] / 25mm
    float w3 =  (-1.3*vx + 1.3*vy);
   
    
    
    boolean w0_ccw = w0 > 0 ? true : false;
    boolean w1_ccw = w1 > 0 ? true : false;
    boolean w2_ccw = w2 > 0 ? true : false;
    boolean w3_ccw = w3 > 0 ? true : false;
    
   
    byte w0_speed = (byte) map(abs(w0), 0, 255, 0, 255);
    byte w1_speed = (byte) map(abs(w1), 0, 255, 0, 255);
    byte w2_speed = (byte) map(abs(w2), 0, 255, 0, 255);
    byte w3_speed = (byte) map(abs(w3), 0, 255, 0, 255);

   
    Serial.print(" w0: ");
    Serial.print(w0_speed);
    if(w0_ccw) Serial.print(" CCW"); else Serial.print(" CW");
    Serial.print(" w1: ");
    Serial.print(w1_speed);
    if(w1_ccw) Serial.print(" CCW"); else Serial.print(" CW");
    Serial.print(" w2: ");
    Serial.print(w2_speed);
    if(w2_ccw) Serial.print(" CCW"); else Serial.print(" CW"); 
     Serial.print(" w3: ");
    Serial.print(w3_speed);
    if(w3_ccw) Serial.print(" CCW"); else Serial.print(" CW");
    
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

   //for motor 4
   if (w3_ccw)
   {
     M4_ccw(w3_speed);
   }
   else
   {
     M4_cw(w3_speed);
   }
  }
}
    // Analog button values can be read from almost all buttons
    if (PS3.getAnalogButton(L2) || PS3.getAnalogButton(R2)) {
      Serial.print(F("\r\nL2: "));
      Serial.print(PS3.getAnalogButton(L2));
      if (!PS3.PS3NavigationConnected) {
        Serial.print(F("\tR2: "));
        Serial.print(PS3.getAnalogButton(R2));
      }
    }
    if (PS3.getButtonClick(PS))
    {
      Serial.print(F("\r\nPS"));
//      PS3.disconnect();
    }
else{
    if (PS3.getButtonClick(TRIANGLE))     // bldc speed inc
    {count3++;
      Serial.print(F("\r\nTraingle"));
      Serial1.write("a"); 
      flag=1;           
      
    }
    if (PS3.getButtonClick(CIRCLE))
     {
      count++;
      Serial.print(F("\r\nCircle"));
      Serial.println("count=");
      Serial.println(count);
   
      if(count==1)
      {
        digitalWrite(servo_gate,HIGH);
      }
      if(count==2)
      {
        digitalWrite(servo_gate,LOW);
      }
      if(count==3)
      {
        digitalWrite(extension,HIGH);
      }
      if(count==4)
      {
        digitalWrite(clamp,HIGH);
      }
      if(count==5)
      {
       digitalWrite(extension,LOW); 
      }
      if(count==6)
      {
        digitalWrite(gripper,HIGH);
      }
      if(count==7)
      {
        digitalWrite(clamp,LOW);
      }
     }
     
    if (PS3.getButtonClick(CROSS))     // bldc speed dec
      {
        Serial1.write("b");
        count3--;
        Serial.print(F("\r\nCross"));   
       if(count3<1)
       {
        flag=0;
       }
      }
    if (PS3.getButtonClick(SQUARE))    // motor stop
     {
        Serial.print(F("\r\nSQUARE"));
          
  
        M1_stop();
        M2_stop();
        M3_stop();
        M4_stop();
        Serial.println(F("Motors Stopped"));
        delay(25);          
     }

  
    if (PS3.getButtonClick(RIGHT))
    {
      Serial.print(F("\r\nRight"));
      //PS3.setLedOff();
      //PS3.setLedOn(LED1);
      
    }
    if (PS3.getButtonClick(LEFT))
    {
      Serial.print(F("\r\nLeft"));
     // PS3.setLedOff();
      //PS3.setLedOn(LED3);
    }
    if (PS3.getButtonClick(UP))        //xaxis height inc 
    {
      Serial.print(F("\r\nUp"));
     // PS3.setLedOff();
     // PS3.setLedOn(LED4); 
     
    }
   if (PS3.getButtonClick(DOWN))     // xaxis height dec
   {      
      Serial.print(F("\r\nDown"));
     // PS3.setLedOff();
      //PS3.setLedOn(LED2);
      
    }
    
    if (PS3.getButtonClick(L1))
    {
      
      Serial.print(F("\r\nL1"));
     // Serial1.write("e");
      Serial1.write("c");  
    }
    if (PS3.getButtonClick(R1))
    {
    
      Serial.print(F("\r\nR1"));
     // Serial1.write("f");
      Serial1.write("d");
    }
    if (PS3.getButtonPress(L2))
    { 
      if(flag==0)
      {
        i=100;
      }
      if(flag==1)
      {
        i=200;
      }
        Serial.print(F("\r\nClockwise"));
        M1_cw(i);
        M2_cw(i);
        M3_cw(i);
        M4_cw(i);
        
        delay(7);
        M1_stop();
        M2_stop();
        M3_stop();
        M4_stop();
    }
      
    if (PS3.getButtonPress(R2))
     {
        Serial.print(F("\r\nCounter Clockwise"));
        M1_ccw(100);
        M2_ccw(100);
        M3_ccw(100);
        M4_ccw(100);
        
        delay(7);
        M1_stop;
        M2_stop();
        M3_stop();
        M4_stop();  
      }

    if (PS3.getButtonClick(SELECT)) {
      Serial.print(F("\r\nSelect - "));
     // PS3.printStatusString();
      Serial1.write("e");
    }
    if (PS3.getButtonClick(START))
    {
      Serial.print(F("\r\nStart"));
      count=0;
      digitalWrite(gripper,LOW);
      digitalWrite(extension,LOW);
      digitalWrite(servo_gate,LOW);
      digitalWrite(clamp,LOW);
    } 
    }
 #if 0   // Set this to 1 in order to see the angle of the controller
    if (printAngle) {
      Serial.print(F("\r\nPitch: "));
      Serial.print(PS3.getAngle(Pitch));
      Serial.print(F("\tRoll: "));
      Serial.print(PS3.getAngle(Roll));
    }
    #endif
  }
}
