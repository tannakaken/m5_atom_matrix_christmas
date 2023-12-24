#include "M5Atom.h"
#define WIDTH 5
int snow_flag = false;


void setup(){
    M5.begin(false, false, true); // UART, I2C, LED
}

uint32_t brown = 0x745030;

uint32_t tree_matrix[WIDTH][WIDTH] = {
  {0x000000, 0x000000, 0x00ff00, 0x000000, 0x000000},
  {0x000000, 0x00ff00, 0x00ff00, 0x00ff00, 0x000000},
  {0x00ff00, 0x00ff00, 0x00ff00, 0x00ff00, 0x00ff00},
  {0x000000, brown,    brown,    brown,    0x000000},
  {0x000000, brown,    brown,    brown,    0x000000},
};

void draw_tree() {
    for (int i = 0; i < WIDTH; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            M5.dis.drawpix(i * WIDTH + j, tree_matrix[i][j]);
        }
    }
}

int snows[WIDTH] = {WIDTH, WIDTH, WIDTH, WIDTH, WIDTH};

void draw_snows() {
    for (int i = 0; i < WIDTH; ++i) {
        int snow = snows[i];
        if (0 <= snow && snow < WIDTH) {
            M5.dis.drawpix(snow * WIDTH + i, 0xffffff);
        }
        snows[i]++;
        if (snow >= WIDTH) {
            snows[i] = -random(WIDTH * 2);
        }
     }
}

void reset_snows() {
    for (int i = 0; i < WIDTH; ++i) {
        snows[i] = WIDTH;
    }
}

unsigned long total_time;
unsigned long counter = 0;
void loop(){
    M5.update();
    unsigned long current_time = millis();
    unsigned long diff = current_time - total_time;
    counter += diff;
    if (M5.Btn.wasReleased()) {
        snow_flag = !snow_flag;
        if (!snow_flag) {
            reset_snows();
        }
    }
    while (counter >= 500) {
      if (snow_flag){
          draw_tree();
          draw_snows();
      } else {
          draw_tree();
      }
      counter -= 500;
    }
    total_time = current_time;
}
