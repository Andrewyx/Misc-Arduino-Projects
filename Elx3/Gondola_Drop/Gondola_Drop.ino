#include <Servo.h>

Servo wheel;
Servo dropper;

int drops = 0, wheeldir = 180, lightlvl;
bool dropstate = LOW, backupdet = false;
volatile bool mode = false;
unsigned long miltime, prevmil = 0, backupmil = 0, coolprev = 0;
const int droptime = 295, threshold = 500, cooldown = 3000;
const int irpin = A0, contactpin = 9, onbtn = 2;

void setup() {
  
    Serial.begin(9600);
    wheel.attach(3);
    dropper.attach(5);
    pinMode(contactpin, INPUT_PULLUP);
    pinMode(onbtn, INPUT);
    pinMode(irpin, INPUT);
    attachInterrupt(digitalPinToInterrupt(onbtn), btnpressed, RISING);
    
}


void dropcoin() {
  while (true){
    dropper.write(180);
    wheel.write(wheeldir);
    miltime = millis();
    Serial.println(miltime);
    if (miltime - prevmil > droptime){
      prevmil = miltime;
      break;
    }    
  }
  prevmil = miltime;
}


void btnpressed(){
  mode = !mode;
  backupmil = miltime;
}

void backup(){
  if (miltime - backupmil >= 10000){
    backupdet = true;
    backupmil = miltime;
  }
}

void loop() {
  miltime = millis();

  
  if (miltime - coolprev >= cooldown){
      dropstate = digitalRead(contactpin);
      lightlvl = analogRead(irpin);
    }
  else{
    dropstate = HIGH;
    lightlvl = 0;
    backupdet = false;
  }
  
  if (drops < 4 && mode == true){
    
    backup();
    
    if (dropstate == LOW && backupdet == true){
      wheeldir = 90;
      prevmil = miltime;
      dropcoin();
      drops++;
      dropstate = !dropstate;
      wheeldir = 180;
      backupmil = miltime;
      backupdet = false;
      coolprev = miltime;
    }
    else if (lightlvl > threshold){
      wheeldir = 180;
      prevmil = miltime;
      dropcoin();
      drops++;
      dropstate = !dropstate;
      backupmil = miltime;
      backupdet = false;
      coolprev = miltime;
    }
    
    else if (dropstate == HIGH && lightlvl <= threshold){
      Serial.println(" No Contact");
      wheel.write(wheeldir);
      dropper.write(90);
    }
  }
  
  else if (drops >= 4 || mode == false){
    wheel.write(90);
    dropper.write(90);
    Serial.print(mode);
    Serial.println(" stopped");
  }
}