#define MOTOR_D1_PIN 7
#define MOTOR_D2_PIN 8
#define MOTOR_PWM_PIN 6
int interruptChannel1APin = 2;
int interruptChannel1BPin = 3;
int delay_count = 0;
int setpoint=0;
int toggle = 1;

volatile int encoderCount = 0;
volatile int encoderDir = 0;
void moveForward (int speed) 
{
  digitalWrite(MOTOR_D1_PIN,HIGH);
  digitalWrite(MOTOR_D2_PIN,LOW);
  analogWrite(MOTOR_PWM_PIN,speed);
}

void moveBackward (int speed) 
{
  digitalWrite(MOTOR_D1_PIN,LOW);
  digitalWrite(MOTOR_D2_PIN,HIGH);
  analogWrite(MOTOR_PWM_PIN,speed);
}
void setSpeed (int speed)
{
  if (speed>0)
  {
    if(speed>255)
    {speed=255;}
    moveForward(speed);
  }
 else if (speed<0)
 {
   speed=speed*(-1);
   if (speed>255)
   {speed=255;}
   moveBackward(speed);
 }
 else
 {moveForward(1);}
}
void setup()
{
  pinMode(MOTOR_D1_PIN,OUTPUT);
  pinMode(MOTOR_D2_PIN,OUTPUT);
  pinMode(MOTOR_PWM_PIN,OUTPUT);
  
  pinMode(interruptChannel1APin,INPUT_PULLUP);
  pinMode(interruptChannel1BPin,INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(interruptChannel1APin),
                 Channel1A_callback, RISING);
  attachInterrupt(digitalPinToInterrupt(interruptChannel1BPin),
                 Channel1B_callback, RISING);
  Serial.begin(9600);
}
void loop()
{
  int setpoint = analogRead(A0);
  int error = setpoint - encoderCount;
  int p = 2.0*(float)(error);
  setSpeed(p);
  Serial.print(setpoint);
  Serial.print(",");
  Serial.println(encoderCount);
  delay(100);
  
  Serial.print("Dir: ");
  Serial.print(encoderDir);
  Serial.print(",Pos: ");
  Serial.print(encoderCount);
  Serial.print(",P: ");
  Serial.println(p);
  delay(10);
}

void Channel1A_callback()
{
  if (digitalRead(interruptChannel1APin)==1 && 
  digitalRead(interruptChannel1BPin)==0)
   {
     encoderCount++;
    encoderDir = 1;
   }
}

void Channel1B_callback()
{
  if (digitalRead(interruptChannel1APin)==0 && 
  digitalRead(interruptChannel1BPin)==1)
   {
     encoderCount--;
    encoderDir = 0;
   }
}

void serialEvent() 
{
  setpoint = Serial.parseInt();
}
