#define SW 8
#define LED 9
boolean prev = true;
void setup() {
  // put your setup code here, to run once:
  pinMode(SW, INPUT_PULLUP);
  ledcSetup(0, 38000, 8);
  ledcAttachPin(LED, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
  boolean current = digitalRead(SW);
  if(prev && !current){
    ledcWrite(0, 85);
    delay(50);
    ledcWrite(0, 0);
  }
  prev = current;
}
