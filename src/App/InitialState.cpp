#include "InitialState.h"

void InitialState::step(App* app) {
    std::cout << "Hello World!\n";
    app->setState(nullptr);
}