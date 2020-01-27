int count=0;
bool reverse=false;
byte segments=0b00000001;

void setup()
{
  DDRD=0b11111111;
}

void loop()
{
  PORTD=segments;
  delay(500);
  PORTD=0x00;
  delay(500);
  if(count>=7)
  {
    reverse=true;
  }
  if(count<=0)
  {
    reverse=false;
  }
  if(reverse==false)
  {
    segments=segments<<1;
    count++;
  }
  else
  {
    segments=segments>>1;
    count--;
  }
}
