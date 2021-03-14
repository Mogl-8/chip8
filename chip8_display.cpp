
#include "SDL.h"
#include <stdio.h>
#include "Display.h"
#include "CPU.h"

#define SCREEN_SCALE 20

int main(int argc, char* argv[]) {
    Display display;
    CPU cpu;
    cpu.init();

    display.initDisplay(SCREEN_SCALE);
    display.drawPixel(64, 32, 1);
    display.drawSprite(cpu.get_RAM(), 5, 0, 5,6);
    

    return 0;
}