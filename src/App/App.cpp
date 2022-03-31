#include "App.h"

App::App()
{
    scheduler = new Scheduler();
    //TODO load data
}

void App::run()
{
    while (state != nullptr)
    {
        state->run(this);
    }
}

Scheduler* App::getScheduler() const
{
    return scheduler;
}

void App::setState(State* state)
{
    this->state = state;
}