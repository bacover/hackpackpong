#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include "RGB.h"

#define PIN 1

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);


void setup() {
  matrix.begin();
  matrix.setBrightness(40);
  matrix.setTextColor( matrix.Color(white.r, white.g, white.b) );
  matrix.setTextWrap(false);

}

  int gameover;
  int leftpaddle = 0;
  int rightpaddle = 5;
  int lefthp = 1; //0,1,2
  int righthp = 1; //0,1,2
  int ballx = 3;
  int bally = 3;
  int velocityx = 1;
  int velocityy = 1;
  int matrix2[8][8] = {  
   {0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0}
  };
    int matrix3[8][8] = {  
   {0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0}
  };

void loop() {
  colorWipe(off, 15);
  randomSeed(analogRead(0));
  

  leftpaddle = 0;
  rightpaddle = 5;
  lefthp = 1; //0,1,2
  righthp = 1; //0,1,2
  ballx = 3;
  bally = 3;
  velocityx = 1;
  velocityy = 1;
      for(int row = 0; row < 8; row++) {
      for(int column = 0; column < 8; column++) {
       matrix2[row][column] = 0;
     }
    }

  gameover = 0; 
   
  while (gameover == 0)
  {
    matrix2[0][leftpaddle] = 1;
    matrix2[0][leftpaddle+1] = 1;
    matrix2[0][leftpaddle+2] = 1;
    matrix2[7][rightpaddle] = 1;
    matrix2[7][rightpaddle+1] = 1;
    matrix2[7][rightpaddle+2] = 1;
    matrix2[ballx][bally] = 1;

    for(int row = 0; row < 8; row++) {
      for(int column = 0; column < 8; column++) {
       if(matrix2[row][column] == 1) {
         fadePixel(column, row, off, red, 1, 0);
       }
       if ((matrix3[row][column]) == 1 && (matrix2[row][column] == 0))
       {
          fadePixel(column, row, red, off, 1, 0);
       }
     }
    }
    
    //adjust values
    ballx = ballx + velocityx;
    bally = bally + velocityy;
    
    if (bally > (leftpaddle + lefthp))
    {
      leftpaddle++;
      if (leftpaddle > 5)
      {
        leftpaddle = 5;
      }
    }
    if (bally < (leftpaddle + lefthp))
    {
      leftpaddle--;
      if (leftpaddle < 0)
      {
        leftpaddle = 0;
      }
    }
    if (bally > (rightpaddle + righthp))
    {
      rightpaddle++;
      if (rightpaddle > 5)
      {
        rightpaddle = 5;
      }
    }
    if (bally < (rightpaddle + righthp))
    {
      rightpaddle--;
      if (rightpaddle < 0)
      {
        rightpaddle = 0;
      }
    }
    
    //check for ball bounce
    if (bally == 7)
    {
      velocityy = -1;
    }   
    if (bally == 0)
    {
      velocityy = 1;
    }
    
    if ((ballx == 0) && ((bally-leftpaddle < 3) && (bally-leftpaddle > -1)))
    {
      //hit
      //update velocity
      velocityy = lefthp - 1;
      velocityx = 1;
      //update hit position
      lefthp = random(0,3);
    }
    if ((ballx == 7) && ((bally-rightpaddle < 3) && (bally-rightpaddle > -1)))
    {
      //hit
      //update velocity
      velocityy = righthp - 1;
      velocityx = -1;
      //update hit position
      righthp = random(0,3);
    }
    
    if ((ballx == 0) && ((bally-leftpaddle > 2) || (bally-leftpaddle < 0)))
    {
      //fail
      gameover = 1;
    }
    if ((ballx == 7) && ((bally-rightpaddle > 2) || (bally-rightpaddle < 0)))
    {
      //fail
      gameover = 1;
    }
    
    

    delay(10);
    
    for(int row = 0; row < 8; row++) {
      for(int column = 0; column < 8; column++) {
        matrix3[row][column] = matrix2[row][column];
       matrix2[row][column] = 0;
     }
    }

    
  }
  

  //fix seed
  //fix crash
  
  
  
}

// Fill the dots one after the other with a color
void colorWipe(RGB color, uint8_t wait) {
  for(uint16_t row=0; row < 8; row++) {
    for(uint16_t column=0; column < 8; column++) {
      matrix.drawPixel(column, row, matrix.Color(color.r, color.g, color.b));
      matrix.show();
      delay(wait);
    }
  }
}

// Fade pixel (x, y) from startColor to endColor
void fadePixel(int x, int y, RGB startColor, RGB endColor, int steps, int wait) {
  for(int i = 0; i <= steps; i++) 
  {
     int newR = startColor.r + (endColor.r - startColor.r) * i / steps;
     int newG = startColor.g + (endColor.g - startColor.g) * i / steps;
     int newB = startColor.b + (endColor.b - startColor.b) * i / steps;
     
     matrix.drawPixel(x, y, matrix.Color(newR, newG, newB));
     matrix.show();
     delay(wait);
  }
}

