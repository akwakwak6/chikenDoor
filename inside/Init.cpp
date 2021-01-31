#include <LiquidCrystal_I2C.h>
#include <DS1631.h>

#include "Arduino.h"
#include "Init.h"

extern LiquidCrystal_I2C lcd;
extern DS1631 tempSens;

void initConfig(){


  lcd.init(); // initialisation de l'afficheur
  lcd.backlight();
  lcd.print("Loading . . .");
  lcd.setCursor(0, 1);

  tempSens.writeConfig(13);  // Set to 12-bit, 1-shot mode

  pinMode(bpSet, INPUT_PULLUP);
  pinMode(bp_down, INPUT_PULLUP);
  pinMode(bp_up, INPUT_PULLUP);
  
  pinMode(LED_GREEN, OUTPUT);
  digitalWrite(LED_GREEN,HIGH);
  
  pinMode(SEN_1_G, OUTPUT);
  pinMode(SEN_2_G, OUTPUT);
  pinMode(SEN_3_G, OUTPUT);
  pinMode(SEN_4_G, OUTPUT);
  pinMode(SEN_1_R, OUTPUT);
  pinMode(SEN_2_R, OUTPUT);
  pinMode(SEN_3_R, OUTPUT);
  pinMode(SEN_4_R, OUTPUT);

  digitalWrite(SEN_1_G,HIGH);
  digitalWrite(SEN_2_G,HIGH);
  digitalWrite(SEN_3_G,HIGH);
  digitalWrite(SEN_4_G,HIGH);
  digitalWrite(SEN_1_R,HIGH);
  digitalWrite(SEN_2_R,HIGH);
  digitalWrite(SEN_3_R,HIGH);
  digitalWrite(SEN_4_R,HIGH);

  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER,LOW);

  pinMode(SET_HC12, OUTPUT);
  digitalWrite(SET_HC12,HIGH);

  Serial.begin(9600);             // Serial port to computer
  Serial1.begin(1200);

  delay(500);

    // initialize timer1 
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;

  TCNT1 = 3036;            // preload timer 65536-3036 / (16MHz/256) = 1Hz
  TCCR1B |= (1 << CS12);    // 256 prescaler  , add :   | (1 << CS10); for 256 to 1024 => 16M/1024= 15625
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
  
  interrupts();             // enable all interrupts

  
  
}
