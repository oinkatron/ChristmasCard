#ifndef ALARM_H
#define ALARM_H

#include <SDL/SDL.h>
#include <vector>
#include <iostream>

using namespace std;

class Alarm
{
    public:
        Alarm();
        Alarm (long a_t, void (*act)(void*));
        virtual ~Alarm();

        static vector<Alarm*> alarm_list;
        static void tickAlarms();

        bool isExpired() { return (SDL_GetTicks() - create_time >= len); }
        void ring();
    protected:
    private:
        long len;
        long create_time;
        void (*action)(void*);

};

#endif // ALARM_H
