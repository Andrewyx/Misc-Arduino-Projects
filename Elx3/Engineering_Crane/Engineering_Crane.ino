//Engineering Candy Crane

#include <Servo.h>

Servo xmtr;
Servo ymtr;
Servo zmtr;

bool upretract = HIGH, lowretract = HIGH;

const int speedpin = A0;
const int forbtn = 4, backbtn = 7, leftbtn = 2, rightbtn = 8, upbtn = 10, lowbtn = 9;
const int xpin = 3, ypin = 5, zpin = 6;
const int threshold = 1000;

int speed = 0, runspeed = 90;
volatile int xdir = 0, ydir = 0, zdir = 0;
volatile bool uplastbtn = HIGH, lowlastbtn = HIGH;
volatile int upclicks = 0, lowclicks = 0;

unsigned long miltime = millis(), upbtntime = 0, lowbtntime = 0;

float duration = 0;
double starttime = micros(), endtime = 0; 

bool *pupretract = &upretract, *plowretract = &lowretract;
int *pspeed = &speed, *prunspeed = &runspeed;
float *pduration = &duration;

class path {
  
  public:

    void sethome(){
      //set current position as home
      x_sum = 0;
      y_sum = 0;
      z_sum = 0;
    }
    
    //setter functions to update current displacement
    void xupdate(int x_current, float duration){
      x_sum += (x_current * duration);
    }
    
    void yupdate(int y_current, float duration){
      y_sum += (y_current * duration);
    }
    
    void zupdate(int z_current, float duration){
      z_sum += (z_current * duration);
    }
    
    void printsum(){
      Serial.print("d: ");
      Serial.print(*pduration);
      
      Serial.print(" x:");
      Serial.print(x_sum);
      
      Serial.print(" y:");
      Serial.print(y_sum);
      
      Serial.print(" z:");
      Serial.println(z_sum);
      
    }
    
    //getter functions to return to home position
    void retraction(float duration, float starttime){
      int mode = 1;
      xmtr.write(90);
      ymtr.write(90);
      zmtr.write(90);
      
      //z retract
      if (mode == 1){
      if (z_sum < 0){
        while (z_sum < 0){
          zmtr.write(180);
          //delay for duration time *pduration
          delay(48);
          Serial.println(z_sum);
          //Add duration * max speed
          z_sum += (55*60);
        }
      }
      else if (z_sum > 0){
        while(z_sum > 0){
          zmtr.write(0);
          delay(48);
          Serial.println(z_sum);
          z_sum -= (55*60);
        }
      }
      if (-3000 < z_sum < 3000){
        z_sum = 0;
        mode = 2;
        zmtr.write(90);
      }
      }
      
      if (mode == 2){
      //x retract
      if (x_sum < 0){
        while (x_sum < 0){
          xmtr.write(180);
          delay(48);
          Serial.println(x_sum);
          x_sum += (55*60);
        }
      }
      else if (x_sum > 0){
        while(x_sum > 0){
          xmtr.write(0);
          delay(48);
          Serial.println(x_sum);
          x_sum -= (55*60);
        }
      }
      if (-3000 < x_sum < 3000){
        x_sum = 0;
        mode = 3;
        xmtr.write(90);
      }
      }
      if (mode == 3){
      //y retract
      if (y_sum < 0){
        while (y_sum < 0){
          ymtr.write(180);
          delay(48);
          Serial.println(y_sum);
          y_sum += (55*60);
        }
      }
      else if (y_sum > 0){
        while(y_sum > 0){
          ymtr.write(0);
          delay(48);
          Serial.println(y_sum);
          y_sum -= (55*60);
        }
      }
      if (-3000 < y_sum < 3000){
        y_sum = 0;
        mode = 1;
        ymtr.write(90);
      }
      }
    } 
    
    private:
      //stored position
      double x_sum, y_sum, z_sum;
    
};

path returning;

//functions to read buttons
void checkx(){
  if (digitalRead(forbtn) == LOW){
    xdir = 1;
  }
  else if (digitalRead(backbtn) == LOW){
    xdir = -1;
  }
  else {
    xdir = 0;
  }
}
void checky(){
  if (digitalRead(leftbtn) == LOW){
    ydir = 1;
  }
  else if (digitalRead(rightbtn) == LOW){
    ydir = -1;
  }
  else {
    ydir = 0;
  }  
}
void checkz(){
  if (digitalRead(upbtn) == LOW){
    zdir = 1;
  }
  else if (digitalRead(lowbtn) == LOW){
    zdir = -1;
  }
  else {
    zdir = 0;
  }
}

void setup() {
  //controller board input
  pinMode(speedpin, INPUT);
  
  pinMode(forbtn, INPUT_PULLUP);
  pinMode(backbtn, INPUT_PULLUP);
  pinMode(leftbtn, INPUT_PULLUP);
  pinMode(rightbtn, INPUT_PULLUP);
  pinMode(upbtn, INPUT_PULLUP);
  pinMode(lowbtn, INPUT_PULLUP);

  Serial.begin(9600);
  
  //motor output
  xmtr.attach(xpin);
  ymtr.attach(ypin);
  zmtr.attach(zpin);
}

void loop() {
  returning.printsum();
  miltime = millis();
  *pspeed = analogRead(speedpin);
  *pspeed = map(*pspeed, 0, 1032, 0, 50);

  //begin timing button input
  starttime = micros();
  

  *pupretract = digitalRead(upbtn);
  *plowretract = digitalRead(lowbtn);

  //edge detection for button state change
  if (*pupretract != uplastbtn){
    upclicks++;
    upbtntime = miltime;
    uplastbtn = *pupretract;
  }
  else if (*plowretract != lowlastbtn){
    lowbtntime = miltime;
    lowclicks++;
    lowlastbtn = *plowretract;
  }
  
  //three quick up presses to initaite retraction sequence
  if (upclicks == 6 && miltime - upbtntime <= threshold){
      returning.retraction(*pduration, starttime);
  }
  else if (miltime - upbtntime > threshold && upclicks != 0){
    upclicks = 0;
    }
    
  //three quick down presses to set current position as home
  if (lowclicks == 6 && miltime - lowbtntime <= threshold){
      returning.sethome();
  }
  else if (miltime - lowbtntime > threshold && lowclicks != 0){
    lowclicks = 0;
    }
    
  //check if a button is being pressed
  checkx();
  checky();
  checkz();

  //end button timing and calculate duration
  endtime = micros();
  *pduration = endtime - starttime;
  
  //drive motors
switch (xdir) {
  case 1:
    //calculate speed and run motor
    *prunspeed = 80 - speed;
    xmtr.write(*prunspeed);
    //feed current speed and previous duration into return function
    returning.xupdate(speed * -1 - 10, *pduration);
    //leave case
    break;
  case -1:
    *prunspeed = 100 + speed;
    xmtr.write(*prunspeed);
    returning.xupdate(speed + 10, *pduration);
    
    break;
  default:
    xmtr.write(90);
    
}

switch (ydir) {
  
  case 1:
    *prunspeed = 100 + speed;
    ymtr.write(*prunspeed);
    returning.yupdate(speed + 10, *pduration);
    break;
    
  case -1:
    *prunspeed = 80 - speed;
    ymtr.write(*prunspeed);
    returning.yupdate(speed * -1 - 10, *pduration);
    break;
  
  default:
    ymtr.write(90);
}

switch (zdir) {
  
  case 1:
    *prunspeed = 100 + speed;
    zmtr.write(100 + speed);
    returning.zupdate(speed + 10, *pduration);
    break;
    
  case -1:
    *prunspeed = 80 - speed;
    zmtr.write(*prunspeed);
    returning.zupdate(speed * -1 - 10, *pduration);
    break;
  
  default:
    zmtr.write(90);
  }
}