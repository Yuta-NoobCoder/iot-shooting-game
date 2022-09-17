#include <M5Stack.h>
#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

#define IR_RECEIVE_PIN GPIO_NUM_22
#define SERVO_PIN GPIO_NUM_16

int count = 0;
int score = 0;
boolean prev = true;

void setup() {
  M5.begin();
  M5.Power.begin();
  // 赤外線受光
  pinMode(IR_RECEIVE_PIN, INPUT);
  // サーボ設定
  pinMode(SERVO_PIN, OUTPUT);
  ledcSetup(1, 50, 16);
  ledcAttachPin(SERVO_PIN, 1);
  // LCD設定
  M5.Lcd.setTextSize(5);
  M5.Lcd.setTextColor(BLACK);
  // Blutooth
  SerialBT.begin("target");
}

void loop() {
  // 受光時にLOW(False)
  
  boolean current = digitalRead(IR_RECEIVE_PIN);
  if(!prev && !current) {
    count ++;
  }else{
    // ノイズ除去のためLOWが5回連続するとヒット判定
    if(count >= 5) {
      score ++;
      // HIT表示
      M5.Lcd.fillScreen(WHITE);
      M5.Lcd.setCursor(50, 100);
      M5.Lcd.print("HIT !!!");
      // ヒット判定をスマートグラスへ送信
      SerialBT.printf("%d\r", score);
      // 的を倒す
      knockdownServo();
      delay(200);
      // 戻す
      standUpServo();
      M5.Lcd.clear(BLACK);
    }
    count = 0;
  }
  prev = current;
  delay(5);
}

void knockdownServo() {
  for (int i = 2500; i <= 6000; i=i+500) {
    ledcWrite(1, i);
    delay(30);
    Serial.printf("%d\n", i);
  }
}

void standUpServo() {
  for (int i = 6000; i >= 2500; i=i-500) {
    ledcWrite(1, i);
    delay(30);
    Serial.printf("%d\n", i);
  }
}

