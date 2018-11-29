#include <SoftwareSerial.h>

String line = "";
SoftwareSerial mySerial(3,4);  //rx, tx

void setup()
{
   mySerial.begin(9600);
   pinMode(0, OUTPUT);
   pinMode(3, INPUT);
   pinMode(4, OUTPUT);
   
}

void loop(){

  if(mySerial.available()){
    char inChar = mySerial.read();
    line += inChar;

    if (inChar == '\n') {
        line = "";
    }

    //Kvuli relay tady musi bejt 0, aby se sepnulo svetlo. Standardne by tu melo byt 1
    if(line.indexOf('0') >= 0){
      digitalWrite(0, HIGH);
    }
    
    //Kvuli relay tady musi bejt 1, aby se vypnulo svetlo. Standardne by tu melo byt 0
    if(line.indexOf('1') >= 0){
      digitalWrite(0, LOW);
    }
  }    
}
