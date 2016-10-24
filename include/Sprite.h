#ifndef SPRITE_H
#define SPRITE_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Sprite
{
    public:
        Sprite();
        Sprite(SDL_Surface *raw, int num_frames, int x, int y, int w, int h);
        Sprite(string f_n, int num_frames, int x, int y, int w, int h);
        virtual ~Sprite();

        void init(SDL_Surface *raw, int num_frames, int x, int y, int w, int h);
        SDL_Rect *getFrame(int i) { return ((i >= 0 && i < n_frames) ? &frames[i] : NULL); }
        SDL_Rect *getFrame();

        int frameWidth() { return f_w; }
        int frameHeight() { return f_h; }

        SDL_Surface *rawImage() { return img; }
        int numFrames() { return n_frames; }

        void frameSpeed(int val) { f_speed = val; }
        int frameSpeed() { return f_speed; }

        void resetTime() { l_frame = SDL_GetTicks(); };

        static SDL_Surface *loadImage(string f_name);
    protected:
    private:
        SDL_Surface *img;
        SDL_Rect *frames;
        int n_frames;
        int c_frame;
        int f_w;
        int f_h;
        long l_frame;
        long f_speed;


};

#endif // SPRITE_H
