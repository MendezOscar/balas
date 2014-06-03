#include "arriba.h"

arriba::arriba(int x, int y, SDL_Surface *screen,SDL_Surface * surface)
{
    this->x = x;
    this->y = y;
    this->surface = surface;
    this->screen = screen;
// TODO (mendez#1#):
    this->borrar = false;
    this->tipo="ar";
    this->morir =0;
}

void arriba::mover()
{
    y+=5;
}

arriba::~arriba()
{
    //dtor
}
