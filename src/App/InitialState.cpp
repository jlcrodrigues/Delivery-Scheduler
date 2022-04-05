#include "InitialState.h"

void InitialState::step(App* app) {
    std::vector<Courier> couriers = app->getScheduler()->getCouriers();
    std::vector<Delivery> deliveries = app->getScheduler()->getDeliveries();

    std::cout << couriers[0].getVolume() << " ";
    std::cout << couriers[couriers.size() - 1].getVolume() << std::endl;
    std::cout << deliveries[0].getVolume() << " ";
    std::cout << deliveries[deliveries.size() - 1].getVolume() << std::endl;
    app->setState(nullptr);
}