
#include "SDL.h"
#include <stdio.h>
#include "Display.h"
#include "CPU.h"

#define SCREEN_SCALE 10

int main(int argc, char* argv[]) {
    Display display;
    CPU cpu;
    SDL_Event event;
    bool running = 1;

    cpu.init();

    display.createDisplay(SCREEN_SCALE);
    cpu.getRegisters()[0xF] = 0;
    cout << (int)cpu.getRegisters()[0xF] << endl;
    display.drawSprite(cpu.get_RAM(), 5, 5 * 3, 0, 0, &cpu.getRegisters()[0xF]);
    display.drawSprite(cpu.get_RAM(), 5, 5 * 3, 15, 0, &cpu.getRegisters()[0xF]);
    cout << (int)cpu.getRegisters()[0xF] << endl;

    while (running) {
        //SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        //SDL_RenderClear(renderer);

        //display.drawPixel(64, 32, 1);

        //Poll for events
        while (SDL_PollEvent(&event)) {

            switch (event.type) {
            case SDL_QUIT:
                running = 0;
                display.closeDisplay();
                cout << "Terminated";
                break;
            default:
                break;
            }

        }
    }



    return 0;
}