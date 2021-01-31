#include <Communication.h>

#include "Arduino.h"
#include "UseCom.h"
#include "UseData.h"

Com com(getDataOfCmd,useDataOfCmd);
bool busy=false;
extern bool flagTenMinute;

void setBusy(bool b){
  busy=b;
}

bool getBusy(){
  return busy;
}

void flush_data(){
  com.flush();
}

bool sendCmd(int cmd){
  return com.sendMsg(cmd);
}

bool sendCmd(int cmd,int nbData,int *data){

  /*Serial.println("send cmd set");
  for(int i=0;i<nbData;i++)
    Serial.println(data[i]);*/
  
  return com.sendMsg(cmd,nbData,data);
  
}

void getCmd(){
  com.getMsg();
}


void getDataOfCmd(int cmd,int *nbData,int *_data){


}

void useDataOfCmd(int cmd,int nbData,int *data){

  switch (cmd) {

    case 134 :  //Door update 128+6
        busy=true;
        setData(nbData,data);
        moveDoorUpdate();
        break;

    case 135 : //Door move End 128+7
        moveDoorEnd(data[0]);        
        flagTenMinute=true;
        busy=false;
        break;
    case 145 : //sensor Log 128+17
        for(int i=0;i<nbData;i++){
          Serial.print(data[i]);
          Serial.print(":");
        }
        Serial.println();  
        break;
        
    case 1 : 
    case 2 : 
    case 3 : 
    case 8 :
    case 15:
        setData(nbData,data);
        break;
    case 11:
    case 12:
        getConfigMove(nbData,data);
        break;
        
  }
  /*Serial.println("useDataOfCmd ok?");
  Serial.println(cmd);
  Serial.println(nbData);
  for(int i=0;i<nbData;i++)
    Serial.println(data[i]);*/
  
  
}
