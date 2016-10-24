#include "../include/SnowFlake.h"

vector<SnowFlake*> SnowFlake::flakes;

SnowFlake::SnowFlake()
{
    flakes.push_back(this);
    x = 0;
    y = 0;
    angle = 0;
    r_speed = 0;
    f_speed = 0;
}

SnowFlake::SnowFlake(int xx, int yy, float fall_speed, float rot_speed)
{
    flakes.push_back(this);
    init(xx, yy, fall_speed, rot_speed);
}

SnowFlake::~SnowFlake()
{
    //dtor
}

void SnowFlake::init(int xx, int yy, float fall_speed, float rot_speed)
{
    x = xx;
    y = yy;
    angle = 0;
    r_speed = rot_speed;
    f_speed = fall_speed;
}

void SnowFlake::onUpdate(long dt)
{
    float t_step = (float)dt/1000.f;
    angle += r_speed * t_step;
    if (angle > 360)
        angle -= 360;
    else if (angle < 0)
        angle += 360;

    y += (int)(f_speed * t_step);
    if (y > 200)
    {
        x = rand()%600;
        y = 0;
    }
}

void SnowFlake::onDraw(SDL_Surface *dest)
{
    SDL_Rect tmp;
    tmp.x = x;
    tmp.y = y;
    tmp.w = 2;//spr->frameWidth();
    tmp.h = 2;//spr->frameHeight();
    SDL_FillRect(dest, &tmp, SDL_MapRGB(dest->format, 255, 255, 255));
}
