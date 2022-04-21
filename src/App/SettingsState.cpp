#include "SettingsState.h"

void SettingsState::step(App *app) {
    printBreak();

    std::cout << "  Settings\n\n";

    std::cout << "Deliveries per day: ";
    std::cout << app->getScheduler()->getDeliveriesPerDay() << ".\n";
    std::cout << std::endl;
    std::cout << "3) Set deliveries per day.\n";
    std::cout << "2) Reset deliveries.\n";
    std::cout << "\n1) Go back.\n";
    std::cout << "0) Exit.\n";

    while (true) {
        int option = readOption(app);

        switch (option) {
            case 3:
                std::cout << "Choose amount to be allocated: ";
                app->getScheduler()->setDeliveriesPerDay(readOption(app));
                app->setState(new SettingsState());
                return;
            case 2:
                app->resetScheduler();
                app->setState(new SettingsState());
                return;
            case 1:
                app->setState(new InitialState());
                return;
            case 0:
                app->setState(nullptr);
                return;
            default:
                printInvalidOption();
        }
    }
}
