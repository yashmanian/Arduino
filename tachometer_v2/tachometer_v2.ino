int val;
long last=0;
int stat=LOW;
int stat2;
int contar=0;

int sens=75;  // this value indicates the limit reading between dark and light,
              // it has to be tested as it may change acording on the 
              // distance the leds are placed.
int nPalas=6; // the number of blades of the propeller

int time=500; // the time it takes each reading
void setup()
{
  Serial.begin(9600);
  pinMode(13,OUTPUT);
}

void loop()
{
  val=analogRead(0);
  if(val<sens)
    stat=LOW;
   else
    stat=HIGH;
   digitalWrite(13,stat); //as iR light is invisible for us, the led on pin 13 
                          //indicate the state of the circuit.

   if(stat2!=stat){  //counts when the state change, thats from (dark to light) or 
                     //from (light to dark), remmember that IR light is invisible for us.
     contar++;
     stat2=stat;
   }
   if(millis()-last>=time){
     double rps=((double)contar/nPalas)/2.0*1000.0/time;
     double rpm=((double)contar/nPalas)/2.0*60000.0/(time);
     Serial.print((contar/2.0));Serial.print("  RPS ");Serial.print(rps);
     Serial.print(" RPM");Serial.print(rpm);Serial.print("  VAL ");Serial.println(val);
     contar=0;
     last=millis();
   }
}
