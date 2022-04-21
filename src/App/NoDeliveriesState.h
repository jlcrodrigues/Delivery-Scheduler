#ifndef DELIVERY_SCHEDULER_NODELIVERIESSTATE_H
#define DELIVERY_SCHEDULER_NODELIVERIESSTATE_H

#include "State.h"
#include "ChooseSceneryState.h"

class NoDeliveriesState : public State {
    void step(App* app) override;
};


#endif //DELIVERY_SCHEDULER_NODELIVERIESSTATE_H
