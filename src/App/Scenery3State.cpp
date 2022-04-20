#include "Scenery3State.h"

void Scenery3State::step(App* app) {
    printBreak();

    if (!app->getScheduler()->hasDeliveries()) {
        app->setState(new NoDeliveriesState());
        return;
    }

    Allocation allocation = app->getScheduler()->scenario3();

    std::cout << "Scenario 3: Optimize express deliveries\n\n";
    std::cout << " - Day " << app->getScheduler()->getDay() << "\n";
    std::cout << allocation << std::endl;

    std::cout << std::endl;
    std::cout << "2) Next day.\n\n";
    std::cout << "1) Go back.\n";
    std::cout << "0) Exit.\n";

    while (true) {
        int option = readOption(app);

        switch (option) {
            case 2:
                app->setState(new Scenery3State());
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