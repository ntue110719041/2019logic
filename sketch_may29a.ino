int latchPin = 8;
int clockPin = 12;
int dataPin = 11;
byte colDataMatrix[8] = { B01111111,
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
    B10100101,
    B10100101,
    B10000001,
    B11111111
  };
// 定義顯示器顯示的時間 (延遲時間), 預設 1ms
int delay_time = 1;
       
void setup() {
pinMode(latchPin,OUTPUT);
pinMode(clockPin,OUTPUT);
pinMode(dataPin,OUTPUT);
}
int buttonPin=2;
int buttonState=0;
void loop() {


buttonState=digitalRead(buttonPin);
 for(int i = 0; i < 8 ; i++){
 //byte colData = colDataMatrix[i];
digitalWrite(latchPin,LOW);
  //  pickDigit(i);
   shiftOut(dataPin, clockPin, MSBFIRST, colDataMatrix[i]);
    shiftOut(dataPin, clockPin, MSBFIRST, rowDataMatrix[i]);
    //shiftOut(dataPin, clockPin, MSBFIRST, colDataMatrix[i]);
    digitalWrite(latchPin,HIGH);
    delay(delay_time);
}
if(buttonState==HIGH) {
  byte rowDataMatrix[8] = { 
    B10000001,
    B11000011,
    B10111101,
    B10000001,
    B10100101,
    B10100101,
    B10000001,
    B11111111
  };
  buttonState==1;
}
else{
 byte rowDataMatrix[8] = { 
    B10000001,
    B11000011,
    B10111101,
    B10000001,
    B10100101,
    B10100101,
    B10000001,
    B11111111
  };
  buttonState==0;

  }}
void pickDigit(int x) {
  byte rowByte = 1 << x;
  shiftOut(dataPin, clockPin, MSBFIRST, rowByte);

}

