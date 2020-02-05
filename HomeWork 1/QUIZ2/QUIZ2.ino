int count =0;
void setup(){
  DDRB=0b00000001;
  DDRD=0b11111111;
}
void loop(){
  PORTD=0b00000001<<count;
  if(PINB==0b00000001){
    delay(250);
    count++;}
  if(count==8){
    count = 0;
  }
}
