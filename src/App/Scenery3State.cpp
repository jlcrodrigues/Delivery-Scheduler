#include "Scenery3State.h"

void Scenery3State::step(App* app) {
    printBreak();

    Allocation allocation = app->getScheduler()->scenario3();

    std::cout << allocation;

    std::cout << std::endl;
    std::cout << "2) See list of couriers.\n\n";
    std::cout << "1) Go back.\n";
    std::cout << "0) Exit.\n";

    while (true) {
        int option = readOption(app);

        switch (option) {
            case 2:
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