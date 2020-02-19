#include <SPI.h>

#define DATA_PIN 11
#define CLOCK_PIN 13
#define SS_PIN_1 10
#define SS_PIN_2 9
#define add A0
#define minus A1
#define countdown A2
int count = 0;
int a[10] = {
  0x3F,
  0x06,
  0x5B,
  0x4F,
  0x66,
  0x6D,
  0x7D,
  0x07,
  0x7F,
  0x6F
};

void spi_write_1(unsigned char cData) {
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, cData);
  
  digitalWrite (SS_PIN_1, HIGH);
  digitalWrite (SS_PIN_1, LOW);
}

void spi_write_2(unsigned char cData) {
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, cData);
  digitalWrite (SS_PIN_2, HIGH);
  digitalWrite (SS_PIN_2, LOW);
}

void setup()
{
  pinMode(SS_PIN_1, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(SS_PIN_2, OUTPUT);
  pinMode(add,INPUT);
  pinMode(minus,INPUT);
  pinMode(countdown,INPUT);
  pinMode(7,OUTPUT);
  //Serial.begin(9600);
}

void dis_num(int x)
{
  int x1,x2;
  x1 = x%10; 
  x2 = x/10;
  spi_write_2(a[x1]);
  spi_write_1(a[x2]);
}
void loop()
{
//  Serial.print("add : ");
//  Serial.print(digitalRead(add));
//  Serial.print("minus : ");
//  Serial.print(digitalRead(minus));
//  Serial.print("countdown : ");
//  Serial.print(digitalRead(countdown));
//  Serial.println();
//  for(int i=0 ; i<100 ; i++){
//    dis_num(i);
//    delay(500);
//  }
//    
  dis_num(count);
  if(digitalRead(add)==0){
    while(digitalRead(add)==0);
    count++;
  }
    if(digitalRead(minus)==0){
    while(digitalRead(minus)==0);
    if(count ==-1){
      count=99;
    }
    count--;
  }
    if(digitalRead(countdown)==0){
    while(digitalRead(countdown)==0);
    for(int i = count;i > 0;i--){
      dis_num(i);
      delay(200);
    }
    count =0;
    tone(7,1000,2000);
  }
  delay(100);
}
