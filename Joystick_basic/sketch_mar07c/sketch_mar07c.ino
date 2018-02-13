int joystick_X = 0;
int joystick_Y = 0;
int x1 = 0;
int y1 = 0;

// the setup routine runs once when you press reset:
void setup() 
{
 Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() 
{
  // read the input on analog pin 0:
  joystick_X = analogRead(A0);
  joystick_Y = analogRead(A1);
  x1 = map(joystick_X,0,1023,-127,127);
  y1 = map(joystick_Y,0,1023,-127,127);
  Serial.print(x1);
  Serial.print(" ");
  Serial.print(y1);
  Serial.println(" ");
}
