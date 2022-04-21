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
    int deliveries_per_day = scheduler->getDeliveriesPerDay();
    int time = scheduler->getTimeAvailable();
    scheduler = new Scheduler("../data/vans.csv",
                                      "../data/deliveries.csv");
    scheduler->setDeliveriesPerDay(deliveries_per_day);
    scheduler->setTimeAvailable(time);
}

void App::setState(State* state)
{
    this->state = state;
}