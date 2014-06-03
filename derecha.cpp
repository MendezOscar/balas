#include "derecha.h"

derecha::derecha(int x, int y, SDL_Surface *screen,SDL_Surface * surface)
{
    this->x = x;
    this->y = y;
    this->surface = surface;
    this->screen = screen;
    this->borrar = false;
    this->tipo="d";
    this->morir =0;
}

void derecha::mover()
{
    x-=5;
}
derecha::~derecha()
{
    //dtor
}
