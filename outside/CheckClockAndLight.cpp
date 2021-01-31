#include "Arduino.h"
#include "Init.h"
#include "CheckClockAndLight.h"
#include "UseData.h"
#include "MoveDoor.h"

uint8_t cpt;
int error=0;        ///////////////////////////export to useData

void check(){

    int cptPowerTooLong = CPT_FOR_POWER;  //4s

    int h,m,sensor;
    int conf[14]; 

    getClock(&h,&m);
    getConfig(conf);

    if(conf[11]==1){
      if( cmpHour(h,m,conf[1],conf[2]) && cmpHour(conf[6],conf[7],h,m)){
        if(getDoorPostion() == 0){
          moveDoor(true);
          //Serial.println("monte la porte");
        }
      }
      else{
        if(getDoorPostion() == 1){
          moveDoor(false);
          //Serial.println("descend la porte");
        }
      }
      //Serial.println("fini");
      return;
    }

    if( cmpHour(conf[1],conf[2],h,m) || cmpHour(h,m,conf[8],conf[9]) ){
      if(getDoorPostion() == 1){
          moveDoor(false);
          //Serial.println("descend la porte 2");
        }
      //Serial.println("fini 2");
      return;
    }

    if( cmpHour(h,m,conf[3],conf[4]) && cmpHour(conf[6],conf[7],h,m) ){
      if(getDoorPostion() == 0){
          moveDoor(true);
          //Serial.println("monte la porte 2");
        }
      //Serial.println("fini 3");
      return;
    }

  if( cmpHour(h,m,conf[1],conf[2]) && cmpHour(conf[3],conf[4],h,m) ){

    if(getDoorPostion() == 1){
      //Serial.println("deja ouvert");
      return;
    }  
  }else{
    if(getDoorPostion() == 0){
      //Serial.println("deja ferme");
      return;
    }
  }


  /*digitalWrite(relay,HIGH);
    
  while (sensorSignal()==0&&(cptPowerTooLong)){
    cptPowerTooLong--; 
    delay(100);
  }
  if(!cptPowerTooLong){
    digitalWrite(relay,LOW);
    error=15;
    return;
  }    
  delay(3000);*/


  if(conf[12]==1)                
    sensor  = analogRead(PHOTOREST_IN)/4;
  else
    sensor  = analogRead(PHOTOREST_OUT)/4;

  //Serial.print("sensor ");
  //Serial.println(sensor);

  ///////////////////////////////////////////digitalWrite(relay,LOW);

  if( cmpHour(h,m,conf[1],conf[2]) && cmpHour(conf[3],conf[4],h,m) ){

    if(sensor>conf[0]){
      cpt++;    
    }else{
      cpt=0;
    }
    if(cpt>=conf[13]){
      moveDoor(true);
      //Serial.println("ok monte la porte");
      cpt=0;
    }
    
  }else{

    if(sensor<conf[5]){
      cpt++;    
    }else{
      cpt=0;
    }
    if(cpt>=conf[13]){
      moveDoor(false);
      //Serial.println("ok descend la porte");
      cpt=0;
    }
    
  }

}



bool cmpHour(int h1,int m1,int h2,int m2){


    if(h1<=h2){
      if(h1==h2){
        if(m1>m2){
          return true;
        }else{
          return false;
        }
      }else{
        return false;
      }
    }else{
      return true;
    }
  
}
