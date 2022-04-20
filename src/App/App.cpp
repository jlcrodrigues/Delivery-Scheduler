#include "App.h"

App::App()
{
    scheduler = new Scheduler("../data/vans.csv",
                              "../data/deliveries.csv");
    scheduler->setDeliveriesPerDay(100);
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

void App::resetScheduler() {
    scheduler = new Scheduler("../data/vans.csv",
                                      "../data/deliveries.csv");
    scheduler->setDeliveriesPerDay(100);
}

void App::setState(State* state)
{
    this->state = state;
}