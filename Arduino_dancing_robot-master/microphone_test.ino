/***********************************************
* name:Sound Sensor
* function: you can see the value of sound intensity on Serial Monitor.
* When the volume reaches to a certain value, the LED attached to pin 13 on the SunFounder Uno board will light up. 
**************************************************/
//Email:support@sunfounder.com
//Website:www.sunfounder.com

//const int ledPin = 13; //pin 13 built-in led
const int soundPin = A0; //sound sensor attach to A0

void setup()
{
//  pinMode(ledPin,OUTPUT);//set pin13 as OUTPUT
  Serial.begin(9600); //initialize serial
    //clear ADCSRA and ADCSRB registers
  ADCSRA = 0;
  ADCSRB = 0;
  
  ADMUX |= (1 << REFS0); //set reference voltage
  ADMUX |= (1 << ADLAR); //left align the ADC value- so we can read highest 8 bits from ADCH register only
  
  ADCSRA |= (1 << ADPS2) | (1 << ADPS0); //set ADC clock with 32 prescaler- 16mHz/32=500kHz
  ADCSRA |= (1 << ADATE); //enabble auto trigger
  ADCSRA |= (1 << ADEN); //enable ADC
  ADCSRA |= (1 << ADSC); //start ADC measurements
  
  //if you want to add other things to setup(), do it here
}

void loop()
{
  int value = ADCH;//read the value of A0
  Serial.println(value);//print the value
}
