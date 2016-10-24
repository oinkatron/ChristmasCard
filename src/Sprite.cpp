#include "../include/Sprite.h"

Sprite::Sprite()
{
    img = NULL;
    frames = NULL;
    n_frames = 0;
    c_frame = 0;
    f_w = 0;
    f_h = 0;
    l_frame = 0;
    f_speed = 50;
}

Sprite::Sprite(SDL_Surface *raw, int num_frames, int x, int y, int w, int h)
{
    f_speed = 50;
    init(raw, num_frames, x, y, w, h);
}

Sprite::Sprite(string f_n, int num_frames, int x, int y, int w, int h)
{
    f_speed = 50;
    img = Sprite::loadImage(f_n);
    if (img)
        init(img, num_frames, x, y, w, h);

}

Sprite::~Sprite()
{
    //dtor
}

SDL_Surface *Sprite::loadImage(string f_name)
{
    SDL_Surface *tmp=NULL, *opt=NULL;

    tmp = IMG_Load(f_name.c_str());
    if (!tmp)
    {
        return NULL;
    }

    opt=SDL_DisplayFormat(tmp);
    if (!opt)
    {
        SDL_FreeSurface(tmp);
        return NULL;
    }

    SDL_SetColorKey(opt, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(opt->format, 255, 0, 255));
    return opt;

}

void Sprite::init(SDL_Surface *raw, int num_frames, int x, int y, int w, int h)
{
    img = raw;
    n_frames = num_frames;
    c_frame = 0;
    f_w = w;
    f_h = h;
    l_frame = SDL_GetTicks();

    frames = new SDL_Rect[n_frames];

    for (int i = 0; i < n_frames; i++)
    {
        frames[i] = (SDL_Rect){x+(i*w), y, w, h};
    }
}

SDL_Rect* Sprite::getFrame()
{
    long dif = (SDL_GetTicks() - l_frame);

    if (f_speed > 0)
    {
        int o_f = c_frame;
        while (dif >= f_speed)
        {
            c_frame++;
            dif -= f_speed;
        }

        if (o_f != c_frame)
            l_frame = SDL_GetTicks() + dif;


        if (c_frame >= n_frames)
                c_frame -= n_frames;
    }

    return &frames[c_frame];
}
