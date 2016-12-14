#ifndef UTIL
#define UTIL

void setRect(SDL_Rect* rect,int x,int y,int w,int h)
{
    rect->x=x;
    rect->y=y;
    rect->w=w;
    rect->h=h;
}

int render_image(int srcx,int srcy,int destx,int desty,int w,int h,SDL_Texture* base_texture,SDL_Renderer* renderer)
{
    SDL_Rect srcrect,destrect;

    setRect(&destrect,destx,desty,w,h);
    setRect(&srcrect,srcx,srcy,w,h);

    SDL_RenderCopy(renderer,base_texture,&srcrect,&destrect);
}
#endif
