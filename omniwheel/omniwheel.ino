// OmniWheels
//open-electronics.org
//by Mirco Segatello
 
#define IRpin 6              // pin for IR sensor
#define SIGNAL_SIZE 32       // number bit of sequence
#define SIGNAL_START 1600    // width bit start
#define SIGNAL_0_min 150     // width bit 0 min
#define SIGNAL_0_max 250     // width bit 0 max
#define SIGNAL_1_min 450     // width bit 1 min
#define SIGNAL_1_max 650     // width bit i max
unsigned int SignalWidth[SIGNAL_SIZE];
byte yaw, pitch, throttle, trim;
 
#define DIRA_pin 2
#define PWMA_pin 3
#define DIRB_pin 8
#define PWMB_pin 9
#define DIRC_pin 12
#define PWMC_pin 10
#define DIRD_pin 4
#define PWMD_pin 5
 
float motA, motB, motC;
int PWMA, PWMB, PWMC;
 
int i;
 
 
void setup()
{
  Serial.begin(9600);
  pinMode(IRpin, INPUT);
  pinMode(DIRA_pin, OUTPUT);    
  pinMode(DIRB_pin, OUTPUT);  
  pinMode(DIRC_pin, OUTPUT); 
  analogWrite(PWMA, 0); 
  analogWrite(PWMB, 0);
  analogWrite(PWMC, 0);
  Serial.println("Wait IR Signal...");
}
 
void loop()
{
  if(IR_Receive()==0)
  {
    Serial.print("yaw=");
    Serial.print(yaw, DEC);
    Serial.print ("\tpitch=");
    Serial.print(pitch, DEC);
    Serial.print ("\tthrottle=");    
    Serial.print(throttle, DEC);
    Serial.print ("\ttrim=");    
    Serial.print(trim, DEC);
    Serial.println();    
    SetMotor();
    delay(200);
  }
}
 
void SetMotor()
{
 
  motA = 4.0 * (-0.5* float(63-yaw)-0.866*float(63-pitch)) + float(63-trim);
  motB = 4.0 * (-0.5* float(63-yaw)+0.866*float(63-pitch)) + float(63-trim);
  motC = 4.0 * (float(63-yaw)) + float(63-trim);
 
  PWMA = int(constrain(motA,-255,255));
  PWMB = int(constrain(motB,-255,255));
  PWMC = int(constrain(motC,-255,255));  
   
  Serial.print("PWMA=");
  Serial.print(PWMA);
  Serial.print("\tPWMB=");
  Serial.print(PWMB);
  Serial.print("\tPWMC=");
  Serial.println(PWMC);
   
  Serial.println();
 
  if (PWMA < 0)
  {
     analogWrite(PWMA_pin, abs(PWMA));
     digitalWrite(DIRA_pin, HIGH);
  }
  else
  {
     analogWrite(PWMA_pin, PWMA);
     digitalWrite(DIRA_pin, LOW);     
  }  
 
   
  if (PWMB < 0)
  {
     analogWrite(PWMB_pin, abs(PWMB));
     digitalWrite(DIRB_pin, HIGH);
  }
  else
  {
     analogWrite(PWMB_pin, PWMB);
     digitalWrite(DIRB_pin, LOW);     
  } 
   
 
  if (PWMC < 0)
  {
     analogWrite(PWMC_pin, abs(PWMC));
     digitalWrite(DIRC_pin, HIGH);
  }
  else
  {
     analogWrite(PWMC_pin, PWMC);
     digitalWrite(DIRC_pin, LOW);     
  }  
  
}
 
 
int IR_Receive()
{
  int Status=0;
  while(pulseIn(IRpin, HIGH)  < SIGNAL_START)
  {
  }
 
  for(i=0; i < SIGNAL_SIZE; i++)
  {
    SignalWidth[i]=pulseIn(IRpin, HIGH);
  }
 
  yaw=0;
  pitch=0;
  throttle=0;
  trim=0;
   
  for( i=1; i < 8; i++)
  {    
    if (SignalWidth[i] > SIGNAL_0_min && SignalWidth[i] < SIGNAL_0_max)
      bitClear(yaw, 7-i); 
   else if (SignalWidth[i] > SIGNAL_1_min &&   SignalWidth[i] < SIGNAL_1_max)
      bitSet(yaw, 7-i);
   else
     //Serial.print("Error");  
     Status = -1;
  }
   
   for(i=1; i < 8; i++)
   {    
    if (SignalWidth[i+8] > SIGNAL_0_min && SignalWidth[i+8] < SIGNAL_0_max)
      bitClear(pitch, 7-i); 
   else if (SignalWidth[i+8] > SIGNAL_1_min &&   SignalWidth[i+8] < SIGNAL_1_max)
      bitSet(pitch, 7-i);
   else
          Status = -1;//Serial.print("Error");  
  } 
   
  for(int i=1; i < 8; i++)
  {    // il primo bit è sempre zero
    if (SignalWidth[i+16] > SIGNAL_0_min && SignalWidth[i+16] < SIGNAL_0_max)
      bitClear(throttle , 7-i); //viene trasmesso prima il più significativo
   else if (SignalWidth[i+16] > SIGNAL_1_min &&   SignalWidth[i+16] < SIGNAL_1_max)
 
      bitSet(throttle , 7-i);
   else
          Status = -1;//Serial.print("Error");  
  }
   
  for(int i=1; i < 8; i++)
  {    
    if (SignalWidth[i+24 ] > SIGNAL_0_min && SignalWidth[i+24] < SIGNAL_0_max)
      bitClear(trim , 7-i); 
   else if (SignalWidth[i+24] > SIGNAL_1_min &&   SignalWidth[i+24] < SIGNAL_1_max)
      bitSet(trim , 7-i);
   else
          Status = -1;//Serial.print("Error");  
  }
     
    // yaw è modificato da trim 
    int crz  = float(yaw)-0.3*float(trim-63);  
    crz = constrain(crz, 12, 115);  
    yaw = map(crz, 12, 115, 0, 127);  
     
    return Status;
}
