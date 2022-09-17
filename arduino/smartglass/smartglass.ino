#include <M5StickCPlus.h> 
#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

String data;

void setup() {
  M5.begin();
  //LCD設定
  M5.Lcd.setRotation(1);
  M5.Lcd.writecommand(TFT_MADCTL);
  M5.Lcd.writedata(TFT_MAD_MH | TFT_MAD_MV | TFT_MAD_BGR);
  M5.Lcd.setTextSize(5);
  M5.Lcd.setTextColor(WHITE);

  
  // Bluetoth Serial
  SerialBT.begin("smartglass_device", true); 
  M5.Lcd.setTextSize(3);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.print("Connecting...");
  // 接続完了まで繰り返す
  while(!SerialBT.connect("target")); 
  // 接続完了メッセージ
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.print("Connected !");
  delay(1000);
  // 接続完了メッセージ消去
  M5.Lcd.setTextSize(4);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(60, 30);
  M5.Lcd.print("SCORE:");
  M5.Lcd.setCursor(120, 70);
  M5.Lcd.print(0);
}

void loop() {
  if(SerialBT.available()){
    data = SerialBT.readStringUntil('\r');
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(60, 30);
    M5.Lcd.print("SCORE:");
    M5.Lcd.setCursor(120, 70);
    M5.Lcd.print(data);
  }

}
