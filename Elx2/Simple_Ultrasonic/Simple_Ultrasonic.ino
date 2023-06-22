const unsigned long ult2 = 2;
const unsigned long ult10 = 10;
unsigned long ult2prev = 0;
unsigned long ult10prev = 0;

long duration;

const int trigPin = 9;
const int echoPin = 10;
const int redled = 7;
const int piezo = 6;

int mtrpwm;
int distance;
int mtr = 5;

void setup() {
  
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT); 
pinMode(redled, OUTPUT);
pinMode(mtr, OUTPUT);
pinMode(piezo, OUTPUT);
Serial.begin(9600); 
}

void loop() {
  
   unsigned long microtime = micros();
     
digitalWrite(trigPin, LOW);
 if (microtime - ult2prev >= ult2) {
   digitalWrite(trigPin, HIGH);
    ult2prev = microtime;
}

  if (microtime - ult10prev >= ult10) {
    digitalWrite(trigPin, LOW);
    ult10prev = microtime;
}

duration = pulseIn(echoPin, HIGH);

distance= duration*0.034/2;
mtrpwm = (distance/);

Serial.print("Distance: ");
Serial.print(distance);
Serial.print(" Motor PWM: ");
Serial.print(mtrpwm);

analogWrite(mtr, 255 - mtrpwm); 

tone(piezo, distance * 2);  

if (distance <= 10){
 	 digitalWrite(redled, HIGH);
  }
  else 
    digitalWrite(redled, LOW);
}