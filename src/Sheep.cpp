#include "../include/Sheep.h"

Sheep::Sheep()
{
    x = y = 0;
    spr=NULL;
}

Sheep::Sheep(Sprite *s, int xx, int yy)
{
    x = xx;
    y = yy;
    spr = s;
}

Sheep::~Sheep()
{
    //dtor
}

void Sheep::onUpdate()
{

}

void Sheep::onDraw(SDL_Surface *dest)
{
    if (spr && dest)
    {
        SDL_Rect t = (SDL_Rect){x, y, 0, 0};
        SDL_BlitSurface(spr->rawImage(), spr->getFrame(), dest, &t);
    }
}
