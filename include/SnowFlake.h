#ifndef SNOWFLAKE_H
#define SNOWFLAKE_H

#include <vector>

#include "Sprite.h"

class SnowFlake
{
    public:
        SnowFlake();
        SnowFlake(int xx, int yy, float fall_speed, float rot_speed);
        virtual ~SnowFlake();

        static vector<SnowFlake*> flakes;

        void init(int xx, int yy, float fall_speed, float rot_speed);

        void onUpdate(long dt);
        void onDraw(SDL_Surface *dest);
    protected:
    private:
        Sprite *spr;

        int x, y;
        float angle;
        float r_speed;
        float f_speed;

};

#endif // SNOWFLAKE_H
