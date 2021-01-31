#include <LiquidCrystal_I2C.h>
#include <DS1631.h>
#include <WireRtcLib.h>

#include "UseCom.h"
#include "Init.h"
#include "Menu.h"
#include "MoveDoor.h"
#include "CheckClockAndLight.h"
#include "UseData.h"


LiquidCrystal_I2C lcd(0x27, 20, 4);
DS1631 tempSens(0);
WireRtcLib rtc;

bool BpSetEnable=true,flagOneMinute=false,flagTenMinute=false;
uint8_t PositScreen=0,cptSec=0,cptMin=0;
volatile unsigned long button_time = 0;
const int debounce = 500; // debounce latency in ms

void setup() {
  
  initConfig();
  attachInterrupt(digitalPinToInterrupt(bpSet), intBpSet, FALLING);
  
}

void loop() {
  
  if(BpSetEnable)
    menu();
    
  if(flagOneMinute){  //one minute passed
    flagOneMinute=false;
  }
    
  if(flagTenMinute){  //ten minute passed
    if(isSendLog()) sendLog();
    check();
    flagTenMinute=false;
  }
    
}

void serialEvent1() {

  getCmd();
  
}


ISR(TIMER1_OVF_vect)        
{
  TCNT1 = 3036;            // preload timer

  cptSec++;
  if(cptSec>=60) {               
    cptSec=0;
    cptMin++;
    if(cptMin>=10){     
      cptMin=0;
      flagTenMinute=true;
    }
    flagOneMinute=true;
  } 

}


void intBpSet(){

  if (button_time > millis()) return;
  delayMicroseconds(3200);
  BpSetEnable=true;
  button_time = millis() + debounce;  
  
}
