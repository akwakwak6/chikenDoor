#include <DS1631.h>
#include <WireRtcLib.h>
#include <EEPROM.h>

#include "Arduino.h"
#include "UseCom.h"
#include "UseData.h"
#include "Init.h"

extern DS1631 tempSens;
extern WireRtcLib rtc;

int _data[10];
int _nbData;

bool isSendLog(){
  return (bool)EEPROM.read(28);
}

/*void sendLog(int s3,int s4){

      int s1,s2;

    getClock(&s1,&s2);
    _data[0]=s3/4;
    _data[1]=s4/4; 

    _data[2]=s1;
    _data[3]=s2; 
   
    sendCmd(17,4,_data); 
}*/


void sendLog(){

    int s1,s2;

    getClock(&s1,&s2);
    _data[0]=s1;
    _data[1]=s2;   
                 
    s1  = analogRead(PHOTOREST_IN);
    s1/=4;
    s2  = analogRead(PHOTOREST_OUT);
    s2/=4;

    _data[2]=s1;
    _data[3]=s2; 
   
    sendCmd(17,4,_data);   
  
}

void setOtherConfigs(){

    for(uint8_t i=0;i<6;i++){
      EEPROM.put(i*2+20, _data[i]);
    } 
  
}

void getOtherConfigs(){

    int v;
    for(uint8_t i=0;i<6;i++){
      EEPROM.get(i*2+20, v);
      _data[i] =  v;
    }
}

void getConfigMove(int nbData,int *data){

  int v = data[1];
  v<<=8;
  _data[0] = v+data[0];
  for(int i=1;i<5;i++)
    _data[i] = data[i+1];
}

void getConfigOpening(){

  int v;
    for(uint8_t i=0;i<5;i++){
      EEPROM.get(i*2, v);
      _data[i] =  v;
    } 
}

void setConfigOpening(){

    for(uint8_t i=0;i<5;i++){
      EEPROM.put(i*2, _data[i]);
    } 
  
}

void getConfigCloseing(){

  int v;
    for(uint8_t i=0;i<5;i++){
      EEPROM.get(i*2+10, v);
      _data[i] =  v;
    } 
}

void setConfigCloseing(){
  
      for(uint8_t i=0;i<5;i++){
      EEPROM.put(i*2+10, _data[i]);
    } 
}

void getConfig(int *vals){

    int v;
    for(uint8_t i=0;i<14;i++){
      EEPROM.get(i*2, v);
      vals[i] =  v;
    }
}

void setDoorPostion(int b){
  EEPROM.write(32, b);
}

int getDoorPostion(){
  return (int)EEPROM.read(32);
}


void flushData(){
  flush_data();
}

void MoveDoorUpdate(int nbData,int *data){

  setData(nbData,data);
  sendCmd(6,nbData,data);
}

void MoveDoorEnd(int error){

  Serial.println("moveDoorEnd");
  Serial.println(error);
  int t[2] = {error};
  sendCmd(7,1,t);
}


void setHour(){

  WireRtcLib::tm* t = rtc.getTime();
  t->hour = _data[0];
  t->min  = _data[1];
  rtc.setTime(t);
  
}

void setDate(){

  WireRtcLib::tm* t = rtc.getTime();
  t->mday = _data[0];
  t->mon  = _data[1];
  t->year  = _data[2];
  rtc.setTime(t);
  
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

void setData(int nbData,int *data){

  _nbData=nbData;
  for(int i=0;i<nbData;i++){
    _data[i]=data[i];
  }
}

void setData(int posit,int data){
  _data[posit]=data;
}

int getData(int posit){
  return _data[posit];
}

void getTemperature(int *v1,int *v2){

  float f = tempSens.readTempOneShot();
  int valTp;
  valTp=(int)f;
  *v1=valTp;
  *v2=(f-valTp)*10;

}

void getClock(int *v1,int *v2){

  WireRtcLib::tm* t = rtc.getTime();
  *v1=t->hour;
  *v2=t->min;

}
void getDate(int *v1,int *v2,int *v3){

  WireRtcLib::tm* t = rtc.getTime();
  *v1=t->mday;
  *v2=t->mon;
  *v3=t->year;
  
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
