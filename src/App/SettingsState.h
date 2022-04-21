#ifndef DELIVERY_SCHEDULER_SETTINGSSTATE_H
#define DELIVERY_SCHEDULER_SETTINGSSTATE_H

#include "State.h"
#include "InitialState.h"

class SettingsState : public State {
   void step(App* app) override;
private:

};


#endif //DELIVERY_SCHEDULER_SETTINGSSTATE_H
