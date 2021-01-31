#ifndef UseCom_h
#define UseCom_h

#define TEMPER 1 // get temperature

void sendCmd(int cmd);
bool sendCmd(int cmd,int nbData,int *data);
void getCmd();
void flush_data();

void getDataOfCmd(int cmd,int *nbData,int *_data);
void useDataOfCmd(int cmd,int nbData,int *data);


#endif
