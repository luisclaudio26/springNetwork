#include "../include/grafx.h"
#include "../include/springNetwork.h"
#include <SDL/SDL.h>
#include <math.h>
#include <stdio.h>

#define NULL (void*)0
#define YELLOW 0xFFFF00

#define WIDTH 640
#define HEIGHT 480


static SDL_Surface* GS_MAIN_SURFACE = NULL;

static void plotXY(SDL_Surface *image, int x, int y, Uint32 color, int dotSize)
{
    for(int i = -dotSize; i <= dotSize; i++)
        for(int j = -dotSize; j <= dotSize; j++)
        {
            if(x+i > 0 && x+i < WIDTH && y+j > 0 && y+j < HEIGHT)
            {
                Uint32 *pixels = (Uint32*)image->pixels;
                pixels[((y+j)*image->w)+x+i] = color;
            }
        }

    if(dotSize == 0)
    {
        if(x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
        {
            Uint32 *pixels = (Uint32*)image->pixels;
            pixels[(y*image->w)+x] = color;
        }
    }
}

void initialize()
{
	// initialize SDL 
    SDL_Init(SDL_INIT_VIDEO); 

    // set the title bar 
    SDL_WM_SetCaption("SDL Test", "SDL Test"); 

    // create window 
    GS_MAIN_SURFACE = SDL_SetVideoMode(WIDTH, HEIGHT, 32,
                                       SDL_HWSURFACE|SDL_DOUBLEBUF);

    initializeNetwork();
}

void drop()
{
    // cleanup SDL
    SDL_Quit();
    destroyNetwork();

    printf("Dropped stuff\n");
}

void simulate()
{ 
    SDL_Event event; 
    int gameover = 0; 

    /* message pump */ 
    while (!gameover) 
    { 
            /* look for an event */ 
            if (SDL_PollEvent(&event)) 
            { 
                    /* an event was found */ 
                    switch (event.type) 
                    { 
                            /* close button clicked */ 
                            case SDL_QUIT: 
                                    gameover = 1; 
                                    break; 

                            /* handle the keyboard */ 
                            case SDL_KEYDOWN: 
                                    switch (event.key.keysym.sym) 
                                    { 
                                            case SDLK_ESCAPE:
                                                    gameover = 1; 
                                                    break; 
                                    } 
                                    break; 
                    } 
            } 
    
            /* update the screen */
            SDL_FillRect(GS_MAIN_SURFACE, 0, SDL_MapRGB(GS_MAIN_SURFACE->format, 0, 0, 0)); //Clean screen

            updateNetwork(0.015);
            drawNetwork();

            SDL_Flip(GS_MAIN_SURFACE);
            SDL_Delay(15);
    } 
}

/* -----------------------------------------
 * ------------- FROM GRAFX.H --------------
 * ----------------------------------------- */
void drawPoint(double x, double y, int radius)
{
	plotXY(GS_MAIN_SURFACE, (int)round(x), (int)round(y), YELLOW, 0);
}

void drawLine(double x1, double y1, double x2, double y2)
{
	return;	
}

