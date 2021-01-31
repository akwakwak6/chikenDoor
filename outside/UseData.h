#ifndef UseData_h
#define UseData_h

#include "Arduino.h"

bool isSendLog();
void sendLog();
//void sendLog(int s1,int s2);
void setOtherConfigs();
void getOtherConfigs();
void getConfigMove(int nbData,int *data);
void setConfigOpening();
void setConfigCloseing();
void getConfigOpening();
void getConfigCloseing();
void getConfig(int *vals);
void setDoorPostion(int b);
int getDoorPostion();
void getTemperature(int *v1,int *v2);
void MoveDoorUpdate(int nbData,int *data);
void MoveDoorEnd(int error);
void getClock(int *v1,int *v2);
void setData(int nbData,int *data);
void setData(int posit,int data);
int getData(int posit);
int getNewVal(int val,int step_,int mi,int ma,bool up);
void getDate(int *v1,int *v2,int *v3);
String getHour(int h,int m);
void setHour();
void setDate();
void flushData();
  

#endif
