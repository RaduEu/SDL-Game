#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include<stdio.h>
#include"include/game.h"
struct color
{
    char r;
    char g;
    char b;
};

const int SCREEN_WIDTH=640,SCREEN_HEIGHT=480;

const char* GAME_TITLE="PuppetGAME",*GAME_ICON_PATH="images/untitled.bmp",*MAIN_CHARACTER="images/mainchar.bmp",*BACKGROUND_IMAGE_PATH="images/untitled.bmp";
const char* FONT="PlsNo.ttf";

int quit;
struct color COLOR_TO_IGNORE;

SDL_Event event;
TTF_Font* font;

int xpos=0,ypos=0,speed=1;
int movingx=0,movingy=0;

SDL_Window* main_window;//our window
SDL_Renderer *renderer;//our renderer

void graphics()
{

}

int move(struct game_object* go,int right, int up)
{
    go->x_pos+=right*speed;
    go->y_pos-=up*speed;
}

int render_image(int srcx,int srcy,int destx,int desty,int w,int h,SDL_Texture* base_texture)
{
    SDL_Rect srcrect,destrect;

    setRect(&destrect,destx,desty,w,h);
    setRect(&srcrect,srcx,srcy,w,h);

    SDL_RenderCopy(renderer,base_texture,&srcrect,&destrect);
}

int set_go(game_object* to_set, int x, int y, struct collider* collider, struct sprite* sprite)
{
    to_set->x_pos=x;
    to_set->y_pos=y;
    to_set->collider=collider;
    to_set->sprite=sprite;
}

int render_image(int srcx,int srcy,int destx,int desty,int w,int h,char* name,int ignoreColor=0)
{
    SDL_Surface* surface=SDL_LoadBMP(name);
    if(ignoreColor) SDL_SetColorKey(surface,SDL_TRUE,SDL_MapRGB(surface->format,COLOR_TO_IGNORE.r,COLOR_TO_IGNORE.g,COLOR_TO_IGNORE.b));
    SDL_Texture* texture=SDL_CreateTextureFromSurface(renderer,surface);
    render_image(srcx,srcy,destx,desty,w,h,texture);
}

int setup()
{
    COLOR_TO_IGNORE.r=200;
    COLOR_TO_IGNORE.g=158;
    COLOR_TO_IGNORE.b=100;

    if(SDL_Init(SDL_INIT_EVERYTHING)) return 0;
    if(TTF_Init()) return 0;

    font=TTF_OpenFont(FONT,28);

    if(font==NULL) return 0;

    main_window=SDL_CreateWindow(GAME_TITLE,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_HIDDEN);
    if(main_window==NULL) return 0;

    SDL_Surface* icon=SDL_LoadBMP(GAME_ICON_PATH);
    if(icon==NULL) return 0;

    SDL_SetWindowIcon(main_window,icon);

    SDL_Surface* window_surface=SDL_GetWindowSurface(main_window);

    if(window_surface==NULL) return 0;

    SDL_ShowWindow(main_window);

    SDL_Color white;
    white.r=255;
    white.g=255;
    white.b=255;

    SDL_Surface* text=TTF_RenderText_Solid(font, GAME_TITLE, white);

    if(text==NULL) return 0;

    SDL_BlitSurface(text,NULL,SDL_GetWindowSurface(main_window),NULL);

    renderer=SDL_CreateRenderer(main_window,-1,0);
    if(renderer==NULL) return 0;
    //SDL_RenderClear(renderer);
    //render_image(0,0,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,(char*)BACKGROUND_IMAGE_PATH);

    //SDL_RenderPresent(renderer);

    return 1;
}

int render_go(struct game_object* go)
{
    sprite* to_render=go->sprite;
    render_image(to_render->x_pos,to_render->y_pos,go->x_pos,go->y_pos,to_render->width,to_render->height,to_render->texture);
}

int main()
{

    if(!setup())
    {
        printf("%s",SDL_GetError());
        SDL_Delay(1000);
        return 1;
    }

    SDL_Delay(1000);

    game_object main_char;
    struct sprite main_char_sprite;

    SDL_Texture *texture=SDL_CreateTextureFromSurface(renderer,SDL_LoadBMP(MAIN_CHARACTER));

    set_sprite(&main_char_sprite, texture, 100, 100, 100, 100);

    set_go(&main_char, 100, 100, NULL, &main_char_sprite);

    while(!quit)
    {
        while(SDL_PollEvent(&event))
        {

            switch(event.type)
            {
            case SDL_QUIT:
                quit=1;

            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                case SDLK_d:
                    movingx=1;
                    movingy=0;
                    break;
                case SDLK_a:
                    movingx=-1;
                    movingy=0;
                    break;
                case SDLK_w:
                    movingy=1;
                    movingx=0;
                    break;
                case SDLK_s:
                    movingy=-1;
                    movingx=0;
                    break;
                }
            }
        }

        move(&main_char,movingx,movingy);
        SDL_RenderClear(renderer);
        render_go(&main_char);
        SDL_RenderPresent(renderer);
        SDL_Delay(1);
    }

    SDL_Quit();

    return 0;
}
