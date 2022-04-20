#include "NoDeliveriesState.h"

void NoDeliveriesState::step(App *app) {
    printBreak();

    std::cout << "No deliveries remaining!\n\n";

    std::cout << "2) Reset deliveries.\n";
    std::cout << "1) Go back.\n";
    std::cout << "0) Exit.\n";

    while (true) {
        int option = readOption(app);

        switch (option) {
            case 2: {
                app->resetScheduler();
                app->setState(new ChooseSceneryState());
                return;
            }
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
