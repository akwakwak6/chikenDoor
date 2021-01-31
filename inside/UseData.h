#ifndef UseData_h
#define UseData_h

#include "Arduino.h"

bool setOtherConfigs();
bool getOtherConfigs();
bool isRingError();
bool isRingMorNig();
void getConfigMoveBack();
void setConfigOpening();
void setConfigCloseing();
void getConfigMove(int nbData,int *data);
bool getConfigCloseing();
bool getConfigOpening();

bool getDoorPosition();


void moveDoorUpdate();
void moveDoorEnd(int msg);
void manageLeds(int val);
void getTemperature(int *v1,int *v2);
bool getTemperatureOut(int *v1,int *v2);
void setData(int nbData,int *data);
bool getClock(int *v1,int *v2);
bool getDate(int *v1,int *v2,int *v3);
String getHour(int h,int m);
bool setHour();
bool setDate();
void setData(int posit,int data);
int getData(int posit);
int getNewVal(int val,int step_,int mi,int ma,bool up);
void flushData();
  

#endif
