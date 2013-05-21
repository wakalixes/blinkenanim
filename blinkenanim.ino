/*1) copy library to Sketchbook directory -> libraries
2) reopen Arduino IDE
3) import library


This library depends on the TI Tlc5940 library.
For installation instructions please visit

http://playground.arduino.cc/learning/TLC5940

newer version might require other and/or additional
header-files to be included.


For more information on how to create a animation
please read the comments in BlinkenWall.h

example programm

this will constantly draw the ITS logo to the wall

8<--------8<------8<------
*/

#include "tlc_config.h"
#include "Tlc5940.h"
#include "BlinkenWall.h"
#include "Animations.h"
#include <math.h>

#define PI 3.14159

/* delay 150 ms, black default background */
BlinkenWall blinkenWall(50, 0);

/* ITS - IT Syndikat */
const char col[] = {1,1,1,1,1,1,1,1};

const char row[] = {1,1,1,1,1,1,1,1,1,1,1,1};

const char pix[] = {1};

char pixframe[] = {
  0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0
};

const uint32_t color_pixframe[] = {
  0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff,
  0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff,
  0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff,
  0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff,
  0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff,
  0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff,
  0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff,
  0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff
};

const uint32_t color_pix[] = {0xffffff};

const uint32_t color_col[] = {0xff0000,0xff0000,0xff0000,0xff0000,0xff0000,0xff0000,0xff0000,0xff0000};
const uint32_t color_row[] = {0x00ff00,0x00ff00,0x00ff00,0x00ff00,0x00ff00,0x00ff00,0x00ff00,0x00ff00,0x00ff00,0x00ff00,0x00ff00,0x00ff00};

struct animation colanim = {1, 8, 1, col, color_col};
struct animation rowanim = {1, 1, 12, row, color_row};
struct animation pixanim = {1, 1, 1, pix, color_pix};

char deltaframe = 2;
char deltadelta = 2;
char freqx = 1;
char phasex = 0;
char freqy = 1;
char phasey = 0;
char rotmax = 8;
volatile char rotcnt = rotmax;
volatile char figcnt = 0;
    
void
setup()
{
    blinkenWall.setup();
}

void
loop()
{
    deltaframe+=deltadelta;
    if (deltaframe<10) deltadelta = 2;
    if (deltaframe>=10) deltadelta = 0;
    rotcnt++;
    if (rotcnt>rotmax) {
      rotcnt = 0;
      switch (figcnt) {
        case 0:
          blinkenWall.clear();
          blinkenWall.update();
          delay(500);
          figcnt = 1;
          freqx = 1; freqy = 1; phasex = 0; phasey = 0;
          rotcnt = 0; rotmax = 5;
          deltaframe = 2; deltadelta = 2;
          clearpixframe();
          break;
        case 1:
          blinkenWall.clear();
          blinkenWall.update();
          delay(500);
          figcnt = 2;
          freqx = 1; freqy = 1; phasex = 0; phasey = 1;
          rotcnt = 0; rotmax = 5;
          deltaframe = 2; deltadelta = 2;
          clearpixframe();
          break;
        case 2:
          blinkenWall.clear();
          blinkenWall.update();
          delay(500);
          figcnt = 3;
          freqx = 2; freqy = 1; phasex = 0; phasey = 0;
          rotcnt = 0; rotmax = 5;
          deltaframe = 2; deltadelta = 2;
          clearpixframe();
          break;
        case 3:
          blinkenWall.clear();
          blinkenWall.update();
          delay(500);
          figcnt = 4;
          freqx = 20; freqy = 20; phasex = 0; phasey = 0; 
          rotcnt = 1; rotmax = 4;
          deltaframe = 4; deltadelta = 2;
          clearpixframe();
          break;
        case 4:
          blinkenWall.clear();
          blinkenWall.update();
          delay(500);
          figcnt = 5;
          freqx = 20; freqy = 20; phasex = 0; phasey = 1;
          rotcnt = 1; rotmax = 4;
          deltaframe = 4; deltadelta = 2;
          clearpixframe();
          break;
        case 5:
          blinkenWall.clear();
          blinkenWall.update();
          delay(500);
          figcnt = 6;
          freqx = 40; freqy = 20; phasex = 0; phasey = 0;
          rotcnt = 1; rotmax = 4;
          deltaframe = 4; deltadelta = 2;
          clearpixframe();
          break;
        case 6:
          blinkenWall.clear();
          blinkenWall.update();
          while (1) {};
      }
    }
    for(int frame=0;frame<360;frame=frame+deltaframe) {
      int xpos = sin((double)frame*freqx/180*PI+phasex*PI/2)*4+4;
      int ypos = sin((double)frame*freqy/180*PI+phasey*PI/2)*6+6;
      struct animation pixframeanim = {1, 8, 12, pixframe, color_pixframe};
      blinkenWall.drawAnimation(&pixanim, xpos, ypos, 0, 0);
      blinkenWall.drawAnimation(&colanim, 0, ypos, 1, 0);
      blinkenWall.drawAnimation(&rowanim, xpos, 0, 2, 0);
      if (rotcnt>=2) {
        int address = xpos*12+ypos;
        if (address>95) address = 95;
        pixframe[address] = 1;
        blinkenWall.drawAnimation(&pixframeanim, 0, 0, 3, 0);
      }
      blinkenWall.update();
      blinkenWall.clear();
    }
}

void
clearpixframe() {
  for (int i=0;i<sizeof(pixframe);i++) {
    pixframe[i] = 0;  
  }  
}
