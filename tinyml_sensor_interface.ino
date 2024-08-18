#include "TFT_eSPI.h"
#include "DHT.h"

#define DHTPIN 1
#define DHTTYPE 22

DHT dht(DHTPIN,DHTTYPE);

TFT_eSPI tft;
TFT_eSprite spr =TFT_eSprite(&tft);
int sensorPin=A1;
float sensorValue=0;

void setup() {
  pinMode(WIO_LIGHT,INPUT);
  pinMode(WIO_BUZZER,OUTPUT);
  Serial.begin(9600);

  dht.begin();
  tft.begin();
  tft.setRotation(3);
  spr.createSprite(TFT_HEIGHT,TFT_WIDTH);
 
}

void loop() {
 float t=dht.readTemperature();
 float h=dht.readHumidity();
 int light =analogRead(WIO_LIGHT);

 Serial.print("Temp: ");
 Serial.println(t);
 Serial.print("Humidity: ");
 Serial.print(h);

 spr.fillSprite(TFT_WHITE);
 spr.fillRect(0,0,320,50,TFT_DARKGREEN);
 spr.setTextColor(TFT_WHITE);
 spr.setTextSize(3);
 spr.drawString("Smart Garden",50,15);

 spr.drawFastVLine(150,50,190,TFT_BLACK);
 spr.drawFastHLine(0,140,320,TFT_BLACK);


 spr.setTextColor(TFT_BLACK);
 spr.setTextSize(2);
 spr.drawString("Temperature",10,65);
 spr.setTextSize(3);
 spr.drawNumber(t,50,95);
 spr.drawString("C",90,95);

 spr.setTextSize(2);
 spr.drawString("Humidity",25,160);
 spr.setTextSize(3);
 spr.drawNumber(h,30,190);
 spr.drawString("%RH",70,190);

 sensorValue=analogRead(sensorPin);
 sensorValue=map(sensorValue,1023,400,0,100);
 spr.setTextSize(2);
 spr.drawString("Soil. Moisture",160,65);
 spr.setTextSize(3);
 spr.drawNumber(sensorValue,200,95);
 spr.drawString("%", 240,95);

 spr.setTextSize(2);
 spr.drawString("Light",200,160);
 spr.setTextSize(3);
 light=map(light,0,1023,0,100);
 spr.drawNumber(light,205,190);
 spr.drawString("%",245,190);

 //CONDITION FOR LOW MOISTURE
if (sensorValue<50){
  spr.fillSprite(TFT_RED);
  spr.drawString("Time to Water!!",35,100);
  analogWrite(WIO_BUZZER,150);
  delay(3000);
  analogWrite(WIO_BUZZER,0);
  delay(1000);

}

  spr.pushSprite(0,0);
  delay(50);
  }