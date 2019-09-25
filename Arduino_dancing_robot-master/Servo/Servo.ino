//#include <Servo.h>
#include <VarSpeedServo.h>

VarSpeedServo servo;
//Servo myservox, myservoy,myservoz;


void setup()
{
  servo.attach(9);
  servo.write(90);
  delay(1000);
  servo.write(120);
  delay(1000);
  servo.write(60);
  delay(2000);
  servo.write(90);

}
 
void loop()
{
  
} 
 
