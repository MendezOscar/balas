#ifndef DERECHA_H
#define DERECHA_H
#include "Enemies.h"

class derecha : public Enemies
{
public:
    derecha(int x, int y, SDL_Surface *screen,SDL_Surface * surface);
    virtual ~derecha();
    void mover();
protected:
private:
};

#endif // DERECHA_H
