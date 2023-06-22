const int trigPin = 9;
const int echoPin = 10;
const int redled = 6;
int mtr = 11;
const int piezo = 13;
int mtrpwm;
// defines variables
long duration;
int distance;
void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
pinMode(redled, OUTPUT);
pinMode(mtr, OUTPUT);
pinMode(piezo, OUTPUT);
Serial.begin(9600); // Starts the serial communication
}
void loop() {
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.print(distance);
Serial.print(" Motor PWM: ");
  
Serial.println(mtrpwm);
mtrpwm = (255 - distance/1.6);
analogWrite(mtr, mtrpwm); 
  
tone(piezo, distance * 2);
  
  if (piezo == HIGH) {
    digitalWrite(redled, HIGH);
}
  else 
    digitalWrite(redled, LOW);
   
}