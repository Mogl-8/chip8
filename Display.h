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

    //Aux var
    int i, j;

public:
    void closeDisplay() {
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyTexture(texture);
        SDL_Quit();
    }
    int createDisplay(int SCREEN_SCALE) {

 //---------------------------   SETUP VARS   ---------------------------------------
       
        total_screen_width = 64 * SCREEN_SCALE;
        total_screen_height = 32 * SCREEN_SCALE;
        scr_scl = SCREEN_SCALE;
        rpixel.w = rpixel.h = scr_scl;

//---------------------------- Initialize SDL2 --------------------------------------
       
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
        return 0;
    }

    int drawPixel(int rx, int ry, bool bw, uint8_t* vf) { //dray pixel in a relative (x,y) position

        // Clear winow
        //SDL_RenderClear(renderer);

        if (rx > SCREEN_WIDTH - 1) rx = rx - SCREEN_WIDTH;
        else if (rx < 0) rx = SCREEN_WIDTH + rx;
        

        if (ry > SCREEN_HEIGHT - 1) ry = ry - SCREEN_HEIGHT;
        else if (ry < 0) ry = SCREEN_HEIGHT + ry;

        rpixel.x = rx*scr_scl;
        rpixel.y = ry*scr_scl;


        
        switch (bw ^ screen_color[rx][ry]) {
        case 1: SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                screen_color[rx][ry] = 1;
            break;
        case 0: SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            if (screen_color[rx][ry] & bw) *vf = 1;
            screen_color[rx][ry] = 0;
            //verify collition
            
            break;
        default: cout <<"yo wtf you're boolean :v";

        }
        
        // Render rect
        SDL_RenderFillRect(renderer, &rpixel);

        // Render the rect to the screen
        SDL_RenderPresent(renderer);

        return 1;
    }


    void drawSprite(uint8_t * RAM, uint8_t nb, uint16_t I,  int x, int y, uint8_t * vf) {//uint8_t* v,
        /*Declare aux bytes ram_cpy to store the
        current byte in the loop and lsb (least 
        significant bit) to store the pixel to be 
        drawn.*/
        uint8_t ram_cpy,lsb;

        for (i=0; i <(int)nb;i++){
            ram_cpy = RAM[i+I];
            for (j = 0; j < 8; j++) {
                lsb = ram_cpy & 1;
                if (lsb) drawPixel(x + 7 - j, y + i, 1,vf);
                else drawPixel(x + 7 - j, y + i, 0,vf);
                ram_cpy = ram_cpy >> 1;
                //cout << (int)lsb << " - " << endl; //check printed bit val
            }
        }
             
    }


};
