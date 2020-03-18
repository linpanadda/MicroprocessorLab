int CLOCK=13;//SHCP
int LATCH=10;//STCP
int DATA=11;//DS
int count =0;
int timer1_counter;

long map7seg[10] = {111111101, 101100000, 111011010, 111110010, 101100111, 110110111
                , 110111111, 111100001, 111111111 , 111110111
               };
long temp;

void setLed()
{
  digitalWrite(LATCH,LOW);
  temp=map7seg[count];
  for(int i=0;i<8;i++)
  {
    digitalWrite(DATA,temp%10);
    digitalWrite(CLOCK,HIGH);
    digitalWrite(CLOCK,LOW);
    temp=temp/10;
  }
  digitalWrite(LATCH,HIGH);
}
void setup()
{
  //put your setup code here,to run once:
  pinMode(CLOCK,OUTPUT);
  pinMode(LATCH,OUTPUT);
  pinMode(DATA,OUTPUT);
  setLed();
  noInterrupts();
  TCCR1A=0;
  TCCR1B=0;
  
  timer1_counter = 0;
  TCNT1 = timer1_counter;
  TCCR1B |= (1<<CS12);
  TIMSK1 |= (1<<TOIE1);
  
  interrupts();
}

ISR(TIMER1_OVF_vect)
{
  TCNT1=timer1_counter;
  count++;
  if(count>9)
  {
    count=0;
  }
}

void loop()
{
  setLed();
}
