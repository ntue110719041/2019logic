#include "pitches.h"


int melody[]={
 NOTE_G4, NOTE_D5, NOTE_C5 , NOTE_G4, NOTE_B4, NOTE_B4, NOTE_C5, NOTE_G4, NOTE_C5, NOTE_G4 ,  NOTE_B4, NOTE_B4, NOTE_C5
};
int noteDurations[]={
4, 4,4, 4,3,3, 2, 4, 4, 4,3,3, 3
};

int melody1[]={
NOTE_G5,NOTE_F5,NOTE_DS5,NOTE_C5,NOTE_G5,NOTE_F5,NOTE_DS5,NOTE_D5,NOTE_DS5,NOTE_D5,NOTE_C5,NOTE_C5
};
int noteDurations1[]={
4,4,4,4,8,4,4,4,8,8,8,8
};
/*--------------------------------------------------*/
int latchPin = 7;
int clockPin = 12;
int dataPin = 11;
const int buttonPin = 2;
int buttonState = 0;
unsigned long CT=0,PT=0;
int cnt=0;
int pauseBetweenNotes;
boolean nexttone=true;

/*--------------------------------------------------*/
byte colDataMatrix[8] = { 
   B01111111,
   B10111111,
   B11011111,
   B11101111,
   B11110111,
   B11111011,
   B11111101,
   B11111110
  };
                      
byte rowDataMatrix[8] = { 
    B10000001,
    B11000011,
    B10111101,
    B10000001,
    B10000001,
    B10100101,
    B10000001,
    B11111111
  };
  byte rowDataMatrix1[8] = {
    B11111111,
    B11000011,
    B10100101,
    B10011001,
    B10011001,
    B10100101,
    B11000011,
    B11111111
  };
// 定義顯示器顯示的時間 (延遲時間), 預設 1ms
int delay_time = 1;     
/*--------------------------------------------------*/
void setup() {
pinMode(latchPin,OUTPUT);
pinMode(clockPin,OUTPUT);
pinMode(dataPin,OUTPUT);
pinMode(buttonPin,INPUT);
digitalWrite(buttonPin,HIGH);
}
/*--------------------------------------------------*/
void loop() {
buttonState = digitalRead(buttonPin);

//按鈕關
if(buttonState == LOW){

if(nexttone){
int noteDuration = 1000 / noteDurations[cnt];
tone(8,melody[cnt],noteDurations);
pauseBetweenNotes=noteDuration*1.30;
nexttone=false;
} 

for(int i = 0; i < 8 ; i++){
digitalWrite(latchPin,LOW);
shiftOut(dataPin, clockPin, MSBFIRST, colDataMatrix[i]);
shiftOut(dataPin, clockPin, MSBFIRST, rowDataMatrix[i]);
digitalWrite(latchPin,HIGH);
delay(delay_time);
}

CT=millis();
if((CT-PT)>pauseBetweenNotes){
cnt++;
nexttone=true;
PT=CT;
}
if(cnt>=13) cnt=0;

}

//按鈕開
else if(buttonState == HIGH){

if(nexttone){
int noteDuration=1000/noteDurations1[cnt];
tone(8,melody1[cnt],noteDurations);
pauseBetweenNotes=noteDuration*1.30;
nexttone=false;
} 

for(int i = 0; i < 8 ; i++){
digitalWrite(latchPin,LOW);
shiftOut(dataPin, clockPin, MSBFIRST, colDataMatrix[i]);
shiftOut(dataPin, clockPin, MSBFIRST, rowDataMatrix1[i]);
digitalWrite(latchPin,HIGH);
delay(delay_time);
}

CT=millis();
if((CT-PT)>pauseBetweenNotes){
cnt++;
nexttone=true;
PT=CT;
}
if(cnt>=12) cnt=0;
 
}

}
/*--------------------------------------------------*/
void pickDigit(int x) {

byte rowByte = 1 << x;

shiftOut(dataPin, clockPin, MSBFIRST, rowByte);

}
void shiftOut(int myDataPin, int myClockPin, byte myDataOut) {
  // This shifts 8 bits out MSB first, 
  //on the rising edge of the clock,
  //clock idles low

  //internal function setup
  int i=0;
  int pinState;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, OUTPUT);

  //clear everything out just in case to
  //prepare shift register for bit shifting
  digitalWrite(myDataPin, 0);
  digitalWrite(myClockPin, 0);

  //for each bit in the byte myDataOut&#239;&#191;&#189;
  //NOTICE THAT WE ARE COUNTING DOWN in our for loop
  //This means that %00000001 or "1" will go through such
  //that it will be pin Q0 that lights. 
  for (i=7; i>=0; i--)  {
    digitalWrite(myClockPin, 0);

    //if the value passed to myDataOut and a bitmask result 
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000 
    // and proceeds to set pinState to 1.
    if ( myDataOut & (1<<i) ) {
      pinState= 1;
    }
    else {        
      pinState= 0;
    }

    //Sets the pin to HIGH or LOW depending on pinState
    digitalWrite(myDataPin, pinState);
    //register shifts bits on upstroke of clock pin  
    digitalWrite(myClockPin, 1);
    //zero the data pin after shift to prevent bleed through
    digitalWrite(myDataPin, 0);
  }

  //stop shifting
  digitalWrite(myClockPin, 0);
}
