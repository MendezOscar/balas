#include "Enemies.h"


Enemies::Enemies()
{

}

Enemies::Enemies(int x, int y, SDL_Surface *screen,SDL_Surface * surface)
{
    this->x = x;
    this->y = y;
    this->surface = surface;
    this->screen = screen;
    this->borrar = false;
    this->tipo="n";
    this->morir =0;
}


void Enemies::dibujar()
{
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( surface , NULL, screen, &offset );

}

void Enemies::mover()
{
    this->x+=5;

}

void Enemies::logica(int clickx , int clicky)
{
    if(clickx>=x && clickx<=x+surface->w
            &&clicky >=y&& clicky <=y+surface->h)
    {
        morir++;
        if(morir==3)
            borrar = true;

    }

}
Enemies::~Enemies()
{
    //dtor
}
