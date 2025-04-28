/*
  =============================================================
  |🌡️💧TemperatureHumiditySensor by https://github.com/Maxdgf|
  =============================================================
  |Used components:
  |-1) Arduino UNO
  |-2) LCD1602 I2C
  |-3) DHT11
  |-4) RGB LED module
*/

//including others libs
#include <string.h>

//including libs for modules
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

//define modules pins
#define DHT_PIN 7 
#define RED_PIN 8 
#define GREEN_PIN 9 
#define BLUE_PIN 10 

//initialize a custom symbols in byte arrays
const byte tempSymbol[8] = { 0b01100, 0b01000, 0b01100, 0b01000, 0b01100, 0b01000, 0b10100, 0b01000 };
const byte humSymbol[8] = { 0b00000, 0b00000, 0b00100, 0b01110, 0b11111, 0b01110, 0b00100, 0b00000 };
const byte gradusSymbol[8] = { 0b01100, 0b10010, 0b10010, 0b01100, 0b00000, 0b00000, 0b00000, 0b00000 };
const byte dotSymbol[8] = { 0b00000, 0b00000, 0b00100, 0b01110, 0b01110, 0b00100, 0b00000, 0b00000 };

//creating objects of LCD1602 I2C display and DHT11 temp hum sensor
LiquidCrystal_I2C lcd(0x27, 16, 2); //creating LCD1602 I2C (16 chars and 2 lines display) object
DHT dht(DHT_PIN, DHT11); //or DHT22

void setup()
{
  //start DHT11
  dht.begin();

  //LCD1602 I2C initialization and creating special symbols
  lcd.init();                     
  lcd.backlight();

  lcd.createChar(1, tempSymbol);
  lcd.createChar(2, humSymbol);
  lcd.createChar(3, gradusSymbol);
  lcd.createChar(4, dotSymbol);

  //initialization RGB led pins
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

void loop()
{
  //reading DHT11 data (temperature and humidity)
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  //create data strings for printing in LCD1602 I2C display
  String tempData = "Temp: " + String(temp) + char(3) + "C";
  String humData = "Hum: " + String(hum) + "%";

  //printing DHT11 sensor data in LCD1602 I2C display
  lcd.setCursor(0, 0);
  lcd.print(char(1));
  lcd.setCursor(1, 0);
  lcd.print(tempData);
  lcd.setCursor(0, 1);
  lcd.print(char(2));
  lcd.setCursor(1, 1);
  lcd.print(humData);

  //check DHT11 sensor data norms and update strings
  checkNormsOfTemp(temp, tempData, humData);
  checkNormsOfHum(hum, tempData, humData);

  delay(2000);
}

void turnOffRGBLight() {
  //turn off RGB led
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);
}

void checkNormsOfTemp(float temp, String text1, String text2) {
  //checking temperature norms
  //set to temperature data string pointer symbol (dotSymbol) when RGB led turns on
  lcd.setCursor(0, 0);
  lcd.print(char(1));
  lcd.setCursor(1, 0);
  lcd.print(text1 + char(4));

  //turns on RGB led logic by temperature value
  if (temp >= 20 && temp <= 30) {
    //normal temperature
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, HIGH);
    digitalWrite(BLUE_PIN, LOW);

    delay(1000);

    turnOffRGBLight();
  } else if (temp >= 30) {
    //critical temperature
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BLUE_PIN, LOW);

    delay(1000);

    turnOffRGBLight();
  } else if (temp <= 15) {
    //small temperature
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BLUE_PIN, HIGH);

    delay(1000);

    turnOffRGBLight();
  }

  //delete pointer symbol (dotSymbol) and update data strings
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(char(1));
  lcd.setCursor(1, 0);
  lcd.print(text1);
  lcd.setCursor(0, 1);
  lcd.print(char(2));
  lcd.setCursor(1, 1);
  lcd.print(text2);
}

void checkNormsOfHum(float hum, String text1, String text2) {
  //checking humidity norms
  //set to humidity data string pointer symbol (dotSymbol) when RGB led turns on
  lcd.setCursor(0, 1);
  lcd.print(char(2));
  lcd.setCursor(1, 1);
  lcd.print(text2 + char(4));

  if (hum >= 40 && hum <= 60) {
    //normal humidity
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, HIGH);
    digitalWrite(BLUE_PIN, LOW);

    delay(1000);

    turnOffRGBLight();
  } else if (hum >= 70) {
    //critical humidity
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BLUE_PIN, LOW);

    delay(1000);

    turnOffRGBLight();
  } else if (hum <= 30) {
    //small humidity
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BLUE_PIN, HIGH);

    delay(1000);

    turnOffRGBLight();
  }

  //delete pointer symbol (dotSymbol) and update data strings
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(char(1));
  lcd.setCursor(1, 0);
  lcd.print(text1);
  lcd.setCursor(0, 1);
  lcd.print(char(2));
  lcd.setCursor(1, 1);
  lcd.print(text2);
}
