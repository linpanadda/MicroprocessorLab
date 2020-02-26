
void setup() {
  // put your setup code here, to run once:
  pinMode(8,OUTPUT);
  Serial.begin(9600);
  Serial.print("Ready...");
  delay(1000);
  Serial.print("Start\n");
}

void loop() {
  // put your main code here, to run repeatedly:  
 for(int i = 0; i < 120;i++){
 digitalWrite(8,i%2);
 Serial.print(i);
 Serial.print("Seconds");
 Serial.println();
 delay(1000);
 }
 Serial.print("\n Stop");
 
}
