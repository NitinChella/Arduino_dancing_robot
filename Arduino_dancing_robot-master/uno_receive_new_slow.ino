#include <Servo.h>

Servo myServo;

unsigned long prevMillis;
unsigned long currentMillis;

void move_slow(int middle, int max, int min, long delay){

prevMillis = millis();

for(int i = middle; i <= max; i++){

myServo.write(i);

currentMillis = millis();

while(currentMillis - prevMillis < delay){

currentMillis = millis();

}

prevMillis = currentMillis;

}

prevMillis = millis();

for(int i = max; i >= min; i--){

myServo.write(i);

currentMillis = millis();

while(currentMillis - prevMillis < delay){

currentMillis = millis();

}

prevMillis = currentMillis;

}

prevMillis = millis();

for(int i = min; i <= max; i++){

myServo.write(i);

currentMillis = millis();

while(currentMillis - prevMillis < delay){

currentMillis = millis();

}

prevMillis = currentMillis;

}
  
prevMillis = millis();

for(int i = max; i >= middle; i--){

myServo.write(i);

currentMillis = millis();

while(currentMillis - prevMillis < delay){

currentMillis = millis();

}

prevMillis = currentMillis;

}

move_slow(middle, max, min, delay);

}
