#include "Scenery1State.h"

void Scenery1State::step(App *app) {
    printBreak();

    if (!app->getScheduler()->hasDeliveries()) {
        app->setState(new NoDeliveriesState());
        return;
    }

    Allocation allocation = app->getScheduler()->scenario1();

    std::cout << "Scenario 1: Optimize number of couriers\n\n";
    std::cout << " - Day " << app->getScheduler()->getDay() << "\n";
    std::cout << allocation << std::endl;

    std::cout << "3) See list of couriers.\n";
    std::cout << "2) Next day.\n\n";
    std::cout << "1) Go back.\n";
    std::cout << "0) Exit.\n";

    while (true) {
        int option = readOption(app);

        switch (option) {
            case 3:
                displayCouriers(app, allocation);
                app->getScheduler()->prevDay();
                return;
            case 2:
                app->setState(new Scenery1State());
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
