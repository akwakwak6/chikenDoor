#ifndef UseCom_h
#define UseCom_h

#define TEMPER 1 // get temperature out

void setBusy(bool b);
bool getBusy();

bool sendCmd(int cmd);
bool sendCmd(int cmd,int nbData,int *data);
void getCmd();
void flush_data();
void moveDoorUpdate();

void getDataOfCmd(int cmd,int *nbData,int *_data);
void useDataOfCmd(int cmd,int nbData,int *data);


#endif
