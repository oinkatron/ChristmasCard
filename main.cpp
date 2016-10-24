#ifdef __cplusplus
    #include <cstdlib>
    #include <ctime>
#else
    #include <stdlib.h>
#endif

#define RAND(MIN, MAX) ((rand()%((MAX)-(MIN)))+(MIN))

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

#include "./include/SnowFlake.h"
#include "./include/Sheep.h"
#include "./include/Alarm.h"

#define SHEEP_DELAY 1850
#define TEXT_DELAY 300

long f_time = 0, last_f_time = 0, st_time = 0;

SDL_Surface *srf_msg_back;
SDL_Surface *srf_msg;
SDL_Color msg_color;

SDL_Surface *sheep_sheet = NULL;
SDL_Surface *back_image = NULL;
SDL_Surface *stump = NULL;
Sprite *d_left=NULL, *d_right=NULL;
Sheep *left_sheep=NULL, *right_sheep=NULL;

TTF_Font *f = NULL;

Mix_Music *back_song = NULL;
int audio_rate = 22050;
int num_channels = 2;
int audio_buff_size = 4096;

float randFloat(float f_mn, float f_mx);
void changeLeftToLeft(void *v);
void changeLeftToRight(void *v);
void changeRightToLeft(void *v);
void changeRightToRight(void *v);

void changeTextToGreen(void *v);
void changeTextToRed(void *v);

float randFloat(float f_mn, float f_mx)
{
    float range = (f_mx - f_mn);
    return (((float)rand()/(float)RAND_MAX) * range) + f_mn;
}

void changeTextToGreen(void *v)
{
    if (srf_msg)
    {
        SDL_FreeSurface(srf_msg);
        srf_msg = TTF_RenderText_Blended(f, "Merry Christmas!", (SDL_Color){0, 255, 0, 255});
        new Alarm(TEXT_DELAY, &changeTextToRed);
    }
}

void changeTextToRed(void *v)
{
    if (srf_msg)
    {
        SDL_FreeSurface(srf_msg);
        srf_msg = TTF_RenderText_Blended(f, "Merry Christmas!", (SDL_Color){255, 0, 0, 255});
        new Alarm(TEXT_DELAY, &changeTextToGreen);
    }
}

void changeLeftToRight(void *v)
{
    if (left_sheep)
    {
        left_sheep->sprite(d_right);
        new Alarm(SHEEP_DELAY, &changeLeftToLeft);
    }
}

void changeLeftToLeft(void *v)
{
    if (left_sheep)
    {
        left_sheep->sprite(d_left);
        new Alarm(SHEEP_DELAY, &changeLeftToRight);
    }
}

void changeRightToLeft(void *v)
{
    if (right_sheep)
    {
        right_sheep->sprite(d_left);
        new Alarm(SHEEP_DELAY, &changeRightToRight);
    }
}

void changeRightToRight(void *v)
{
    if (right_sheep)
    {
        right_sheep->sprite(d_right);
        new Alarm(SHEEP_DELAY, &changeRightToLeft);
    }
}

int main ( int argc, char** argv )
{
    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(600, 200, 32,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }

    if (TTF_Init() < 0)
    {
        //cout << "Unable to init fonts! :(" << endl;
        return 1;
    }

    f = TTF_OpenFont("main.ttf", 32);
    if (!f)
    {
        return 1;
    }

    if (Mix_OpenAudio(audio_rate, MIX_DEFAULT_FORMAT, num_channels, audio_buff_size) < 0)
    {
        printf("Error Opening Audio :(\n");
        return 1;
    }

    back_song = Mix_LoadMUS("song.ogg");
    if (!back_song)
    {
        printf("Error opening song\n");
        return 1;
    }

    if (Mix_PlayMusic(back_song, -1) == -1)
    {
        printf("error plain music!\n");
        return 1;
    }

    srf_msg = TTF_RenderText_Blended(f, "Merry Christmas!", (SDL_Color){255, 0, 0, 255});
    srf_msg_back = TTF_RenderText_Blended(f, "Merry Christmas!", (SDL_Color){0, 0, 0, 255});

    srand((unsigned)time(NULL));

    sheep_sheet = Sprite::loadImage("dancin.bmp");
    stump = Sprite::loadImage("stump.bmp");
    back_image = Sprite::loadImage("back.bmp");

    d_left = new Sprite (sheep_sheet, 2, 0, 0, 48, 51);
    d_left->frameSpeed(200);

    d_right = new Sprite(sheep_sheet, 2, 94, 0, 48, 51);
    d_right->frameSpeed(200);

    left_sheep = new Sheep(d_right, 20, 135);
    right_sheep = new Sheep(d_left, 532, 135);

    new Alarm(1800, &changeLeftToLeft);
    new Alarm(1800, &changeRightToRight);
    new Alarm(300, &changeTextToGreen);

    //Sprite *spr = new Sprite("flakes_1.png", 15,  0, 0, 64, 64);

    for (int i = 0; i < 100; i++)
    {
        new SnowFlake(RAND(0, 600), RAND(0, 200), RAND(75, 125), randFloat(2.f, 4.f));
    }

    SDL_WM_SetCaption("**~Merry Christmas Sheepyboo~**", NULL);

    // program main loop
    bool done = false;
    while (!done)
    {
        last_f_time = st_time;
        st_time = SDL_GetTicks();
        f_time = st_time - last_f_time;
        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
            case SDL_QUIT:
                done = true;
                break;

                // check for keypresses
            case SDL_KEYDOWN:
                {
                    // exit if ESCAPE is pressed
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        done = true;
                    break;
                }
            } // end switch
        } // end of message processing

        Alarm::tickAlarms();

        for (int i = 0; i < SnowFlake::flakes.size(); i++)
        {
            SnowFlake::flakes[i]->onUpdate(f_time);
        }

        // DRAWING STARTS HERE
        SDL_Rect tr;

        tr = (SDL_Rect){0, 0, 600, 200};
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 128, 128, 255));

        tr = (SDL_Rect){0, 0, 0, 0};
        SDL_BlitSurface(back_image, NULL, screen, &tr);

        tr = (SDL_Rect){20, 180, 0, 0};
        SDL_BlitSurface(stump, NULL, screen, &tr);

        tr =(SDL_Rect){532, 180, 0, 0};
        SDL_BlitSurface(stump, NULL, screen, &tr);

        left_sheep->onDraw(screen);
        right_sheep->onDraw(screen);

        for (int i = 0; i < SnowFlake::flakes.size(); i++)
        {
            SnowFlake::flakes[i]->onDraw(screen);
        }

        tr = (SDL_Rect){300 - (srf_msg_back->w/2) + 3, 15, srf_msg_back->w, srf_msg_back->h};
        SDL_BlitSurface(srf_msg_back, NULL, screen, &tr);

        tr = (SDL_Rect){300 - (srf_msg->w/2), 10, srf_msg->w, srf_msg->h};
        SDL_BlitSurface(srf_msg, NULL, screen, &tr);


        // DRAWING ENDS HERE

        // finally, update the screen :)
        SDL_Flip(screen);

        if (SDL_GetTicks() - st_time < 1000/60)
        {
            SDL_Delay(1000/60 - (SDL_GetTicks()-st_time));
        }
    } // end main loop

    // free loaded bitmap
    //SDL_FreeSurface(bmp);

    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}
