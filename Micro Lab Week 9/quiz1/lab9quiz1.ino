#define LED0 9
#define INT 3
int timer1_counter;
int toggle=1;
int mode = 1000;
void setup()
{
  pinMode(LED0,OUTPUT);
  pinMode(INT,INPUT);
  attachInterrupt(digitalPinToInterrupt(INT),
                  ISR_Callback, RISING);
}

void loop()
{
  digitalWrite(LED0,toggle);
  delay(mode);
  digitalWrite(LED0,!toggle);
  delay(mode);
}

void ISR_Callback()
{
  mode += 1000;
  if(mode > 3000)
  {
    mode = 1000;
  }
}
