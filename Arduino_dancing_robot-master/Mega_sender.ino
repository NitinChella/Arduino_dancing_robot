//const int ledPin = 13; //pin 13 built-in led
const int soundPin = A0; //sound sensor attach to A0
#define SAMPLEPERIODUS 40
#include <Wire.h>

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
  Wire.begin();
}

// 20 - 200hz Single Pole Bandpass IIR Filter
float bassFilter(float sample) {
    static float xv[3] = {0,0,0}, yv[3] = {0,0,0};
    xv[0] = xv[1]; xv[1] = xv[2]; 
    xv[2] = (sample) / 3.f; // change here to values close to 2, to adapt for stronger or weeker sources of line level audio  
    

    yv[0] = yv[1]; yv[1] = yv[2]; 
    yv[2] = (xv[2] - xv[0])
        + (-0.7960060012f * yv[0]) + (1.7903124146f * yv[1]);
    return yv[2];
}

// 10hz Single Pole Lowpass IIR Filter
float envelopeFilter(float sample) { //10hz low pass
    static float xv[2] = {0,0}, yv[2] = {0,0};
    xv[0] = xv[1]; 
    xv[1] = sample / 50.f;
    yv[0] = yv[1]; 
    yv[1] = (xv[0] + xv[1]) + (0.9875119299f * yv[0]);
    return yv[1];
}

// 1.7 - 3.0hz Single Pole Bandpass IIR Filter
float beatFilter(float sample) {
    static float xv[3] = {0,0,0}, yv[3] = {0,0,0};
    xv[0] = xv[1]; xv[1] = xv[2]; 
    xv[2] = sample / 2.7f;
    yv[0] = yv[1]; yv[1] = yv[2]; 
    yv[2] = (xv[2] - xv[0])
        + (-0.7169861741f * yv[0]) + (1.4453653501f * yv[1]);
    return yv[2];
}
byte a=0;
void transmit(int x){
    a=x;
    Wire.beginTransmission(8);
    Wire.write(a);
    Wire.endTransmission();
    a=0;
  }

void loop()
{
  
  float value;//read the value of A0
  unsigned long time = micros(); // Used to track rate
    float sample, val, envelope, beat, thresh;
    unsigned char i;
    for(i = 0;;++i){
//        Read ADC and center so +-127
        value=ADCH;
        sample = value-128;
       //Serial.println(sample);
       

        // Filter only bass component
        val = bassFilter(sample);
        

        // Take signal amplitude and filter
        if(val < 0)val=-val;
        envelope = envelopeFilter(val);
        

        // Every 200 samples (25hz) filter the envelope 
        if(i%200==0) {
                // Filter out repeating bass sounds 100 - 180bpm
                beat = beatFilter(envelope);
                //Serial.println(beat);
                // Threshold it based on potentiometer on AN1
                thresh = 8;

                // If we are above threshold, light up LED
                if(beat > thresh){
                  transmit(1);
                  //Serial.println(1);
                }
                else{ 
                  transmit(0);
                //Serial.println(0);
                }
                
                //Reset sample counter
                //x = 0;
        }

        // Consume excess clock cycles, to keep at 5000 hz
        //for(unsigned long up = time+SAMPLEPERIODUS; time > 20 && time < up; time = micros());
    }
}
