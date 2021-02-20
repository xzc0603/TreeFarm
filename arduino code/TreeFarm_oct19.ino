// LCD를 쉽게 제어하기 위한 라이브러리를 추가합니다.
#include <LiquidCrystal_I2C.h>
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include "DHT.h"
#include "module.h"

// 0x3F I2C 주소를 가지고 있는 16x2 LCD객체를 생성합니다.(I2C 주소는 LCD에 맞게 수정해야 합니다.)
LiquidCrystal_I2C lcd(0x27, 20, 4);
DHT dht(2, DHT22);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, 8, NEO_GRB + NEO_KHZ800);

unsigned char rcv[8] = {0,};
unsigned int arr[10] = {0,}; //순서대로 온도, 습도, EC, 미세먼지, CO₂,조도 센서
void serialEvent1()
{
  Serial1.readBytes(rcv, 8);
}

/*0.8705,0,0.2078*/

// 실행시 가장 먼저 호출되는 함수이며, 최초 1회만 실행됩니다.
// 변수를 선언하거나 초기화를 위한 코드를 포함합니다.
void setup() {
#include "init.h"
  for (int i = 0; i < 8; i++)strip.setPixelColor(i, 111, 0, 27);
  strip.show();
}

void serialEvent2()
{
  char c;
  c=Serial2.read();
  switch(c)
  {
    case '1':halt=1;break;
    case '2':halt=0;break;
  }
}

/*임시 코드*/
void serialEvent()
{
  char c;
  c=Serial.read();
  switch(c)
  {
    case '1':cF[0]|=1;break;
    case '2':cF[1]|=1;break;
    case '3':cF[2]=1;break;
    case '4':cF[2]=0;break; 
  }
}

void loop() {
  if(!halt)
  {
    #include "main.h"
  }
  else 
  {
    #include "sub.h"
  }
}
