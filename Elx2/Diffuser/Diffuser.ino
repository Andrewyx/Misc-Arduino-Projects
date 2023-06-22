/*
  Code for June 2023 Sergio Maldonado, Andrew Mao, Jeanette Guo Diffuser Project
*/
  long blue = 0;
  long red = 0;
  long green = 0;
  int bluestep = 3;
  int redstep = 3;
  int greenstep = 3;
  const int bluepin = 3;
  const int redpin = 9;
  const int greenpin = 5;
  const int fanpin = 6;
  bool fanstate = LOW;
  
  unsigned long prevfantime = 0;
  unsigned long miltime = 0;
  
  
void setup() {
    Serial.begin(9600);
    pinMode(bluepin, OUTPUT);
    pinMode(redpin, OUTPUT);
    pinMode(greenpin, OUTPUT);
    pinMode(fanpin, OUTPUT);
    green = random(0 , 255);
    red = random(0 , 255);
    blue = random(0 , 255);
}

void loop() {
    miltime = millis();
    
    if(miltime - prevfantime >= 6500 && fanstate == LOW){
      fanstate = !fanstate;
      prevfantime = miltime;
    }
    else if(miltime - prevfantime >= 500 && fanstate == HIGH){
      fanstate = !fanstate;
      prevfantime = miltime;
    }
    digitalWrite(fanpin, fanstate);
   Serial.print("Blue: "); 
   Serial.print(blue);
   Serial.print(" Red: ");
   Serial.print(red);
   Serial.print(" Green: ");
   Serial.println(green);
  
  blue = blue + bluestep;
  if(blue >= 255){
    bluestep = -3;
  }
  else if(blue <= 0){
    bluestep = 3;
  }

  
  red = red + redstep;
  if(red >= 255){
    redstep = -3;
  }
  else if(red <= 0){
    redstep = 3;
  }
  

  green = green + greenstep;
  if(green >= 255){
    greenstep = -3;
  }
  else if(green <= 0){
    greenstep = 3;
  }
 
  if(green <= red && green <= blue){
    green = 0;
  }
  else if(red <= green && red <= blue){
    red = 0;
  }
  else if(blue <= green && blue <= red){
    blue = 0;
  }
  
  analogWrite(greenpin, green);
  analogWrite(redpin, red);
  analogWrite(bluepin, blue);
}
