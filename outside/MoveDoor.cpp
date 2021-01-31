#include "Arduino.h"
#include "MoveDoor.h"
#include "Init.h"
#include "UseData.h"


void moveDoor(bool up){

  int cptPowerTooLong = CPT_FOR_POWER;  //4s
  int cptToMove = CPT_TO_MOVE;  //100s

  int _data[10];
  int cpt=0;

  /////int error=0;        ///////////////////////////export to useData

  int sensors,sensorTp,senorWhenStarted;

  _data[cpt] = (int) up;
  cpt++;
  MoveDoorUpdate(cpt,_data);
  

  digitalWrite(relay,HIGH);
  digitalWrite(way1,LOW);
  digitalWrite(way2,LOW);
    
  while (sensorSignal()==0&&(cptPowerTooLong)){
    cptPowerTooLong--; 
    delay(100);
  }
  if(!cptPowerTooLong){
    digitalWrite(relay,LOW);
    MoveDoorEnd(2);
    setDoorPostion(2);
    return;
  }
  

  sensors = 15;
  sensorTp = senorWhenStarted = sensorSignal();
  sensors &= sensorTp;

  _data[cpt] = senorWhenStarted;
  cpt++;
  MoveDoorUpdate(cpt,_data);

  if(up){
    if(senorWhenStarted == 14){
      digitalWrite(relay,LOW);
      setDoorPostion(1);
      MoveDoorEnd(0);////////////////////////////////////
      return;
    }
  }
  else{
    if(senorWhenStarted == 7){
      digitalWrite(relay,LOW);
      setDoorPostion(0);
      MoveDoorEnd(0);//////////////////////////////////
      return;
    }
  }

  if(up)  digitalWrite(way1,HIGH);
  else    digitalWrite(way2,HIGH);
  
  while (cptToMove){
    cptToMove--; 
    delay(100);
    if(sensorTp != sensorSignal()){
      
      sensorTp = sensorSignal();
      sensors &= sensorTp;
      cpt=3;
      _data[2] = sensors;
      
      MoveDoorUpdate(cpt,_data);
      
      if(up)  {
        if(sensorTp == 14)
          break;
      }
      else{
        if(sensorTp == 7)
          break;
      }
    }
   
  }

  if(cptToMove == 0){
    MoveDoorEnd(4);///////////////////////////did not move fast enought
    setDoorPostion(4);
    digitalWrite(relay,LOW);
    digitalWrite(way1,LOW);
    digitalWrite(way2,LOW);
    return;
  }
  else{
    delay(TIMER_MOVE_AFTER_END);

  }
  digitalWrite(relay,LOW);
  digitalWrite(way1,LOW);
  digitalWrite(way2,LOW);

  cptPowerTooLong=CPT_FOR_POWER;
  while (sensorSignal()!=0&&(cptPowerTooLong)){
    cptPowerTooLong--; 
    delay(100);
  }

  if(!cptPowerTooLong){
    MoveDoorEnd(5);         /////////////////////////////power did not stop
    setDoorPostion(5);
    return;
  }
  if(up)
    setDoorPostion(1);
  else
    setDoorPostion(0);
    MoveDoorEnd(0);
  
}






int sensorSignal(){

  int posSensor=0;

  if(!digitalRead(sensor1)) posSensor++;
  if(!digitalRead(sensor2)) posSensor+=2;
  if(!digitalRead(sensor3)) posSensor+=4;
  if(!digitalRead(sensor4)) posSensor+=8;
  
  return posSensor;
  
}
