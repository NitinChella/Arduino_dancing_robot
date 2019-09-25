
//#include <Servo.h>
#include <VarSpeedServo.h>
VarSpeedServo servo;
//Servo myservox, myservoy,myservoz;


 
void setup()
{
  servo.attach(6);
  

servo.write(0);
delay(500);
servo.write(120);
delay(500);
servo.write(60);
delay(2000);
servo.write(90);

}
 
void loop()
{
  
} 
 


