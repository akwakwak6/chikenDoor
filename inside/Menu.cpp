#include <LiquidCrystal_I2C.h>

#include "Arduino.h"
#include "Menu.h"
#include "Init.h"
#include "UseData.h"
#include "UseCom.h"

extern LiquidCrystal_I2C lcd;

extern bool BpSetEnable,moved;
extern uint8_t PositScreen;
extern int moveDoor;
extern bool cnnctd;

void menu(){

  lcd.clear();
  bpSetPushed();
  PositScreen=0;
  loadScreen();
  BpSetEnable=false;

  flushData();
  
}

void bpSetPushed(){

  switch (PositScreen) {

      case 1 :
      case 2 :
      case 3 :
      case 4 :
      case 5 : 
      case 6 : 
          PositScreen*=10;
        break;
      case 11 :
        setHour();
        PositScreen/=10;
        break;
      case 20 :
        PositScreen/=10;
        break;
      case 32 :
        setDate();
        PositScreen/=10;
        break;
      case 44 :
        setConfigOpening();
        PositScreen/=10;
        break;
      case 54 :
        setConfigCloseing(); 
        PositScreen/=10;
        break;
      case 64 :
        setOtherConfigs(); 
        PositScreen/=10;
        break; 
        
      default :
      PositScreen++;
      break;
        
  }
  loadScreen();
  waitBp();
  
}

void bpUpPushed(){

  int val;

  switch (PositScreen) {

    case 1 :
    case 2 :
    case 3 :
    case 4 :
    case 5 :
      PositScreen++;
      break;
    case 6 :
      PositScreen=1;
      break;
    case 10 :
      val=getNewVal(getData(0),1,0,23,true);
      setData(0,val);
      break;
    case 11 :
      val=getNewVal(getData(1),1,0,59,true);
      setData(1,val);
      break;
    case 20 :
      moveDoor=1;
      PositScreen=0;
      loadScreen();
      return;
      break;
    case 30 :
      val=getNewVal(getData(0),1,1,31,true);
      setData(0,val);
      break;
    case 31 :
      val=getNewVal(getData(1),1,1,12,true);
      setData(1,val);
      break;
    case 32 :
      val=getNewVal(getData(2),1,18,99,true);
      setData(2,val);
      break;
    case 40 :
    case 50 :
      val=getNewVal(getData(0),2,0,254,true);
      setData(0,val);
      break;
    case 41 :
    case 51 :
      val=getNewVal(getData(1),1,0,23,true);
      setData(1,val);
      break;
    case 42 :
    case 52 :
      val=getNewVal(getData(2),1,0,59,true);
      setData(2,val);
      break;
    case 43 :
    case 53 :
      val=getNewVal(getData(3),1,0,23,true);
      setData(3,val);
      break;
    case 44 :
    case 54 :
      val=getNewVal(getData(4),1,0,59,true);
      setData(4,val);
      break;
    case 60 :
      val=getNewVal(getData(0),1,0,2,true);
      setData(0,val);
      break;
    case 61 :
      val=getNewVal(getData(1),1,0,1,true);
      setData(1,val);
      break;
    case 62 :
      val=getNewVal(getData(2),1,0,1,true);
      setData(2,val);
      break;
    case 63 :
      val=getNewVal(getData(3),1,1,5,true);
      setData(3,val);
      break;
    case 64 :
      val=getNewVal(getData(4),1,0,1,true);
      setData(4,val);
      break; 
    
  }
  loadScreen();
  waitBp();
  
}

void bpDwPushed(){

    int val;

    switch (PositScreen) {

    case 2 :
    case 3 :
    case 4 :
    case 5 :
    case 6 :
      PositScreen--;
      break;
    case 1 :
      PositScreen=6;
      break;
    case 10 :
      val=getNewVal(getData(0),1,0,23,false);
      setData(0,val);
      break;
    case 11 :
      val=getNewVal(getData(1),1,0,59,false);
      setData(1,val);
      break;
    case 20 :
      moveDoor=0;
      PositScreen=0;
      loadScreen();
      return;
      break;
    case 30 :
      val=getNewVal(getData(0),1,1,31,false);
      setData(0,val);
      break;
    case 31 :
      val=getNewVal(getData(1),1,1,12,false);
      setData(1,val);
      break;
    case 32 :
      val=getNewVal(getData(2),1,18,99,false);
      setData(2,val);
      break;
    case 40 :
    case 50 :
      val=getNewVal(getData(0),2,0,254,false);
      setData(0,val);
      break;
    case 41 :
    case 51 :
      val=getNewVal(getData(1),1,0,23,false);
      setData(1,val);
      break;
    case 42 :
    case 52 :
      val=getNewVal(getData(2),1,0,59,false);
      setData(2,val);
      break;
    case 43 :
    case 53 :
      val=getNewVal(getData(3),1,0,23,false);
      setData(3,val);
      break;
    case 44 :
    case 54 :
      val=getNewVal(getData(4),1,0,59,false);
      setData(4,val);
      break;
    case 60 :
      val=getNewVal(getData(0),1,0,2,false);
      setData(0,val);
      break;
    case 61 :
      val=getNewVal(getData(1),1,0,1,false);
      setData(1,val);
      break;
    case 62 :
      val=getNewVal(getData(2),1,0,1,false);
      setData(2,val);
      break;
    case 63 :
      val=getNewVal(getData(3),1,1,5,false);
      setData(3,val);
      break;
    case 64 :
      val=getNewVal(getData(4),1,0,1,false);
      setData(4,val);
      break;      
    
  }
  loadScreen();
  waitBp();
  
}

void loadScreen(){

  String str;
  String str2;
  char l1[16];
  char l2[16];
  int v1,v2,v3;

  switch (PositScreen) {
    case 0 :              ///Home : time,date,temp  

        getTemperature(&v1,&v2);
        str2 = String(v1)+","+String(v2)+"  ";

        if(cnnctd){
          if(!getTemperatureOut(&v1,&v2)){
            str2 += String(v1)+","+String(v2)+" ";   
            
            if(!getDoorPosition()){
              switch (getData(0)){
                case 0:   str2 += " fer";
                          break;
                case 1:   str2 += " ouv"; 
                          break;
                default:  str2 += "er ";
                          str2 += String(getData(0));
                          break;
              }
              if(getData(0)>1)
                digitalWrite(LED_GREEN,LOW);
              else
                digitalWrite(LED_GREEN,HIGH);
            }
            if(!getClock(&v1,&v2)){
              if(moved){
                Serial.print(v1);
                Serial.print(":");
                Serial.print(v2);
                Serial.println(" moved");
                moved=false;
              }
              str = getHour(v1,v2)+"  ";
              if(!getDate(&v1,&v2,&v3)){
                str += String(v1)+"/"+String(v2)+"/"+String(v3);
              }else{
                cnnctd=false;
                str = NOT_CONNECTED; 
              }
            }else{
              cnnctd=false;
              str = NOT_CONNECTED; 
            }
          }else{
            cnnctd=false;
            str = NOT_CONNECTED; 
          }
        }else str = NOT_CONNECTED;     
        break;
    case 1:            //Config heure
      str = String(CONFIG)+"l'"+String(HEURE);
      if(cnnctd){
        if(!getClock(&v1,&v2)){
          setData(0,v1);
          setData(1,v2);
          str2 = getHour(v1,v2);
        }else{
          cnnctd=false;
          str2 = NOT_CONNECTED;
        }
      }     else str2 = NOT_CONNECTED;
      break;
    case 2:            //Ctrl Door
      str = "Ctrl porte";
      if(cnnctd){
          str2 = "porte est ";
          getDoorPosition();
          switch (getData(0)){
            case 0:   str2 += "ferm";
                      break;
            case 1:   str2 += "ouve"; 
                      break;
            default:  str2 += "en err";
                      break;
          } 
        
      }else str2 = NOT_CONNECTED;
      break;
    case 3:            //Config Date
      str = String(CONFIG)+"la date";
      if(cnnctd){
        if(!getDate(&v1,&v2,&v3)){
            setData(0,v1);
            setData(1,v2);
            setData(2,v3);
            str2 = String(v1)+"/"+String(v2)+"/"+String(v3);  
        }else{
          cnnctd=false;
          str2 = NOT_CONNECTED;
        }
      } else str2 = NOT_CONNECTED;
      break;
    case 4:            //Config opening
      str = String(CONFIG)+"ouverture";
      if(cnnctd){
        if(!getConfigOpening()){
          str2 = String(getData(0))+" "+getHour(getData(1),getData(2))+"-"+getHour(getData(3),getData(4));
        }else{
          cnnctd=false;
          str2 = NOT_CONNECTED;
        }
      } else str2 = NOT_CONNECTED;
      break;
    case 5:            //Config closing
      str = String(CONFIG)+"fermeture";
      if(cnnctd){
        if(!getConfigCloseing()){
            str2 = String(getData(0))+" "+getHour(getData(1),getData(2))+"-"+getHour(getData(3),getData(4)); 
        }else{
          cnnctd=false;
          str2 = NOT_CONNECTED;
        }
      }else str2 = NOT_CONNECTED;
      break;
    case 6:
      str = String(CONFIG)+"trucs";
      if(cnnctd){  
        if(!getOtherConfigs())  str2 = "autres configs";
        else{
            cnnctd=false;
          str2 = NOT_CONNECTED;
        }
      }else str2 = NOT_CONNECTED;
      break;
    case 10:            //Config heure
      str = String(CONFIG)+String(HEURE);
      v1=getData(0);
      v2=getData(1);
      str2 = getHour(v1,v2);
      break;
    case 11:            //Config heure
      str = String(CONFIG)+"minute";
      v1=getData(0);
      v2=getData(1);
      str2 = getHour(v1,v2);
      break;
    case 20:            //Ctrl door
      str = "Ctrl porte";
      str2 = "ferme - ouvrir";
      break;
    case 30:            //Config jour
      str = String(CONFIG)+"jour";
      v1=getData(0);
      v2=getData(1);
      v3=getData(2);
      str2 = String(v1)+"/"+String(v2)+"/"+String(v3);
      break;
    case 31:            //Config mois
      str = String(CONFIG)+"mois";
      v1=getData(0);
      v2=getData(1);
      v3=getData(2);
      str2 = String(v1)+"/"+String(v2)+"/"+String(v3);
      break;
    case 32:            //Config annee
      str = String(CONFIG)+"annee";
      v1=getData(0);
      v2=getData(1);
      v3=getData(2);
      str2 = String(v1)+"/"+String(v2)+"/"+String(v3);
      break;
    case 40:            //Config light of move
    case 50:
      str = String(CONFIG)+"lumino";
      str2 = String(getData(0))+" "+getHour(getData(1),getData(2))+"-"+getHour(getData(3),getData(4));
      break;
    case 41:            //Config H min for move
    case 51:
      str = String(CONFIG)+"H min";
      str2 = String(getData(0))+" "+getHour(getData(1),getData(2))+"-"+getHour(getData(3),getData(4));
      break;
    case 42:            //Config M min for move
    case 52:
      str = String(CONFIG)+"M min";
      str2 = String(getData(0))+" "+getHour(getData(1),getData(2))+"-"+getHour(getData(3),getData(4));
      break;
    case 43:            //Config H max for move
    case 53:
      str = String(CONFIG)+"H max";
      str2 = String(getData(0))+" "+getHour(getData(1),getData(2))+"-"+getHour(getData(3),getData(4));
      break;
    case 44:            //Config H max for move
    case 54:
      str = String(CONFIG)+"H min";
      str2 = String(getData(0))+" "+getHour(getData(1),getData(2))+"-"+getHour(getData(3),getData(4));
      break;
   case 60:
      str = String(CONFIG)+"Sonnerie"; 
      switch(getData(0)){
      case 0 :  str2 = "jamais";
                break;
      case 1 :  str2 = "mati/soir";
                break;    
      case 2 :  str2 = "mati/soir-erreur";
                break;    
      }   
      break;
   case 61:
      str = String(CONFIG)+"H fixe"; 
      if(getData(1))  str2 = "oui";
      else            str2 = "non";
      break;
   case 62:
      str = String(CONFIG)+"S IN/OUT"; 
      if(getData(2))  str2 = "IN";
      else            str2 = "OUT";
      break;
   case 63:
      str = String(CONFIG)+"nbChekOk"; 
      str2 = String(getData(3));
      break;
   case 64:
      str = String(CONFIG)+"send lux"; 
      if(getData(4) == 1) str2 = "oui";
      else                str2 = "non";
      break;
      
      default :
      str = PositScreen;
      break;
  }


  str.toCharArray(l1,16);
  str2.toCharArray(l2,16);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(l1);
  lcd.setCursor(0, 1);
  lcd.print(l2);
  
}

void waitBp(){

  int cptTooLong;
  bool bpDw=true,bp_Set=true,bpUp=true;

  delay(150);

  cptTooLong=CPT_TO_PUSH;

  while (bpDw&&bpUp&&bp_Set&&cptTooLong){
    cptTooLong--; 
    delay(100);
    bpUp=digitalRead(bp_up);
    bp_Set=digitalRead(bpSet);
    bpDw=digitalRead(bp_down);
    
  }
  
  if(cptTooLong==0) return;
  else if(bpUp==false) bpUpPushed();
  else if(bpDw==false) bpDwPushed();
  else if(bp_Set==false) bpSetPushed();
  
}
