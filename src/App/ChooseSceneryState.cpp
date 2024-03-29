#include "ChooseSceneryState.h"

void ChooseSceneryState::step(App *app) {
    printBreak();
    std::cout << "\tScenery\n\n";
    std::cout << "3) Optimize express deliveries.\n";
    std::cout << "2) Optimize company profit.\n";
    std::cout << "1) Optimize number of couriers.\n\n";
    std::cout << "4) Go Back.\n";
    std::cout << "0) Exit.\n";

    while (true) {
        int option = readOption(app);

        switch (option) {
            case 4:
                app->setState(new InitialState());
                return;
            case 3:
                app->setState(new Scenery3State());
                return;
            case 2:
                app->setState(new Scenery2State());
                return;
            case 1:
                app->setState(new Scenery1State());
                return;
            case 0:
                app->setState(nullptr);
                return;
            default:
                printInvalidOption();
        }
    }
}


