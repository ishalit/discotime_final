/* Ilan
 * Cecil
 * George
 * Soph
 * cs
 * 5/15/18
 */

/* main program omgggg */

#include "matrix.h"
#include "RGB.h"
#include <stdio.h>


int serialvalue; // value for serial 
const int potPin = A1; //sets potentiometer to read from port A1
int val; // value grabbed by poteniometer reading
int started; //if serial begins reading from max

/* george variables lol */
double tempo=1000;
double dlay = tempo/13;

/* vars for bars */
int rand1;
int rand2;
int rand3;
int rand4;
int count;

/* vars for cool */
int bright0 = 50;
int bright1 = 40;
int bright2 = 30;
int bright3 = 20;
int bright4 = 10;
int bright5 = 8;
int bright6 = 5;
int bright7 = 1;
//int count = 0;

/* vars for weird square thing */

uint16_t color;
uint16_t x;
uint16_t y;
uint16_t w;
uint16_t h;

void setup() {
  /* begins potentiometer reading*/
  pinMode(potPin, INPUT);

  //Serial.print(val);

  randomSeed(analogRead(0));

  /* intialize matrix */
  matrix.begin();
  matrix.setBrightness(40);
  matrix.setTextWrap(false);
  matrix.fillScreen(0);
  matrix.show();

  /* begin serial reading */
  Serial.begin(9600);
  
  
}

void loop() {
  
  /* store value from potentiometer */
  val = analogRead(potPin);


  if(Serial.available()) // check to see if there's serial data in the buffer
  {
    serialvalue = Serial.read(); // read a byte of serial data
    started = 1; // set the started flag to on
  }

  //Serial.print(serialvalue);

  /* heartbeat */
  if(val>800 && val<1023) {
    
    int h=9;
    int s = serialvalue;

    //set background color
    matrix.fillScreen(231);

    //draw lines
    matrix.drawLine(0, 9, 4, 9, matrix.Color(255, 0, 0));
    matrix.drawLine(4, 9, 6, h-s, matrix.Color(255, 0, 0));
    matrix.drawLine(6, h-s, 8, h+(2*s/3), matrix.Color(255, 0, 0));
    matrix.drawLine(8, h+(2*s/3), 10, h-(s/3), matrix.Color(255, 0, 0));
    matrix.drawLine(10, h-(s/3), 12, 9, matrix.Color(255, 0, 0));
    matrix.drawLine(12, 9, 15, 9, matrix.Color(255, 0, 0));

    //send data to matrix
    matrix.show();
    
  }


  /* squares */

  if(val >600 && val < 800) {

    //initialize variables
    x = 0;
    y = 0;
    h = serialvalue;
    w = serialvalue;
  
    /* if greater than peak, change color */
    if(serialvalue > 10) {
      randColor();
      //countervalue++;
    }

    //fill matrix w new values
    matrix.fillRect(x, y, w, h, color);
    matrix.show(); //send data to matrix

    
  }
  

  /*random circles */
  if(val>300 && val<600) { 
     
    matrix.fillScreen(0);

    //initialize variables
    int rndm1 = (rand() % 16);
    int rndm2 = (rand() % 16);
    int color1 = (rand() % 255);
    int color2 = (rand() % 255);
    int color3 = (rand() % 255);
    int x = (rand() % 16);
    int y = (rand() % 16);

    //if sound goes over peak    
    if(serialvalue > 4) {

      //trigger random circle algorithm
      matrix.setBrightness(bright0);
      SnowFlake0(x, y, matrix.Color(color1, color2, color3));
      matrix.show();
      matrix.setBrightness(bright1);
      SnowFlake1(x, y, matrix.Color(color1, color2, color3));
      matrix.show();
      matrix.setBrightness(bright2);
      SnowFlake2(x, y, matrix.Color(color1, color2, color3));
      matrix.show();
      matrix.setBrightness(bright3);
      SnowFlake3(x, y, matrix.Color(color1, color2, color3));
      matrix.show();
      matrix.setBrightness(bright4);
      SnowFlake4(x, y, matrix.Color(color1, color2, color3));
      matrix.show();
      matrix.setBrightness(bright5);
      SnowFlake5(x, y, matrix.Color(color1, color2, color3));
      matrix.show();
      matrix.setBrightness(bright6);
      SnowFlake6(x, y, matrix.Color(color1, color2, color3));
      matrix.show();
      matrix.setBrightness(bright7);
      SnowFlake7(x, y, matrix.Color(color1, color2, color3));
      matrix.show(); // This sends the updated pixel colors to the hardware.
      delay(100);

      matrix.fillScreen(0);
      serialvalue = 0;
    }

    else
    {
      if(count>10)
      {   
        matrix.fillScreen(0);
        matrix.setBrightness(rand() % 50);
        rando(matrix.Color(rand() % 255, rand() % 255, rand() % 255));
        matrix.show();
        delay(20);
        count = 0;
      }
      else
        {count++;}
    }
  }
  
  /* Bars */
  if(val>0 && val<300) {
    
    rand1 = (rand() % 4);
    rand2 = rand1;
    
    while(rand2 == rand1)
    {
      rand2 = (rand() % 4);
    }
    rand3 = rand2;
    
    while(rand3 == rand2 || rand3 == rand1)
    {
      rand3 = (rand() % 4);
    }
    rand4 = rand3;
    
    while(rand4==rand3||rand4==rand2||rand4==rand1)
    {
      rand4 = (rand() % 4);
    }
  
    rand1++;
    rand2++;
    rand3++;
    rand4++;
  
    rand1 = serialvalue/rand1;
    rand2 = serialvalue/rand2;
    rand3 = serialvalue/rand3;
    rand4 = serialvalue/rand4;
  
    if(count>5)
    {
      Bar1();
      Bar2();
      Bar3();
      Bar4();
      matrix.show(); // This sends the updated pixel colors to the hardware.
      delay(100);

      count = 0;
      //matrix.fillScreen(matrix.Color(255, 255, 255));
      matrix.fillScreen(0);
    }
    else
    {
      count++;
    }
    
  }
  
}

/* functions for random circles */
void rando(uint32_t c)
{
  matrix.drawPixel((rand() % 16), (rand() % 16), c);
}

void SnowFlake0(int x, int y, uint32_t c){
  matrix.fillCircle(x, y, 0, c); // x0, y0, radius, color
}

void SnowFlake1(int x, int y, uint32_t c){
  matrix.fillCircle(x, y, 1, c); // x0, y0, radius, color
}

void SnowFlake2(int x, int y, uint32_t c){
  matrix.fillCircle(x, y, 2, c); // x0, y0, radius, color
}

void SnowFlake3(int x, int y, uint32_t c){
  matrix.fillCircle(x, y, 3, c); // x0, y0, radius, color
}

void SnowFlake4(int x, int y, uint32_t c){
  matrix.fillCircle(x, y, 4, c); // x0, y0, radius, color
}

void SnowFlake5(int x, int y, uint32_t c){
  matrix.fillCircle(x, y, 5, c); // x0, y0, radius, color
}

void SnowFlake6(int x, int y, uint32_t c){
  matrix.fillCircle(x, y, 6, c); // x0, y0, radius, color
}

void SnowFlake7(int x, int y, uint32_t c){
  matrix.fillCircle(x, y, 7, c); // x0, y0, radius, color
}


/* functions for BARS */
void Bar1(){
  int i = 0;
  int color1 = 250;
  int color2 = 100;
  int color3 = 0;
   
  while(i<=rand1)
  {
    matrix.fillRect(i, 0, 1, 4, matrix.Color(color1, color2, color3)); // x0, y0, radius, color
    i++;
    
    if(i%2 == 0)
    {
      if(color2>249)
        {color2 = 250;
        color1 = color1 - 50;
        }
      else   
        color2 = color2 + 50;
    }    
  }
}

void Bar2(){
  int i = 0;
  int color1 = 250;
  int color2 = 100;
  int color3 = 0;

  while(i<=rand2)
  {    
    matrix.fillRect(i, 4, 1, 4, matrix.Color(color1, color2, color3));
    i++;
    
    if(i%2 == 0)
    {
      if(color2>249)
        {color2 = 250;
        color1 = color1 - 50;
        }
      else   
        color2 = color2 + 50;
    }
  }
}

void Bar3(){
  int i = 0;
  int color1 = 250;
  int color2 = 100;
  int color3 = 0; 
  
  while(i<=rand3)
  {   
    matrix.fillRect(i, 8, 1, 4, matrix.Color(color1, color2, color3));
    i++;
    
    if(i%2 == 0)
    {
      if(color2>249)
        {color2 = 250;
        color1 = color1 - 50;
        }
      else   
        color2 = color2 + 50;
    }    
  }
}

void Bar4(){
  int i = 0;
  int color1 = 250;
  int color2 = 100;
  int color3 = 0;
  
  while(i<=rand4)
  {
    
    matrix.fillRect(i, 12, 1, 4, matrix.Color(color1, color2, color3));
    i++;
    
    if(i%2 == 0)
    {
      if(color2>249){
        color2 = 250;
        color1 = color1 - 50;
      }
      else    
        color2 = color2 + 50;
    }   
  } 
}

/* function for weird square */
void randColor() {
   color = matrix.Color(rand() % 255, rand() % 255, rand() % 255);
}
