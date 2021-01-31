#include <LiquidCrystal_I2C.h>
#include <DS1631.h>

#include "UseCom.h"
#include "Init.h"
#include "Menu.h"

#include "UseData.h"

LiquidCrystal_I2C lcd(0x27, 20, 4);
DS1631 tempSens(0);

bool BpSetEnable=false,flagOneMinute=false,flagTenMinute=false,cnnctd=true,moved=false;
uint8_t PositScreen=0,cptSec=0,cptMin=0;
int moveDoor=3;
volatile unsigned long button_time = 0;
const int debounce = 500; // debounce latency in ms

void setup() {

  initConfig();
  attachInterrupt(digitalPinToInterrupt(bpSet), intBpSet, FALLING);
  loadScreen();
}

void loop() {

  if(moveDoor!=3){
    sendCmd(9,1,&moveDoor);  //go up/down door
    moveDoor=3;
  }

  if(BpSetEnable){   //bp set pushed
    cnnctd=true;
    digitalWrite(BUZZER,LOW);
    menu();
  }
    
  if(flagOneMinute){  //one minute passed
    if (!getBusy()){
      cnnctd=true;
      loadScreen();
      flagOneMinute=false;
    }
    if(cnnctd==false) cptSec=45;
  }
    
  if(flagTenMinute){  //ten minute passed
    
    flagTenMinute=false;
  }

}


void serialEvent1() {
  //Serial.println("get cmd");
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
  delayMicroseconds(32000);
  BpSetEnable=true;
  button_time = millis() + debounce;
  
}
