#define LED_PIN1 10
#define LED_PIN2 11
float brightness = 0;
String buff;
int state;
char pin;
void setup() {
 // put your setup code here, to run once:
 pinMode(LED_PIN1,OUTPUT);
 pinMode(LED_PIN2,OUTPUT);
 Serial.begin(9600);
}
void loop() {
 // put your main code here, to run repeatedly:

 if (Serial.available() > 0) {
 char inByte = Serial.read();
 if(inByte == 'L'){
 buff = ' ';
 state =0;
 }
 if(('0'<= inByte) && (inByte <= '9') && state == 0){
    if(inByte == '1'){
      pin = LED_PIN1;
      Serial.print("LED 1 :");
    }
     if(inByte == '2'){
      pin = LED_PIN2;
      Serial.print("LED 2 :");
    }
 }
     if(inByte == 'B'){
       buff = ' ';
       state = 1;
    }
     if(('0'<= inByte) && (inByte <= '9') && state == 1){
      buff += inByte;
     }
 if(inByte == '\n'){    

 brightness = buff.toInt();
 Serial.println(brightness);
 analogWrite(pin,int(brightness*2.54));
 }
 }
}
