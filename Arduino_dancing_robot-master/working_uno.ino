#include <Servo.h>
#define trigPin1 2
#define echoPin1 3

Servo servoBody;
Servo servoNeck;
Servo servoHead;

long duration, distance, S1, S2, S3;

int body=5;
int neck=6;
int head=7;

int middle_body =100;
int middle_neck=90;
int low_body=95;
int high_body=105;
int delay_body=40;
int low_neck=45;
int high_neck=135;
int delay_neck=10;
int head_stop=94;
int head_high=110;
int head_low=75;
int delay_head=500;

unsigned long time;
unsigned long end_time;

void setup() {
Serial.begin(9600);
  servoNeck.attach(neck);
  servoNeck.write(middle_neck);
  servoBody.attach(body);
  servoBody.write(middle_body);// start serial for output
  servoHead.attach(head);
  servoHead.write(head_stop);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
}



void SonarSensor(int trigPin,int echoPin)
{

digitalWrite(trigPin, LOW);
delayMicroseconds(2); // This ensures clean high pulse
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = (duration/2) * 0.03445; // distance in cm, speed of sound at 22.5 C

}


void move_fast(){
 for (int pos = middle_neck; pos <= high_neck; pos += 1) {
    servoNeck.write(pos); // tell servo to go to position in variable 'pos'
    delay(delay_neck);                       // waits 15ms for the servo to reach the position
  }
  for (int pos = high_neck; pos >=low_neck; pos -= 1) { 
    servoNeck.write(pos);// tell servo to go to position in variable 'pos'
    delay(delay_neck);                       // waits 15ms for the servo to reach the position
  }
  for (int pos = low_neck; pos <= middle_body; pos += 1) { 
    servoNeck.write(pos);// tell servo to go to position in variable 'pos'
    delay(delay_neck);                       // waits 15ms for the servo to reach the position
  }
  for (int pos = middle_body; pos <= high_neck; pos += 1) {
    servoNeck.write(pos); // tell servo to go to position in variable 'pos'
    delay(delay_neck);                       // waits 15ms for the servo to reach the position
  }
  for (int pos = high_neck; pos >=low_neck; pos -= 1) { 
    servoNeck.write(pos);// tell servo to go to position in variable 'pos'
    delay(delay_neck);                       // waits 15ms for the servo to reach the position
  }
  for (int pos = low_neck; pos <= middle_body; pos += 1) { 
    servoNeck.write(pos);// tell servo to go to position in variable 'pos'
    delay(delay_neck);                       // waits 15ms for the servo to reach the position
  }
  Serial.println("F");
}

void move_slow(){
 for (int pos = middle_body; pos <= high_body; pos += 1) {
    servoBody.write(pos); // tell servo to go to position in variable 'pos'
    delay(delay_body);                       // waits 15ms for the servo to reach the position
  }
  for (int pos = high_body; pos >=low_body; pos -= 1) { 
    servoBody.write(pos);// tell servo to go to position in variable 'pos'
    delay(delay_body);                       // waits 15ms for the servo to reach the position
  }
  for (int pos = low_body; pos <= middle_body; pos += 1) { 
    servoBody.write(pos);// tell servo to go to position in variable 'pos'
    delay(delay_body);                       // waits 15ms for the servo to reach the position
  }
  for (int pos = middle_body; pos <= high_body; pos += 1) {
    servoBody.write(pos); // tell servo to go to position in variable 'pos'
    delay(delay_body);                       // waits 15ms for the servo to reach the position
  }
  for (int pos = high_body; pos >=low_body; pos -= 1) { 
    servoBody.write(pos);// tell servo to go to position in variable 'pos'
    delay(delay_body);                       // waits 15ms for the servo to reach the position
  }
  for (int pos = low_body; pos <= middle_body; pos += 1) { 
    servoBody.write(pos);// tell servo to go to position in variable 'pos'
    delay(delay_body);                       // waits 15ms for the servo to reach the position
  }
  Serial.println("S");
} 

//start when song is finnished 
void kill_move(){
  servoHead.write(head_stop);
  delay(delay_head);
  servoHead.write(head_high);
  delay(delay_head);
  servoHead.write(head_stop);
  delay(1000);
  servoHead.write(head_low);
  delay(delay_head);
  servoHead.write(head_stop);
  Serial.println("K");
}

void human_detected(){
  for (int pos = middle_neck; pos <= 120; pos += 1) { // goes from 0 degrees to 180 degrees
    servoNeck.write(pos); // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
  for (int pos = 120; pos >= middle_neck; pos -= 1) { 
    servoNeck.write(pos); // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
  for (int pos = middle_neck; pos <= 120; pos += 1) { // goes from 0 degrees to 180 degrees
    servoNeck.write(pos); // tell servo to go to position in variable 'pos'
    delay(30);                       // waits 15ms for the servo to reach the position
  }
  for (int pos = 120; pos >= middle_neck; pos -= 1) { 
    servoNeck.write(pos); // tell servo to go to position in variable 'pos'
    delay(30);                       // waits 15ms for the servo to reach the position
  }
  Serial.println("H");
}
  
char com=' ';
int count=0;
bool kill=false;

void loop() {
  // Check if there is anything in the soft Serial Buffer 
  if (Serial.available()){ 
// Read one value from the soft serial buffer and store it in the variable com 
  com = Serial.read(); 
  Serial.println(com);
  }
  if(com=='3'){
    kill_move();
    //Serial.println("Kill");
    kill=true;
    }
  if(!kill){
     SonarSensor(trigPin1, echoPin1);
     S1 = distance;
     if(S1<50){
     human_detected();
     }
    //Serial.println("h");
    else{
      if(com=='1'){  
        //Serial.println("Beat received");
        move_fast();
          //count+=1;
        }
        else{
        move_slow();
        //count=0;
        }
      //}
    }
  }
    com='0';
}
