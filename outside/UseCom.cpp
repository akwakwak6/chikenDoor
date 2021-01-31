#include <Communication.h>

#include "Arduino.h"
#include "UseCom.h"
#include "UseData.h"
#include "MoveDoor.h"

Com com(getDataOfCmd,useDataOfCmd);

void flush_data(){
  com.flush();
}

void sendCmd(int cmd){
  com.sendMsg(cmd);
}

bool sendCmd(int cmd,int nbData,int *data){
  
  return com.sendMsg(cmd,nbData,data);
  
}

void getCmd(){
  com.getMsg();
}


void getDataOfCmd(int cmd,int *nbData,int *_data){

  int v1,v2,v3;

  switch (cmd) {

    case 1 : //temperatue
        *nbData=2;
        getTemperature(&v1,&v2);
        _data[0]=v1;
        _data[1]=v2;
        break;
    case 2 :  //clock now
        *nbData=2;
        getClock(&v1,&v2);
        _data[0]=v1;
        _data[1]=v2;
        break;
     case 3 : //date now
        *nbData=3;
        getDate(&v1,&v2,&v3);
        _data[0]=v1;
        _data[1]=v2;
        _data[2]=v3;
        break;
     case 8 : // is door open
        *nbData=1;
        _data[0]=getDoorPostion();
        break;
     case 11 : // get config opening
        *nbData=6;
        getConfigOpening();
        v1=getData(0);
        _data[0]=v1&255;
        _data[1]=v1>>8;
        for(int i=2;i<6;i++)  _data[i]=getData(i-1);
        break;
     case 12 : // get config closinging
        *nbData=6;
        getConfigCloseing();
        v1=getData(0);
        _data[0]=v1&255;
        _data[1]=v1>>8;
        for(int i=2;i<6;i++)  _data[i]=getData(i-1);
        break;
      case 15 : // get other configs
        *nbData=5;
        getOtherConfigs();
        for(int i=0;i<5;i++)  _data[i]=getData(i);
        break;
      default :
        *nbData=1;
        break;
  }
  /*Serial.println("getDataOfCmd");
  Serial.println(cmd);
  Serial.println(*nbData);
  for(int i=0;i<*nbData;i++)
    Serial.println(_data[i]);*/
  
}

void useDataOfCmd(int cmd,int nbData,int *data){

    switch (cmd) {

    case 132 :      //config H 4+128 
        setData(nbData,data);
        setHour();
        break;
    case 137 :    //ctrl door 9+128
        moveDoor(data[0]);
        break;
    case 138 :      //config Date 10+128 
        setData(nbData,data);
        setDate();
        break;
    case 141 :      //config opening 13+128 
        getConfigMove(nbData,data);
        setConfigOpening();
        break;
    case 142 :      //config closing 14+128 
        getConfigMove(nbData,data);
        setConfigCloseing();
        break;
    case 144 :      //config other config 16+128
        setData(nbData,data);
        setOtherConfigs();
        break;
  }
  /*Serial.println("useDataOfCmd");
  Serial.println(cmd);
  Serial.println(nbData);
  for(int i=0;i<nbData;i++)
    Serial.println(data[i]);*/
  
}
