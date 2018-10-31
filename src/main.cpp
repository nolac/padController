#include <Arduino.h>
#include <LiquidCrystal.h>
#include <MIDI.h>
#include "Clavier.h"
#include "keysDefine.h"
#include "midiMSG.h"

MIDI_CREATE_DEFAULT_INSTANCE();
byte pinX[5]={14,15,16,17,18};
byte pinY[5]={2,3,4,5,6};

LiquidCrystal lcd(12,11,10,9,8,7);
Clavier pad(5,5,pinX,pinY);
byte oldValue=0,currentState=0,notePressed;
bool occuped=false;
byte page=1;
byte valeurSorties[8][5][5]={};
/////////////////////////////////////////
void afficher(byte valeur);
void delRow(bool row);
bool isOccupied();
void incPage();
void decPage();
void updatePageNumber();
void afficherNote(byte note);
void initPadPages();
//////////////////////////////////////////
void setup() {
  //pad.init(valeurSorties);
  //updatePageNumber();
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  MIDI.begin(1);
  Serial.begin(115200);
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("hello");
  lcd.setCursor(0, 1);
  lcd.print(" pad controller ");
  delay(1000);
  lcd.clear();
  afficherNote(0);
  initPadPages();
  updatePageNumber();
}
//////////////////////////////////////////
void loop() {
  currentState=pad.saisie();
  delay(2);/// for debouncing
  if(currentState!=oldValue){
    if(currentState!=0){
      notePressed=currentState;
      if(currentState>=10&&!occuped){
        afficherNote(notePressed);
        MIDI.sendNoteOn(notePressed, 127, 1);
        occuped=true;
      }
      else if(currentState<10){
        occuped=false;
        lcd.setCursor(0,1);
        delRow(1);

        switch (currentState) {
          case PAGE_DOWN:
            decPage();
            break;
          case CTRL2:
            MIDI.sendControlChange(14, 127, 0);
            break;
          case CTRL3:
            MIDI.sendControlChange(15,127,0);
            break;
          case CTRL4:
            MIDI.sendControlChange(16, 127, 0);
            break;
          case PAGE_UP:
            incPage();
            break;
          case CTRL6:
            MIDI.sendControlChange(13, 127, 0);
            break;
          case CTRL7:
            MIDI.sendControlChange(12,127,0);
            break;
          case STOP:
            MIDI.sendControlChange(11, 127, 0);
            break;
          case PLAY:
            MIDI.sendControlChange(10, 127, 0);
            break;
          default:
            delRow(1);
            break;
        }
        if(currentState!=PAGE_UP&&currentState!=PAGE_DOWN){
          afficher(currentState);
        }
      }
    }else if(currentState==0&&occuped){
      afficherNote(0);
      MIDI.sendNoteOff(notePressed, 0, 1);
      occuped=false;
    }
    oldValue=currentState;
  }
}


void delRow(bool row){
  for(int i=0;i<16;i++){
    lcd.setCursor(i, row);
    lcd.print(" ");
  }
}

void afficher(byte valeur){
  if(valeur){
    lcd.setCursor(0,1);
    lcd.print("CC : ");
    lcd.print(valeur);
  }else{
      delRow(1);
  }
}

bool isOccupied(){
  return occuped;
}

void incPage(){
  if(page<numOfPages){
    page++;
  }
  updatePageNumber();
}

void decPage(){
  if(page>1){
    page--;
  }
  updatePageNumber();
}

void updatePageNumber(){
  lcd.setCursor(14,0);
  lcd.print(page);
  byte newTab[5][5];
  for(int i=0;i<5;i++){
    for(int j=0;j<5;j++){
      newTab[i][j]=valeurSorties[page-1][i][j];
    }
  }
  pad.init(newTab);
}

void afficherNote(byte note){
  lcd.setCursor(0, 0);
  lcd.print("note: ");
  lcd.setCursor(5,0);
  lcd.print("   ");
  lcd.setCursor(5, 0);
  if(note!=0){
    if(note<100){
      lcd.print(" ");
      lcd.print(note);
    }else{
      lcd.print(note);
    }
  }else{
    lcd.print("   ");
  }
}


void initPadPages(){
  byte fRank[5]={};
    for(byte i=0;i<5;i++){
        fRank[i]=i;
    }
    for(byte i=0,num=10;i<numOfPages;i++){
        for(byte l=0;l<5;l++){
            valeurSorties[i][0][l]=fRank[l]+1;
        }
        for(byte l=1;l<5;l++){
            for(byte c=0;c<4;c++,num++){
                valeurSorties[i][l][c]=num;
            }
            valeurSorties[i][l][4]=l+5;
        }
    }
}
