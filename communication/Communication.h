#ifndef Communication_h
#define Communication_h

#define CPT_TOO_LONG 20


class Com {

  public:
  
    Com(void (*function)(int cmd,int *nbData,int *data),void (*function2)(int cmd,int nbData,int *data));
    bool sendMsg(int commande);
    bool sendMsg(int cmd,int nbData,int *data);
    void getMsg();
	void flush();

  private:

    int cmd,lastCmd;
    bool setGet;
    int dataTab[10],data;
    int nbData;
	int cptSameCmd;

    bool msgSet();
    bool msgGet();
    bool sendData(int data);
    bool getData();

    void (*getDataOfCmd)(int cmd,int *nbData,int *data);
     void (*useDataOfCmd)(int cmd,int nbData,int *data);
    
};

#endif




