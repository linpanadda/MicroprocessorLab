int number;
bool toggle =1;
int map7seg[10] =
  {
  0b00111111,
  0b00000110,
  0b01011011,
  0b01001111,
  0b01100110,
  0b01101101,
  0b01111101,
  0b00000111,
  0b01111111,
  0b01101111, 
  };
void setup() {
 // put your setup code here, to run once:
 pinMode(13,OUTPUT); //clock
 pinMode(10,OUTPUT); //latch
 pinMode(11,OUTPUT); //data
 
}
void loop() {

  for(int ii = 0 ; ii<10;ii++){
 for(int i = 0 ; i < 8 ; i++){
 digitalWrite(11,map7seg[ii]>>7-i & 0x01 );
 digitalWrite(13,HIGH);
 digitalWrite(13,LOW);
 }
 digitalWrite(10,HIGH);
 delay(1000);
 digitalWrite(10,LOW);
 }
}
