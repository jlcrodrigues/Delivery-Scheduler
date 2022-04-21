#ifndef DELIVERY_SCHEDULER_SCENERY2STATE_H
#define DELIVERY_SCHEDULER_SCENERY2STATE_H

#include "State.h"
#include "ChooseSceneryState.h"
#include "NoDeliveriesState.h"

class Scenery2State : public State {
   void step(App* app) override;
};

#endif //DELIVERY_SCHEDULER_SCENERY2STATE_H
