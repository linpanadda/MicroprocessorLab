int count = 0;
void setup()
{
 pinMode(2, INPUT_PULLUP);
 attachInterrupt(digitalPinToInterrupt(2),
                  ISR_Callback, RISING);
 Serial.begin(9600);
 Serial.println("Test Encoder");
}
void loop()
{
}

void ISR_Callback(){  
  Serial.println(count++);
}
