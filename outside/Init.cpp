#include <LiquidCrystal_I2C.h>
#include <DS1631.h>
#include <WireRtcLib.h>

#include "Arduino.h"
#include "Init.h"

extern LiquidCrystal_I2C lcd;
extern DS1631 tempSens;
extern WireRtcLib rtc;

void initConfig(){


  lcd.init(); // initialisation de l'afficheur
  lcd.backlight();
  lcd.print("Loading . . .");
  lcd.setCursor(0, 1);

  tempSens.writeConfig(13);  // Set to 12-bit, 1-shot mode

  rtc.begin();

  pinMode(relay, OUTPUT);
  pinMode(way1, OUTPUT);
  pinMode(way2, OUTPUT);
  pinMode(setHC12, OUTPUT);
  pinMode(bpSet, INPUT_PULLUP);
  pinMode(bp_up, INPUT_PULLUP);
  pinMode(bp_down, INPUT_PULLUP);
  pinMode(sensor1, INPUT_PULLUP);
  pinMode(sensor2, INPUT_PULLUP);
  pinMode(sensor3, INPUT_PULLUP);
  pinMode(sensor4, INPUT_PULLUP);

  pinMode(PHOTOREST_IN, INPUT);
  pinMode(PHOTOREST_OUT, INPUT);

  digitalWrite(setHC12,HIGH);
  


  Serial.begin(9600);             // Serial port to computer
  Serial1.begin(1200);


      // initialize timer1 
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;

  TCNT1 = 3036;            // preload timer 65536-3036 / (16MHz/256) = 1Hz
  TCCR1B |= (1 << CS12);    // 256 prescaler  , add :   | (1 << CS10); for 256 to 1024 => 16M/1024= 15625
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
  
  interrupts();             // enable all interrupts
  
}
