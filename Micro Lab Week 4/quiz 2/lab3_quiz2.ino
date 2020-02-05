int button;
int clk_pin = 13; //SHCP
int latch_pin = 10; //STCP
int data_pin = 11; //DS
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
  int counter;
void setLed(uint8_t _state){
  digitalWrite(latch_pin,LOW);
  for(int i = 0 ; i < 8 ; i++){
    digitalWrite(data_pin,(_state >> (7-i)) & 0x01);
    digitalWrite(clk_pin,HIGH); 
    digitalWrite(clk_pin,LOW);
  }
  digitalWrite(latch_pin,HIGH);
}
void setup(){
 pinMode(clk_pin,OUTPUT);
 pinMode(latch_pin,OUTPUT);
 pinMode(data_pin,OUTPUT);
  Serial.begin(9600);
  while(!Serial){
    ;
  }

  Serial.println("\n\nString toInt():");
  Serial.println();
}
void loop(){
  String inString;
  while (Serial.available() > 0){
    int inChar = Serial.read();

    inString = (char)inChar;

    Serial.print("Value :");
    Serial.println(inString.toInt());
    setLed(map7seg[inString.toInt()]);
  }

}
