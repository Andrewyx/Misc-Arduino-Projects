/* 
  Sketch generated by the Arduino IoT Cloud Thing "Untitled"
  https://create.arduino.cc/cloud/things/6e8e43fa-e632-4d25-ba94-7b887cfe2b9a 

  Arduino IoT Cloud Variables description

  The following variables are automatically generated and updated when changes are made to the Thing

  CloudMotionSensor motionCloud;
  CloudTemperatureSensor temperature;
  int distance;
  int lDRCloud;
  bool playstate;

  Variables which are marked as READ/WRITE in the Cloud Thing will also have functions
  which are called when their values are changed from the Dashboard.
  These functions are generated with the Thing and added at the end of this sketch.
*/


#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

#include "thingProperties.h"
//#include <pitches.h>

//

//


int x;
const int ledpin = 4;
const int analogpin = A0;
const int pwrtmp = D0, pwrldr = D8;
bool multstate = false;
unsigned long miltime = millis(), prevmil = 0;
const int multinterval = 200;
float temptmp;
int templdr, tolerance = -9;
long duration;
const int motpin = D1, trigpin = D2, echopin = D3;
const int tonePin = D5;

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  delay(1500);

  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  pinMode(ledpin, OUTPUT);
  pinMode(motpin, INPUT);
  pinMode(analogpin, INPUT);
  pinMode(pwrldr, OUTPUT);
  pinMode(pwrtmp, OUTPUT);
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  pinMode(tonePin, OUTPUT);
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}


void multiplex(){
  miltime = millis();
  if (miltime - prevmil >= multinterval){
      multstate = !multstate;
      prevmil = miltime;
  }     

    if (multstate == true){
        //ldr on
        digitalWrite(pwrtmp, LOW);
        digitalWrite(pwrldr, HIGH);
        templdr = analogRead(analogpin);
        Serial.print(" LDR: ");
        Serial.print(templdr);
        lDRCloud = templdr;
        
    }
    
    else if (multstate == false){
        //tmp on
        digitalWrite(pwrldr, LOW);
        digitalWrite(pwrtmp, HIGH);
        temptmp = analogRead(analogpin);
        
        temperature = ((temptmp * 3300)/1023)/10 + tolerance;
        Serial.print(" Temp: ");
        Serial.println(temperature);
      
    }
    

}

void midi() {

    tone(tonePin, NOTE_E3, 400);
    delay(400);
    /*
    for(int y = NOTE_E3; y <= NOTE_FS3; y+=4){
      tone(tonePin, y, 8);
      delay(10);
      noTone(tonePin);
    }
    */
    tone(tonePin, NOTE_FS3, 200);
    delay(200);
    
    for(int x = NOTE_E3; x <= NOTE_B4; x+=9){
      tone(tonePin, x, 9);
      delay(10);
      noTone(tonePin);
    }
    
    tone(tonePin, NOTE_B4, 400);
    delay(400);
    
    for(int z = NOTE_B4; z >= NOTE_E2; z-=9){
      tone(tonePin, z, 10);
      delay(10);
      noTone(tonePin);
    }
    
    tone(tonePin, NOTE_E2, 600);
    delay(600);
    noTone(tonePin);

}


void motiondet(){

    motionCloud = digitalRead(motpin);
    if (motionCloud == HIGH){
      Serial.println("Motion Detected!");
      midi();
    }
    
}

void ultrasonic(){
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echopin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.print(distance);
}

void loop() {
  ArduinoCloud.update();
  
  // Your code here 
  multiplex();
  ultrasonic();
  motiondet();
}

/*
  Since Playstate is READ_WRITE variable, onPlaystateChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onPlaystateChange()  {
  // Add your code here to act upon Playstate change

/*
  Since OnBoardLED is READ_WRITE variable, onOnBoardLEDChange() is
  executed every time a new value is received from IoT Cloud.
*/
}







