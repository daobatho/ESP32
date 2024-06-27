#DAO_BA_THO
```
#define LED_PIN 13
bool ledstate=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_PIN, ledstate);
  ledstate=!ledstate;
  delay(500);
}
```