#include <Servo.h>

int const swPin = 8;
int const led = 6;
int const spkr = 2;
int extend = 0;
int retract = 177;
int totalanger = 0;
int cooldown;

long timestamp;
long futrtime;


Servo myservo;  // create servo object to control a servo

bool toggle = false;
unsigned long miltime;
long prevtog = 0;

int swState;  //Variable used to store the state of the switch (High or Low)
int mode;  //Variable to store random mode


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

     if(miltime < timestamp + 10000 && swState == HIGH){
      cooldown = (timestamp + 10000 ) - miltime;
      totalanger = totalanger + cooldown/1000;
      Serial.print(" Anger: ");
      Serial.print(totalanger);
     }
 
  if(swState == HIGH && mode == 0) //generate a random number
  {
    Serial.print("Switch On and mode set to: ");
    mode = random(1, 5); //increase for each addtional case ex. random 1-10 for 10 cases
  }
  if(swState == HIGH){
    timestamp = miltime;
  }
  
  if(swState == LOW) //Rotate servo to 180 degrees if the switch is Low
  {
     Serial.println(" Switch Off");
     mode = 0;
     myservo.write(retract);
     noTone(spkr);
     digitalWrite(led, LOW);
     Serial.print("toggle: ");
     Serial.print(toggle);
  }
  
    else {
  }
  
  if(miltime - prevtog >= 1000 && swState == HIGH && toggle == false){
    prevtog = miltime;
    toggle = true;
  }
  
    // do something different depending on the mode value:
  // Try to add character to your servo, beeps, chirps, flashes, movements...
  Serial.print("Anger: ");
  Serial.print(totalanger);
 if(toggle == true) {
  switch (mode) {
    case 1:    // Quick click
      Serial.println("Mode 1");
      myservo.write(extend);
      toggle = false;
      Serial.print( toggle);
      break;
    case 2:    // Hesitate
      Serial.println("Mode 2");
      myservo.write(90);
      delay(1000);
      myservo.write(extend);
      toggle = false;
      Serial.print( toggle);
      break;
    case 3:    // Do something new!
      Serial.println("Mode 3");
      myservo.write(70);
      delay(1000);
      myservo.write(20);
      delay(1000);
      myservo.write(extend);
      toggle = false;
      Serial.print( toggle);
      break;
    case 4:    // Do something new!
      Serial.println("Mode 4");
      digitalWrite(led, HIGH);
      myservo.write(30);
      delay(1000);
      myservo.write(extend);
      toggle = false;
      Serial.print( toggle);
      break;
  }
}
  delay(300); // waits for the servo to get there 
}