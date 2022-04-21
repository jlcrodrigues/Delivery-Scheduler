#ifndef DELIVERY_SCHEDULER_CHOOSESCENERYSTATE_H
#define DELIVERY_SCHEDULER_CHOOSESCENERYSTATE_H

#include "State.h"
#include "Scenery2State.h"
#include "Scenery1State.h"
#include "Scenery3State.h"
#include "InitialState.h"

class ChooseSceneryState : public State {
    void step(App* app) override;

private:
};


#endif //DELIVERY_SCHEDULER_CHOOSESCENERYSTATE_H
