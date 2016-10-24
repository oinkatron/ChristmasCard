#ifndef SHEEP_H
#define SHEEP_H

#include "Sprite.h"


class Sheep
{
    public:
        Sheep();
        Sheep(Sprite *spr, int x, int y);
        virtual ~Sheep();

        void onUpdate();
        void onDraw(SDL_Surface *dest);

        void sprite(Sprite *s) { spr = s; spr->resetTime(); }
        Sprite *sprite() { return spr; }
    protected:
    private:
        int x, y;
        Sprite *spr;
};

#endif // SHEEP_H
