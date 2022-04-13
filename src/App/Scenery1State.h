#ifndef DELIVERY_SCHEDULER_SCENERY1STATE_H
#define DELIVERY_SCHEDULER_SCENERY1STATE_H

#include "State.h"
#include "ChooseSceneryState.h"

class Scenery1State : public State {
   void step(App* app) override;
};


#endif //DELIVERY_SCHEDULER_SCENERY1STATE_H
