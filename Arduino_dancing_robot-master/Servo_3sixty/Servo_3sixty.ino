#include <VarSpeedServo.h>

VarSpeedServo myservo;
int count = 0;


void setup() {
  
  Serial.begin(9600);
  myservo.attach(9);
  delay(5000);
  
  /*
  myservo.writeMicroseconds(700); //senso orario (700 valore minimo)
  delay(2000);
  myservo.writeMicroseconds(1515);//stop
  delay(2000);
  myservo.writeMicroseconds(1700);// senso antiorario (2300 valore massimo)
  delay(1000);
  myservo.writeMicroseconds(1515);//stop*/

}

void loop(){
  
  count++;
  
  if(count%3==0){
    
    //rotate anticlockwise to account for slippage
    
    myservo.writeMicroseconds(1500);
    delay(333);
    myservo.writeMicroseconds(1520);
    delay(333);
    myservo.writeMicroseconds(1500);
    delay(333);
    
    }
    
  myservo.writeMicroseconds(1500);
  delay(333);
  myservo.writeMicroseconds(1435);
  delay(333);
  myservo.writeMicroseconds(1500);
  delay(333);
  myservo.writeMicroseconds(1575);
  delay(333);
  
}
