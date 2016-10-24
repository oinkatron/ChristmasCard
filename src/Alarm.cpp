#include "../include/Alarm.h"

vector<Alarm*> Alarm::alarm_list;

Alarm::Alarm()
{
    alarm_list.push_back(this);
    create_time = SDL_GetTicks();
    len = 0;
    action = NULL;

}

Alarm::Alarm(long a_t, void (*act)(void*))
{
    alarm_list.push_back(this);
    create_time = SDL_GetTicks();
    len = a_t;
    action = act;
}

void Alarm::tickAlarms()
{
    for (int i = alarm_list.size()-1; i >= 0; i--)
    {
        if (alarm_list[i]->isExpired())
        {
            alarm_list[i]->ring();
            alarm_list.erase(alarm_list.begin()+i);
        }
    }
}

void Alarm::ring()
{
    (*action)(NULL);
}

Alarm::~Alarm()
{
    //dtor
}
