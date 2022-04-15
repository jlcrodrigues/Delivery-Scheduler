#include "Scenery3State.h"

void Scenery3State::step(App* app) {
    printBreak();

    Allocation allocation = app->getScheduler()->scenery3();

    std::cout << "Scenario 3: Optimize express deliveries\n\n";
    std::cout << allocation << std::endl;

    std::cout << std::endl;
    std::cout << "1) Go back.\n";
    std::cout << "0) Exit.\n";

    while (true) {
        int option = readOption(app);

        switch (option) {
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