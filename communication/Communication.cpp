#include "Arduino.h"
#include "communication.h"


Com::Com(void (*function)(int cmd,int *nbData,int *data),void (*function2)(int cmd,int nbData,int *data)){
  
  getDataOfCmd = function;
  useDataOfCmd = function2;
	cptSameCmd=0;	
}

void Com::flush(){
	Serial1.flush();
}


void Com::getMsg(){ 

	//Serial.println("get Msg ?");
  if(!Serial1.available())
    return;

	//Serial.println("get Msg OK");

  cmd=Serial1.read();
	
		/*Serial.print(" cmd du msg ");
		Serial.println(cmd);
		Serial.print(" last cmd ");
		Serial.println(lastCmd);*/

	/*if(cmd==lastCmd){
		cptSameCmd++;
		if(cptSameCmd>10)	return;	
	}
	else cptSameCmd=0;*/
		
	lastCmd=cmd;
  Serial1.write(cmd^85);


  if(cmd>=128){
    setGet=false;
    msgGet();
  }
  else{
    setGet=true;
    cmd=cmd&127;
    getDataOfCmd(cmd,&nbData,dataTab);
    msgSet();
  }
     
}



bool Com::sendMsg(int _cmd,int _nbData,int *_data){

	//Serial.println("send Msg avec data");

  cmd=_cmd+128;
  nbData=_nbData;
  for(int i=0;i<_nbData;i++){
    dataTab[i]=_data[i]; 
  }
  setGet=true;
  
  if(sendData(cmd))
    return true;

  if(msgSet())
	return true;
	
	return false;	
}


bool Com::sendMsg(int commande){

	//Serial.println("send msg sans data");

  cmd=commande;
  setGet=false;
  
  if(sendData(cmd))
    return true;

  if(msgGet())
	return true;

	return false;
  
}




bool Com::msgSet(){

	//Serial.println("set Msg");

  
  if(sendData(nbData))
    return true;

  for(int i=0;i<nbData;i++){
      if(sendData(dataTab[i]))
        return true;
  }

  return false;
}



bool Com::msgGet(){

	//Serial.println("set Get");	

  if(getData())
    return true;

  nbData=data;  

  for(int i=0;i<nbData;i++){
    if(getData())
      return true;
    dataTab[i]=data;
		//Serial.println(data);
  }

  useDataOfCmd(cmd , nbData , dataTab);
  
  return false;
  
}



bool Com::sendData(int v){

  int val,cptTooLong;

  Serial1.write(v);

  cptTooLong=CPT_TOO_LONG;
  while ((!Serial1.available())&&(cptTooLong)){
    cptTooLong--; 
    delay(100);
  }
  if(!cptTooLong){
    return true;
  }
  val=Serial1.read();
  
  if(val!=(v^85)){  
    return true;
  }

  return false;
  
}



bool Com::getData(){

  int cptTooLong;

  cptTooLong=CPT_TOO_LONG;

  while ((!Serial1.available())&&(cptTooLong)){
    cptTooLong--; 
    delay(100);
  }
  if(!cptTooLong){
    return true;
  }
  data=Serial1.read();
  
  Serial1.write(data^85);
  
  return false;
}















