#include "State.h"

void State::run(App *app)
{
    step(app);
}

int State::readOption(App* app) const
{
    int option;

    while (!(std::cin >> option))
    {
        if (std::cin.eof()) app->setState(nullptr);
        else
        {
            std::cin.clear();
            std::cin.ignore(1000000, '\n');
            printInvalidOption();
        }
    }
    return option;
}

void State::printBreak() const
{
    for (int i = 0; i < 40; i++) std::cout << std::endl;
}

void State::printInvalidOption() const
{
    std::cout << "Invalid option. Try again.\n";
}