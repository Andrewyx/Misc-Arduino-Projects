#include <Servo.h>
#include <pitches.h>
#define REST      0

// notes of the moledy followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
int melody[] = {

  // Never Gonna Give You Up - Rick Astley
  // Score available at https://musescore.com/chlorondria_5/never-gonna-give-you-up_alto-sax
  // Arranged by Chlorondria

  NOTE_D5, -4, NOTE_E5, -4, NOTE_A4, 4, //1
  NOTE_E5, -4, NOTE_FS5, -4, NOTE_A5, 16, NOTE_G5, 16, NOTE_FS5, 8,
  NOTE_D5, -4, NOTE_E5, -4, NOTE_A4, 2,
  NOTE_A4, 16, NOTE_A4, 16, NOTE_B4, 16, NOTE_D5, 8, NOTE_D5, 16,
  NOTE_D5, -4, NOTE_E5, -4, NOTE_A4, 4, //repeat from 1
  NOTE_E5, -4, NOTE_FS5, -4, NOTE_A5, 16, NOTE_G5, 16, NOTE_FS5, 8,
  NOTE_D5, -4, NOTE_E5, -4, NOTE_A4, 2,
  NOTE_A4, 16, NOTE_A4, 16, NOTE_B4, 16, NOTE_D5, 8, NOTE_D5, 16,
  REST, 4, NOTE_B4, 8, NOTE_CS5, 8, NOTE_D5, 8, NOTE_D5, 8, NOTE_E5, 8, NOTE_CS5, -8,
  NOTE_B4, 16, NOTE_A4, 2, REST, 4,

  REST, 8, NOTE_B4, 8, NOTE_B4, 8, NOTE_CS5, 8, NOTE_D5, 8, NOTE_B4, 4, NOTE_A4, 8, //7
  NOTE_A5, 8, REST, 8, NOTE_A5, 8, NOTE_E5, -4, REST, 4,
  NOTE_B4, 8, NOTE_B4, 8, NOTE_CS5, 8, NOTE_D5, 8, NOTE_B4, 8, NOTE_D5, 8, NOTE_E5, 8, REST, 8,
  REST, 8, NOTE_CS5, 8, NOTE_B4, 8, NOTE_A4, -4, REST, 4,
  REST, 8, NOTE_B4, 8, NOTE_B4, 8, NOTE_CS5, 8, NOTE_D5, 8, NOTE_B4, 8, NOTE_A4, 4,
  NOTE_E5, 8, NOTE_E5, 8, NOTE_E5, 8, NOTE_FS5, 8, NOTE_E5, 4, REST, 4,

  NOTE_D5, 2, NOTE_E5, 8, NOTE_FS5, 8, NOTE_D5, 8, //13
  NOTE_E5, 8, NOTE_E5, 8, NOTE_E5, 8, NOTE_FS5, 8, NOTE_E5, 4, NOTE_A4, 4,
  REST, 2, NOTE_B4, 8, NOTE_CS5, 8, NOTE_D5, 8, NOTE_B4, 8,
  REST, 8, NOTE_E5, 8, NOTE_FS5, 8, NOTE_E5, -4, NOTE_A4, 16, NOTE_B4, 16, NOTE_D5, 16, NOTE_B4, 16,
  NOTE_FS5, -8, NOTE_FS5, -8, NOTE_E5, -4, NOTE_A4, 16, NOTE_B4, 16, NOTE_D5, 16, NOTE_B4, 16,

  NOTE_E5, -8, NOTE_E5, -8, NOTE_D5, -8, NOTE_CS5, 16, NOTE_B4, -8, NOTE_A4, 16, NOTE_B4, 16, NOTE_D5, 16, NOTE_B4, 16, //18
  NOTE_D5, 4, NOTE_E5, 8, NOTE_CS5, -8, NOTE_B4, 16, NOTE_A4, 8, NOTE_A4, 8, NOTE_A4, 8,
  NOTE_E5, 4, NOTE_D5, 2, NOTE_A4, 16, NOTE_B4, 16, NOTE_D5, 16, NOTE_B4, 16,
  NOTE_FS5, -8, NOTE_FS5, -8, NOTE_E5, -4, NOTE_A4, 16, NOTE_B4, 16, NOTE_D5, 16, NOTE_B4, 16,
  NOTE_A5, 4, NOTE_CS5, 8, NOTE_D5, -8, NOTE_CS5, 16, NOTE_B4, 8, NOTE_A4, 16, NOTE_B4, 16, NOTE_D5, 16, NOTE_B4, 16,

  NOTE_D5, 4, NOTE_E5, 8, NOTE_CS5, -8, NOTE_B4, 16, NOTE_A4, 4, NOTE_A4, 8, //23
  NOTE_E5, 4, NOTE_D5, 2, REST, 4,
  REST, 8, NOTE_B4, 8, NOTE_D5, 8, NOTE_B4, 8, NOTE_D5, 8, NOTE_E5, 4, REST, 8,
  REST, 8, NOTE_CS5, 8, NOTE_B4, 8, NOTE_A4, -4, REST, 4,
  REST, 8, NOTE_B4, 8, NOTE_B4, 8, NOTE_CS5, 8, NOTE_D5, 8, NOTE_B4, 8, NOTE_A4, 4,
  REST, 8, NOTE_A5, 8, NOTE_A5, 8, NOTE_E5, 8, NOTE_FS5, 8, NOTE_E5, 8, NOTE_D5, 8,

  REST, 8, NOTE_A4, 8, NOTE_B4, 8, NOTE_CS5, 8, NOTE_D5, 8, NOTE_B4, 8, //29
  REST, 8, NOTE_CS5, 8, NOTE_B4, 8, NOTE_A4, -4, REST, 4,
  NOTE_B4, 8, NOTE_B4, 8, NOTE_CS5, 8, NOTE_D5, 8, NOTE_B4, 8, NOTE_A4, 4, REST, 8,
  REST, 8, NOTE_E5, 8, NOTE_E5, 8, NOTE_FS5, 4, NOTE_E5, -4,
  NOTE_D5, 2, NOTE_D5, 8, NOTE_E5, 8, NOTE_FS5, 8, NOTE_E5, 4,
  NOTE_E5, 8, NOTE_E5, 8, NOTE_FS5, 8, NOTE_E5, 8, NOTE_A4, 8, NOTE_A4, 4,

  REST, -4, NOTE_A4, 8, NOTE_B4, 8, NOTE_CS5, 8, NOTE_D5, 8, NOTE_B4, 8, //35
  REST, 8, NOTE_E5, 8, NOTE_FS5, 8, NOTE_E5, -4, NOTE_A4, 16, NOTE_B4, 16, NOTE_D5, 16, NOTE_B4, 16,
  NOTE_FS5, -8, NOTE_FS5, -8, NOTE_E5, -4, NOTE_A4, 16, NOTE_B4, 16, NOTE_D5, 16, NOTE_B4, 16,
  NOTE_E5, -8, NOTE_E5, -8, NOTE_D5, -8, NOTE_CS5, 16, NOTE_B4, 8, NOTE_A4, 16, NOTE_B4, 16, NOTE_D5, 16, NOTE_B4, 16,
  NOTE_D5, 4, NOTE_E5, 8, NOTE_CS5, -8, NOTE_B4, 16, NOTE_A4, 4, NOTE_A4, 8,

  NOTE_E5, 4, NOTE_D5, 2, NOTE_A4, 16, NOTE_B4, 16, NOTE_D5, 16, NOTE_B4, 16, //40
  NOTE_FS5, -8, NOTE_FS5, -8, NOTE_E5, -4, NOTE_A4, 16, NOTE_B4, 16, NOTE_D5, 16, NOTE_B4, 16,
  NOTE_A5, 4, NOTE_CS5, 8, NOTE_D5, -8, NOTE_CS5, 16, NOTE_B4, 8, NOTE_A4, 16, NOTE_B4, 16, NOTE_D5, 16, NOTE_B4, 16,
  NOTE_D5, 4, NOTE_E5, 8, NOTE_CS5, -8, NOTE_B4, 16, NOTE_A4, 4, NOTE_A4, 8,
  NOTE_E5, 4, NOTE_D5, 2, NOTE_A4, 16, NOTE_B4, 16, NOTE_D5, 16, NOTE_B4, 16,

  NOTE_FS5, -8, NOTE_FS5, -8, NOTE_E5, -4, NOTE_A4, 16, NOTE_B4, 16, NOTE_D5, 16, NOTE_B4, 16, //45
  NOTE_A5, 4, NOTE_CS5, 8, NOTE_D5, -8, NOTE_CS5, 16, NOTE_B4, 8, NOTE_A4, 16, NOTE_B4, 16, NOTE_D5, 16, NOTE_B4, 16,
  NOTE_D5, 4, NOTE_E5, 8, NOTE_CS5, -8, NOTE_B4, 16, NOTE_A4, 4, NOTE_A4, 8,
  NOTE_E5, 4, NOTE_D5, 2, NOTE_A4, 16, NOTE_B4, 16, NOTE_D5, 16, NOTE_B4, 16,
  NOTE_FS5, -8, NOTE_FS5, -8, NOTE_E5, -4, NOTE_A4, 16, NOTE_B4, 16, NOTE_D5, 16, NOTE_B4, 16, //45

  NOTE_A5, 4, NOTE_CS5, 8, NOTE_D5, -8, NOTE_CS5, 16, NOTE_B4, 8, NOTE_A4, 16, NOTE_B4, 16, NOTE_D5, 16, NOTE_B4, 16,
  NOTE_D5, 4, NOTE_E5, 8, NOTE_CS5, -8, NOTE_B4, 16, NOTE_A4, 4, NOTE_A4, 8,

  NOTE_E5, 4, NOTE_D5, 2, REST, 4
};

int const swPin = 8;
int const led = 6;
int const spkr = 2;
int tempo = 114;
int buzzer = 2;
// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// there are two values per note (pitch and duration), so for each note there are four bytes
int notes = sizeof(melody) / sizeof(melody[0]) / 2;
// this calculates the duration of a whole note in ms
int wholenote = (60000 * 4) / tempo;
int divider = 0, noteDuration = 0;
int thisNote = 0;
int extend = 16;
int retract = 176;
int totalanger = 0;
int cooldown;
int swState;  //Variable used to store the state of the switch (High or Low)
int mode;  //Variable to store random mode
int ledState = LOW;
int blink;

Servo myservo;  // create servo object to control a servo

bool toggle = false;

unsigned long miltime;
long prevtog = 0;
long timestamp = 0;
long prevcalm = 0;
long prevled = 0;

void setup() {
  Serial.begin(9600);  //Turn on the serial monitor
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  pinMode(swPin, INPUT_PULLUP);  //Use the internal pull-up resistor for 2 wire switch
  pinMode(led, OUTPUT);   //LED set as output
  pinMode(spkr, OUTPUT);  //Speaker set as ouput
}

void loop() {
  swState = digitalRead(swPin); //Store the state of the switch to variable
  miltime = millis();
//Anger increases inversly to the amount of time that has passes within a 20 second timeframe since the switch was last ON.
  if (miltime < (timestamp + 20000) && swState == HIGH && miltime > timestamp) {
    cooldown = (timestamp + 20000 ) - miltime; 
    totalanger = totalanger + cooldown / 1000;
  }
//Maps blink to anger
  blink = map(totalanger, 0, 100, 2500, 2);
//Blinks LED to anger level (Anger Heartbeat)
  if(miltime - prevled >= blink){
    prevled = miltime;
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    digitalWrite(led, ledState);
    delay(100);
    digitalWrite(led, LOW);
  }
  //After 20 Seconds of inactivity, anger decreases
  if(miltime - prevcalm >= 1000 && totalanger > 0 && miltime >= timestamp + 20000){
    prevcalm = miltime;
    totalanger = totalanger - 1;
  }
  
  if (swState == HIGH){
    // remembers when the switch is hit (On)
    timestamp = miltime;
    
    // different reactions with increasing anger
    if(mode == 0){
      if(totalanger <= 20){
        mode = random(0, 3);
      }
      else if(totalanger <= 40 && totalanger > 20){
        mode = random(3, 5);
      }
      else if(totalanger < 60 && totalanger > 40){
        mode = random(5, 7);
      }
      else if(totalanger < 80 && totalanger > 60){
        mode = random(7, 9);
      }
      else if(totalanger > 80){
        mode = random(9, 11);
      }
    }
    //Updates toggle every second
    if (miltime - prevtog >= 1000 && toggle == false) {
     prevtog = miltime;
      toggle = true;
    }
  }
  
  if (swState == LOW) //Rotate servo to 180 degrees if the switch is Low
  {
    mode = 0;
    //sets mode back to 0 (status quo)
    myservo.write(retract);
    noTone(spkr);
  }
  // prints Anger
  Serial.print(" Anger: ");
  Serial.println(totalanger);
  // only triggers if anger is at 100 or more
  if (totalanger >= 100) {
    // opens lid
    myservo.write(70);
    // plays entire song
    while (thisNote < notes * 2 && totalanger >= 100) {

      // calculates the duration of each note
      divider = melody[thisNote + 1];
      if (divider > 0) {
        // regular note, just proceed
        noteDuration = (wholenote) / divider;
      } else if (divider < 0) {
        // dotted notes are represented with negative durations!!
        noteDuration = (wholenote) / abs(divider);
        noteDuration *= 1.5; // increases the duration in half for dotted notes
      }

      // we only play the note for 90% of the duration, leaving 10% as a pause
      tone(buzzer, melody[thisNote], noteDuration * 0.9);

      // Wait for the specief duration before playing the next note.
      delay(noteDuration);
      // stop the waveform generation before the next note.
      noTone(buzzer);
      thisNote = thisNote + 2;
      //Leaves While loop when song expires
      if (thisNote >= notes * 2) {
        break;
      }
    }
  }
  
// resets the music counter and anger when it hits 100
  if (thisNote >= notes * 2 && totalanger >= 100) {
    thisNote = 0;
    totalanger = 0;
  }
  
// servo responses, sets toggle to false after a successful run
  if (totalanger < 100) {
    if (toggle == true) {
      switch (mode) {
        case 1:    // Quick click
          Serial.println("Mode 1");
          myservo.write(extend);
          toggle = false;
          break;
        case 2:    // Hesitate
          Serial.println("Mode 2");
          myservo.write(70);
          delay(1000);
          myservo.write(extend);
          toggle = false;
          break;
        case 3:    // Do something new!
          Serial.println("Mode 3");
          myservo.write(70);
          delay(1000);
          myservo.write(20);
          delay(1000);
          myservo.write(extend);
          toggle = false;
          break;
          
        case 4:    // Do something new!
          Serial.println("Mode 4");
          myservo.write(30);
          delay(1000);
          myservo.write(extend);
          toggle = false;
          break;
          
        case 5:
          Serial.println("Mode 5");
          myservo.write(130);
          delay(200);
          myservo.write(2);
          delay(200);
          myservo.write(130);
          delay(200);
          myservo.write(2);
          delay(200);
          myservo.write(130);
          delay(200);
          myservo.write(2);
          delay(200);
          myservo.write(extend);
          toggle = false;
          break;
          
        case 6:
          Serial.println("Mode 6");
          delay(3000);
          myservo.write(90);
          delay(2000);
          myservo.write(60);
          delay(3000);
          myservo.write(extend);
          delay(700);
          toggle = false;
          break;
          
        case 7:
          Serial.println("Mode 7");
          myservo.write(extend);
          delay(1000);
          myservo.write(retract);
          delay(1000);
          myservo.write(100);
          delay(2000);
          toggle = false;
        break;
        
        case 8:
          Serial.println("Mode 8");
          myservo.write(30);
          delay(2000);
          myservo.write(retract);
          delay(2000);
          myservo.write(extend);
          toggle = false;
        break;
        
        case 9:
          Serial.println("Mode 9");
          myservo.write(extend);
          delay(300);
          myservo.write(50);
          delay(1000);
          myservo.write(extend);
          delay(300);
          myservo.write(50);
          delay(300);
          myservo.write(extend);
          delay(300);
          myservo.write(50);
          delay(300);
          myservo.write(extend);
          toggle = false;
        break;
        
        case 10:
          Serial.println("Mode 10");
          delay(3000);
          myservo.write(90);
          delay(2000);
          myservo.write(60);
          delay(3000);
          myservo.write(extend);
          delay(300);
          myservo.write(50);
          delay(1000);
          myservo.write(extend);
          delay(300);
          myservo.write(50);
          delay(300);
          myservo.write(extend);
          delay(300);
          myservo.write(50);
          delay(300);
          myservo.write(extend);
          toggle = false;
        break;
      }
      delay(1000); // waits for the servo to get there
    }
  }
}