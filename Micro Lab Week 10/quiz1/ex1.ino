#define MOTOR_D1_PIN 7
#define MOTOR_D2_PIN 8
#define MOTOR_PWM_PIN 6
bool previous_read;
int count = 0;
void motor_speed_ccw(int speed){
 digitalWrite(MOTOR_D1_PIN,HIGH);
 digitalWrite(MOTOR_D2_PIN,LOW);
 analogWrite(MOTOR_PWM_PIN,speed);
}
void motor_speed_cw(int speed){
 digitalWrite(MOTOR_D1_PIN,LOW);
 digitalWrite(MOTOR_D2_PIN,HIGH);
 analogWrite(MOTOR_PWM_PIN,speed);
}
void setup() {
 pinMode(2,INPUT_PULLUP);
 pinMode(MOTOR_D1_PIN,OUTPUT);
 pinMode(MOTOR_D2_PIN,OUTPUT);
 pinMode(MOTOR_PWM_PIN,OUTPUT);
 Serial.begin(9600);
 Serial.print("Test Encoder");
}
void loop() {
  motor_speed_ccw(255);
}
