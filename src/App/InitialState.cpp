#include "InitialState.h"

void InitialState::step(App* app) {
    app->getScheduler()->scenario2();
    app->setState(nullptr);
}