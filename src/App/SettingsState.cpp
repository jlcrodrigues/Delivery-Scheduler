#include "SettingsState.h"

void SettingsState::step(App *app) {
    const int padding = 50;
    std::string _deliveries =  "Deliveries per day";
    std::string _time =  "Time available for express deliveries";
    printBreak();

    std::cout << "Settings\n\n";

    std::cout << _deliveries;
    std::cout << std::setfill('.') << std::setw(padding - _deliveries.size())
        << app->getScheduler()->getDeliveriesPerDay() << "\n";
    std::cout << _time;
    std::cout << std::setfill('.') << std::setw(padding - _time.size() - 1)
        << app->getScheduler()->getTimeAvailable() << "s\n";
    std::cout << std::endl;
    std::cout << "5) Set deliveries per day.\n";
    std::cout << "4) Change available time.\n";
    std::cout << "3) Reset deliveries.\n";
    std::cout << "2) Reset default.\n";
    std::cout << "\n1) Go back.\n";
    std::cout << "0) Exit.\n";

    while (true) {
        int option = readOption(app);

        switch (option) {
            case 5:
                std::cout << "Choose amount to be allocated: ";
                app->getScheduler()->setDeliveriesPerDay(readOption(app));
                app->setState(new SettingsState());
                return;
            case 4:
                std::cout << "Available time: ";
                app->getScheduler()->setTimeAvailable(readOption(app));
                app->setState(new SettingsState());
                return;
            case 3:
                app->resetScheduler();
                app->setState(new SettingsState());
                return;
            case 2:
                app->getScheduler()->setDeliveriesPerDay(100);
                app->getScheduler()->setTimeAvailable(28800);
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
