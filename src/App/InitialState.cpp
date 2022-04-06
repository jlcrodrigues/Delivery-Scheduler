#include "InitialState.h"

void InitialState::step(App* app) {
/*
    std::vector<Courier> couriers = app->getScheduler()->getCouriers();
    std::vector<Delivery> deliveries = app->getScheduler()->getDeliveries();

    std::cout << couriers[0].getVolume() << " ";
    std::cout << couriers[couriers.size() - 1].getVolume() << std::endl;
    std::cout << deliveries[0].getVolume() << " ";
    std::cout << deliveries[deliveries.size() - 1].getVolume() << std::endl;
    app->setState(nullptr);
*/
   printBreak();

   std::cout << "\tMenu\n\n";
   std::cout << "2) Start\n";
   std::cout << "0) Exit\n";

   while (true)
   {
       int option = readOption(app);

       switch (option) {
           case 2:
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