#include <DS1631.h>
#include <EEPROM.h>

#include "Arduino.h"
#include "UseCom.h"
#include "UseData.h"
#include "Init.h"
#include "BuzzeSong.h"

extern DS1631 tempSens;
extern bool moved;

int _data[10];
int _nbData;


bool setOtherConfigs(){
  return sendCmd(16,5,_data);
}

bool getOtherConfigs(){

  if(sendCmd(15))
    return true;
  return false;
  
}


bool isRingMorNig(){
  if(EEPROM.read(0)!=0)
    return true;
  else
    return false;
}

bool isRingError(){
  if(EEPROM.read(0)==3)
    return true;
  else
    return false;
}

void setConfigCloseing(){
  getConfigMoveBack();
  sendCmd(14,6,_data);
}

void setConfigOpening(){
  getConfigMoveBack();
  sendCmd(13,6,_data);
}

void getConfigMoveBack(){
  int v = _data[0];
  for(int i=5;i>=1;i--){
    _data[i+1]=_data[i];
  }
  _data[0] = (uint8_t)v;
  _data[1] = v>>=8;

}

void getConfigMove(int nbData,int *data){

  int v = data[1];
  v<<=8;
  _data[0] = v+data[0];
  for(int i=1;i<5;i++)
    _data[i] = data[i+1];
}

bool getDoorPosition(){ 
    if(sendCmd(8))
      return true;
    return false;
}

bool getConfigCloseing(){
  if(sendCmd(12))
    return true;
  return false;
}

bool getConfigOpening(){
  if(sendCmd(11))
    return true;
  return false;
}

void moveDoorUpdate(){

   if(_nbData == 1 ){
    digitalWrite(LED_GREEN,LOW);
    manageLeds(0);
    moved=true;
    return;
   }

  int val;
  switch(_data[_nbData-1]){

      case 15:  val=0;
                break;
      case 7 :  if(digitalRead(SEN_4_R)!=0) val = 17;
                else  val = 1;
                break;
      case 3 :  if(digitalRead(SEN_3_R)!=0) val = 35;
                else  val = 3;
                break;
      case 1 :  if(digitalRead(SEN_2_R)!=0) val = 71;
                else  val = 7;
                break;
                
      case 14:  if(digitalRead(SEN_1_R)!=0) val = 136;
                else  val = 8;
                break;
      case 12:  if(digitalRead(SEN_2_R)!=0) val = 76;
                else  val = 12;
                break;
      case 8:  if(digitalRead(SEN_3_R)!=0) val = 46;
                else  val = 14;
                break;
                
      case 0:   val = 15;
                break;
                
      default :
              val=255;
              break;
  }
  manageLeds(val);
  
}

void manageLeds(int val){

  if((val&128) > 0)   digitalWrite(SEN_1_R,LOW);
  else               digitalWrite(SEN_1_R,HIGH);

  if((val&64) > 0)   digitalWrite(SEN_2_R,LOW);
  else              digitalWrite(SEN_2_R,HIGH);  

  if((32&val) > 0)   digitalWrite(SEN_3_R,LOW);
  else              digitalWrite(SEN_3_R,HIGH);

  if((val&16) > 0)   digitalWrite(SEN_4_R,LOW);
  else              digitalWrite(SEN_4_R,HIGH);

  if((val&8) > 0)   digitalWrite(SEN_1_G,LOW);
  else             digitalWrite(SEN_1_G,HIGH);

  if((val&4) > 0)   digitalWrite(SEN_2_G,LOW);
  else             digitalWrite(SEN_2_G,HIGH);  

  if((val&2) > 0)   digitalWrite(SEN_3_G,LOW);
  else             digitalWrite(SEN_3_G,HIGH);

  if((val&1) > 0)   digitalWrite(SEN_4_G,LOW);
  else             digitalWrite(SEN_4_G,HIGH);
  
}

void moveDoorEnd(int msg){

    if(msg == 0){
      manageLeds(0);
      digitalWrite(LED_GREEN,HIGH);
      singStarWars();
    }else{
      Serial.println("BUZZER,HIGH");
      digitalWrite(BUZZER,HIGH);
    }
  
}


void flushData(){
  flush_data();
}

bool setHour(){

  return sendCmd(4,2,_data);
  
}

bool setDate(){
  return sendCmd(10,3,_data);
}

int getNewVal(int val,int step_,int mi,int ma,bool up){

  int tp;

  if(up){
    tp=val+step_;
    if(tp>ma)  tp = mi;
  }else{
    tp=val-step_;
    if(tp<mi)  tp=ma;
    if(tp>ma) tp=ma;
  }

  return tp;  
}



void setData(int posit,int data){
  _data[posit]=data;
}

int getData(int posit){
  return _data[posit];
}

void setData(int nbData,int *data){

  _nbData=nbData;
  for(int i=0;i<nbData;i++){
    _data[i]=data[i];
  }
  
}

void getTemperature(int *v1,int *v2){

  float f = tempSens.readTempOneShot();
  int valTp;
  valTp=(int)f;
  *v1=valTp;
  *v2=(f-valTp)*10;

}


bool getTemperatureOut(int *v1,int *v2){

  if(sendCmd(1))
    return true;
  *v1=_data[0];
  *v2=_data[1];

    return false;
  
}


bool getClock(int *v1,int *v2){

  if(sendCmd(2))
    return true;
  *v1=_data[0];
  *v2=_data[1];

  return false;

}
bool getDate(int *v1,int *v2,int *v3){

  if(sendCmd(3))
    return true;
  *v1=_data[0];
  *v2=_data[1];
  *v3=_data[2];

  return false;
  
}

String getHour(int h,int m){

  String str;
  if(h<10) str="0";
  str+=h;
  str+=":";
  if(m<10) str+="0";
  str+=m;

  return str;
}
