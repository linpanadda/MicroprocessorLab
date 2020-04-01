#define LED 5
#define MOTOR_D1_PIN 7
#define MOTOR_D2_PIN 8
#define MOTOR_PWM_PIN 6
int LATCH1 = 10,LATCH2 = 9,LATCH3 = 12,LATCH4 = 4;
int DATA = 11;
int CLOCK = 13;
int map7seg[10] = {
  0b00111111,0b00000110,0b01011011,0b01001111,
  0b01100110,0b01101101,0b01111101,0b00000111,
  0b01111111,0b01101111};
int interruptChannel1APin = 2;
int interruptChannel1BPin = 3;
int delay_count = 0;
int setpoint=10;
int toggle = 1;

volatile int encoderCount = 0;
volatile int encoderDir = 0;
void getcode(int code){
  if(code > 0)
  {
    spi_write_1(map7seg[code/1000]);
    spi_write_2(map7seg[(code/100)%10]);
    spi_write_3(map7seg[(code/10)%10]);
    spi_write_4(map7seg[code%10]);
    digitalWrite(LED,LOW);
  }
  if(code < 0)
  {
    code = abs(code);
    spi_write_1(map7seg[code/1000]);
    spi_write_2(map7seg[(code/100)%10]);
    spi_write_3(map7seg[(code/10)%10]);
    spi_write_4(map7seg[code%10]);
    digitalWrite(LED,HIGH);
  }
}
void spi_write_1(signed char cData){
  shiftOut(DATA, CLOCK, MSBFIRST, cData);
  digitalWrite (LATCH1, HIGH);
  digitalWrite (LATCH1, LOW);
}
void spi_write_2(signed char cData){
  shiftOut(DATA, CLOCK, MSBFIRST, cData);
  digitalWrite (LATCH2, HIGH);
  digitalWrite (LATCH2, LOW);
}
void spi_write_3(signed char cData){
  shiftOut(DATA, CLOCK, MSBFIRST, cData);
  digitalWrite (LATCH3, HIGH);
  digitalWrite (LATCH3, LOW);
}
void spi_write_4(signed char cData){
  shiftOut(DATA, CLOCK, MSBFIRST, cData);
  digitalWrite (LATCH4, HIGH);
  digitalWrite (LATCH4, LOW);
}
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
  pinMode(DATA,OUTPUT);
  pinMode(CLOCK,OUTPUT);
  pinMode(LATCH1,OUTPUT);
  pinMode(LATCH2,OUTPUT);
  pinMode(LATCH3,OUTPUT);
  pinMode(LATCH4,OUTPUT);
  pinMode(LED,OUTPUT);
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
  //int setpoint = analogRead(A0);
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
  getcode(encoderCount);
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
