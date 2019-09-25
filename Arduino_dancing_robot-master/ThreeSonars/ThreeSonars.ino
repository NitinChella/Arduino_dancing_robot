// NOTE: Range of HCSR04 - 2cm to 400cm; Angle of sight - -15 degrees to +15 degrees = efectively 30 degrees


#define trigPin1 2
#define echoPin1 3
#define trigPin2 4
#define echoPin2 5
#define trigPin3 6
#define echoPin3 7


long duration, distance, S1, S2, S3, arr[3]= {};
int mov_arr[3] = {0, 0, 0};
const int buffer_size = 10;
int buffer[buffer_size] = {0};
String sensor_names[3] = {"S1", "S2", "S3"};
int last_index = -1;
int prev_pos = 1, curr_pos = 0;

void setup()
{
Serial.begin (9600);

pinMode(trigPin1, OUTPUT);
pinMode(echoPin1, INPUT);
pinMode(trigPin2, OUTPUT);
pinMode(echoPin2, INPUT);
pinMode(trigPin3, OUTPUT);
pinMode(echoPin3, INPUT);
}

void loop() {
  
SonarSensor(trigPin1, echoPin1);
S1 = distance;

SonarSensor(trigPin2, echoPin2);
S2 = distance;

SonarSensor(trigPin3, echoPin3);
S3 = distance;

arr[0] = S1;
arr[1] = S2; 
arr[2] = S3; 

int min_index = 0;
for(int i = 0; i<3; i++){

if(arr[i]<arr[min_index]){
  min_index = i;
  }
  
}

if(min_index == 0){

  Serial.print("Object in front of S1, distance = ");
  mov_arr[0]++;
  
  }else if(min_index == 1){

     Serial.print("Object in front of S2, distance = ");
     mov_arr[1]++;
  
  }else{

     Serial.print("Object in front of S3, distance = ");
     mov_arr[2]++;
  
  }

  Serial.println(arr[min_index]);

  if(last_index == -1){

    last_index++;
    buffer[last_index] = min_index;
    
    }

  // buffer operations
  if(last_index >=0 && buffer[last_index] == min_index){

    last_index++;
    buffer[last_index] = min_index;
    
    }

    else if(last_index >=0 && buffer[last_index] != min_index){

      last_index = -1;
      
      }

    if(last_index==buffer_size-1){

      last_index = -1;
      curr_pos = buffer[buffer_size-1];
      
      if(curr_pos != prev_pos){
      Serial.print("*** ");
      Serial.print("Object moved from ");
      Serial.print(sensor_names[prev_pos]);
      Serial.print(" to ");
      Serial.print(sensor_names[curr_pos]);
      Serial.print(". ");
      if(mov_arr[curr_pos]>mov_arr[prev_pos]){
        Serial.print("Distance Increased. ");
        }
        else if(mov_arr[curr_pos]<mov_arr[prev_pos]){
          Serial.print("Distance reduced. ");
          }
      Serial.println(" ***");
      }
      
      }

      prev_pos = curr_pos;
       
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

/* V1
   if(mov_arr[0] > mov_threshold){

    mov_arr[0] = 0;
    mov_arr[1] = 0;
    mov_arr[2] = 0;
    mov_arr[3] = 0;
    curr_pos = 0;
    
    }else if(mov_arr[1]> mov_threshold){

    mov_arr[0] = 0;
    mov_arr[1] = 0;
    mov_arr[2] = 0;
    mov_arr[3] = 0;
    curr_pos = 1;
      
      }else if(mov_arr[2]> mov_threshold){

    mov_arr[0] = 0;
    mov_arr[1] = 0;
    mov_arr[2] = 0;
    mov_arr[3] = 0;
    curr_pos = 2;
      
      }else if(mov_arr[3]> mov_threshold){

    mov_arr[0] = 0;
    mov_arr[1] = 0;
    mov_arr[2] = 0;
    mov_arr[3] = 0;
    curr_pos = 3;
        
        }

        if(curr_pos != prev_pos){
    Serial.println("***")
    Serial.print("POSITION CHANGE FROM ");
    Serial.print(sensor_names[prev_pos]);
    Serial.print(" TO ");
    Serial.println(sensor_names[curr_pos]);
      
      }

      else{

         Serial.print("CURRENT POSITION ");
         Serial.print(sensor_names[curr_pos]);
        
        }

        prev_pos = curr_pos;
 */
