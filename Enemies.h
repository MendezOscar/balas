#ifndef ENEMIES_H
#define ENEMIES_H
#include <SDL/SDL.h>
#include <iostream>

using namespace std;
class Enemies
{
public:
    SDL_Surface * surface ;
    int x;
    int y;
    int morir;
    string tipo;
    SDL_Surface * screen;
    bool borrar;
    Enemies(int x, int y, SDL_Surface *screen,SDL_Surface * surface);
    Enemies();
    void dibujar();
    virtual void mover();
    void logica(int clickx, int clicky);

    virtual ~Enemies();
protected:
private:
};

#endif // ENEMIES_H
