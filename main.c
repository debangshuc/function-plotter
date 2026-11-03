#include <SDL3/SDL.h>
#include "tinyexpr.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>



#define WIDTH 1024
#define HEIGHT 768
#define GRID 0x2A2A3C


// Functions to Draw the Grid
void Draw_At_Coord(SDL_Surface *surface, SDL_Rect *rect, Uint32 color){
    
    int x_coord = WIDTH / 2 + rect->x;
    int y_coord = HEIGHT / 2 - rect->y;


    SDL_Rect mod_rect = (SDL_Rect) {x_coord, y_coord, rect->w, rect->h};
    SDL_FillSurfaceRect(surface, &mod_rect , color);
}

void DrawGrid(SDL_Surface *surface){

    SDL_Rect axis_x;
    axis_x.x = -WIDTH/2;
    axis_x.y = 0;
    axis_x.w= WIDTH;
    axis_x.h = 1.5;

    SDL_Rect axis_y;
    axis_y.x = 0;
    axis_y.y = HEIGHT/2;;
    axis_y.w= 1.5;
    axis_y.h = HEIGHT;

  
    Draw_At_Coord(surface, &axis_x, GRID);
    Draw_At_Coord(surface, &axis_y, GRID);
    
}

void Plot(SDL_Surface *surface, char *expression){
    double x;
    te_variable vars[] = {{"x",&x}};

    int err;
    te_expr *expr = te_compile(expression,vars,1,&err);
    if(expr){

    }
    else{
        fprintf(stderr,"Error encountered while evaluating Expression: %s \n",expression);
        exit(-1);
    }
}




int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Use %s expression\n",argv[0]);
    }

    char *expression = argv[1];

    // Window Creation Logic

    SDL_Window *window = SDL_CreateWindow("Plotty", WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE );
    SDL_Surface *surface = SDL_GetWindowSurface(window);

    SDL_Rect rect = (SDL_Rect){50,50,50,50};
    Uint32 color = 0xFF0000;


    // Drawing of Grid
    DrawGrid(surface);
    Plot(surface, expression);
    
     
    // Window Running Loop
    SDL_Event event;
    bool running = true;
    SDL_UpdateWindowSurface(window);
    while(running){
            while(SDL_PollEvent(&event)){
                if(event.type == SDL_EVENT_QUIT){
                    running = false;
                }
            }
            
    }
}