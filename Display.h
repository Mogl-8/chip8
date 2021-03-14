/*
notas: tanto colors como rpixel se crearon como atributos
de display para evitar crear nuevos casa llamada a 
drawPixel();

*/

#include "SDL.h"
#include <cstdio>
#include <iostream>
#include <vector>
#include <stdlib.h>

#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32

using namespace std;
class Display
{
private:
    SDL_Window* window;
    SDL_Event event;

    SDL_Renderer* renderer;
    SDL_Texture* texture;

    int total_screen_width;
    int total_screen_height;
    //Local screen scale variable
    int scr_scl; 

//------------------------- COLOR ------------------------------

    // Rectangle representing a scaled pixel 
    SDL_Rect rpixel;
    /*Color management array; when drawing a pixel it
    xor's the new sprite to the existing ones*/
    bool screen_color[SCREEN_WIDTH][SCREEN_HEIGHT] = { {0} };

public:
    void closeDisplay(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* texture) {
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyTexture(texture);
        SDL_Quit();
    }
    int createDisplay(int SCREEN_SCALE) {

 //---------------------------   SETUP VARS   ---------------------------------------
       
        bool running = 1;
        total_screen_width = 64 * SCREEN_SCALE;
        total_screen_height = 32 * SCREEN_SCALE;
        scr_scl = SCREEN_SCALE;
        rpixel.w = rpixel.h = scr_scl;

//---------------------------- Initialize SDL2 --------------------------------------
        
        //SDL_Init(SDL_INIT_VIDEO); goes to main             

        // Create an application window with the following settings:
        window = SDL_CreateWindow(
            "CHIP-8 BY ZACILE",                     // window title
            SDL_WINDOWPOS_UNDEFINED,                // initial x position
            SDL_WINDOWPOS_UNDEFINED,                // initial y position
            total_screen_width,                      // width, in pixels
            total_screen_height,                      // height, in pixels
            SDL_WINDOW_OPENGL                       // flags 
        );

        // Check that the window was successfully created
        if (window == NULL) {
            // In the case that the window could not be made...
            printf("Could not create window: %s\n", SDL_GetError());
            return 1;
        }

        renderer = SDL_CreateRenderer
        (
            window,
            -1,
            SDL_RENDERER_ACCELERATED
        );

        texture = SDL_CreateTexture
        (
            renderer,
            SDL_PIXELFORMAT_RGB24,
            SDL_TEXTUREACCESS_STREAMING,
            total_screen_width, total_screen_height
        );
        
       // drawPixel(64, 32, 1);

//------------------------ DISPLAY LOOP ------------------------------------

        while (running) {
            //SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
            //SDL_RenderClear(renderer);

            

            //Poll for events
            while (SDL_PollEvent(&event)) {

                switch (event.type) {
                case SDL_QUIT:
                    running = 0;
                    break;
                default:
                    break;
                }

            }
        }

        SDL_Quit();
        return 0;
    }

    int drawPixel(int rx, int ry, bool bw) { //dray pixel in a relative (x,y) position

        // Clear winow
        //SDL_RenderClear(renderer);

        if (rx > SCREEN_WIDTH-1) rx = 0;
        else if (rx < 0) rx = SCREEN_WIDTH-1;
        
        if (ry > SCREEN_HEIGHT-1) ry = 0;
        else if (ry < 0) ry = SCREEN_HEIGHT - 1;

        rpixel.x = rx*scr_scl;
        rpixel.y = ry*scr_scl;
        
        switch (bw ^ screen_color[rx][ry]) {
        case 1:SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            break;
        case 0:SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            break;
        default: cout <<"yo wtf you're boolean :v";
        }
        
        // Render rect
        SDL_RenderFillRect(renderer, &rpixel);

        // Render the rect to the screen
        SDL_RenderPresent(renderer);

        return 1;
    }
    void drawSprite(uint8_t * RAM, uint8_t nb, uint16_t I, int x, int y) {
        uint8_t temp;
        for (int i=0; i <(int)nb;i++)
            for (int j=0;j<8;j++){
                temp = RAM[i+I];
                temp = temp >> 1;
                temp = temp && 1;
                if (temp) drawPixel(x + j, y + i, 1);
                else drawPixel(x + j, y + i, 1);
            }
                

    }


};
