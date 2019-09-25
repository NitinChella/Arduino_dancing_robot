/*
 * The professor asked me to check this library out in particular.
 * I have tested it. It works on the Uno.
 * This is the link for the library:
 * https://github.com/ivanseidel/ArduinoThread
 * Download it, remove the -master suffix, add it to your Arduino Libraries.
 * The instructions are available on the webpage too.
 */

#include <Thread.h>
int ledPin = LED_BUILTIN;

//My simple Thread
Thread myThread = Thread();

// callback for myThread
void niceCallback(){
  static bool ledStatus = false;
  ledStatus = !ledStatus;

  digitalWrite(ledPin, ledStatus);

  Serial.print("COOL! I'm running on: ");
  Serial.println(millis());
}

void setup(){
  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);

  myThread.onRun(niceCallback);
  myThread.setInterval(500);
}

void loop(){
  // checks if thread should run
  if(myThread.shouldRun())
    myThread.run();

  // Other code...
  int x = 0;
  x = 1 + 2;
}
