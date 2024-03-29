#include "../include/grafx.h"
#include "../include/springNetwork.h"
#include "../include/parameters.h"
#include <SDL/SDL.h>
#include <math.h>
#include <stdio.h>

#define NULL (void*)0

static SDL_Surface* GS_MAIN_SURFACE = NULL;

static void plotXY(SDL_Surface *image, int x, int y, Uint32 color, int dotRadius)
{
    for(int i = -dotRadius; i <= dotRadius; i++)
        for(int j = -dotRadius; j <= dotRadius; j++)
        {
            if(x+i > 0 && x+i < WIDTH && y+j > 0 && y+j < HEIGHT)
            {
                Uint32 *pixels = (Uint32*)image->pixels;
                pixels[((y+j)*image->w)+x+i] = color;
            }
        }

    if(dotRadius == 0)
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

            updateNetwork(TIME_STEP_PER_FRAME);
            drawNetwork();

            SDL_Flip(GS_MAIN_SURFACE);
            SDL_Delay(1000/FRAME_RATE);
    } 
}

/* -----------------------------------------
 * ------------- FROM GRAFX.H --------------
 * ----------------------------------------- */
void drawPoint(double x, double y, int radius, unsigned int color)
{
    double radiusPixel = radius / CM_PER_PIXEL;
    double xPixel = x / CM_PER_PIXEL;
    double yPixel = y / CM_PER_PIXEL;

	plotXY(GS_MAIN_SURFACE, (int)round(xPixel), (int)round(yPixel), color, (int)round(radiusPixel));
}

void drawLine(double x0, double y0, double x1, double y1, unsigned int color)
{
    return;
}

