#define MOTOR_D1_PIN 7
#define MOTOR_D2_PIN 8
#define MOTOR_PWM_PIN 6
#define En_PIN 3
bool previous_read;
int count = 0;
int speed_input = 1;
void motor_dir(int dir){
  if(dir > 0){
    motor_speed_ccw(dir);
  }
  else{
    int x = abs(dir);
    motor_speed_cw(x);
  }
}
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
  pinMode(3,INPUT_PULLUP);
  pinMode(MOTOR_D1_PIN,OUTPUT);
  pinMode(MOTOR_D2_PIN,OUTPUT);
  pinMode(MOTOR_PWM_PIN,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(2),
                   ISR_Callback, RISING);
  Serial.begin(9600);
  Serial.print("Test Encoder\n");
}
void loop() {
  motor_dir(speed_input);
  delay(1000);
}
void ISR_Callback()
{
  count++;
  if(digitalRead(En_PIN)==0)
  {
    Serial.print("-");
  }
  else
  {
    Serial.print("+");
  }
  Serial.println(count);
}
