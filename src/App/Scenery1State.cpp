#include "Scenery1State.h"

void Scenery1State::step(App *app) {
    printBreak();

    Allocation allocation = app->getScheduler()->scenario1();

    std::cout << "Scenario 1: Optimize number of couriers\n\n";
    std::cout << allocation << std::endl;

    std::cout << "2) See list of couriers.\n\n";
    std::cout << "1) Go back.\n";
    std::cout << "0) Exit.\n";

    while (true) {
        int option = readOption(app);

        switch (option) {
            case 2:
                displayCouriers(app, allocation);
                return;
            case 1:
                app->setState(new ChooseSceneryState());
                return;
            case 0:
                app->setState(nullptr);
                return;
            default:
                printInvalidOption();
        }
    }
}
