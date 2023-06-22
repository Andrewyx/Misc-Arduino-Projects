#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int swPin = 8;  // analog pin used to connect the potentiometer
int swState;  //Variable used to store the state of the switch (High or Low)
int mood = 0;

void setup() {
Serial.begin(9600);  //Turn on the serial monitor

myservo.attach(9);  // attaches the servo on pin 9 to the servo object
pinMode(swPin, INPUT_PULLUP);  //Use the internal pull-up resistor (because Looney didn't add one :())
}

void loop() {
  swState = digitalRead(swPin); //Store the state of the switch to variable
  Serial.print(swState );  //Use serial monitor to display the state of the switch
  Serial.println(mood);

  if(swState == HIGH) //Rotate servo to 0 degrees if the switch is High
  {
    myservo.write(1);
  }
  
  if(swState == LOW) //Rotate servo to 180 degrees if the switch is Low
  {
      myservo.write(178);
  }
  
  else
  {
  }
  /*
  if(mood == 0 && swState == HIGH){
    mood++;
  }
    switch(mood){
      case 1:
     
      
    
      break;
    
      case 2:
      
      
     
      break;
      
      default:
      
      break;
   }
   */
  delay(15); // waits for the servo to get there 
}