#include "Scheduler.h"

Scheduler::Scheduler(const std::string &couriers_file, const std::string &deliveries_file) {
    loadCouriers(couriers_file);
    loadDeliveries(deliveries_file);
}

void Scheduler::loadCouriers(const std::string &file_path) {
    std::string row;
    std::ifstream file(file_path);
    if (!file.is_open()) return;
    getline(file, row); //ignore first line
    while (getline(file, row))
    {
        couriers.push_back(Courier(row));
    }
}

void Scheduler::loadDeliveries(const std::string &file_path) {
    std::string row;
    std::ifstream file(file_path);
    if (!file.is_open()) return;
    getline(file, row); //ignore first line
    while (getline(file, row))
    {
        deliveries.push_back(Delivery(row));
    }
}

std::vector<Courier> Scheduler::getCouriers() const {
    return couriers;
}

std::vector<Delivery> Scheduler::getDeliveries() const {
    return deliveries;
}


/*
// scenery 1

int Scheduler::scenery1(App *app) const {
    std::vector<Delivery> sort_deliveries = app->getScheduler()->getDeliveries();
    std::vector<Courier> sort_couriers = app->getScheduler()->getCouriers();

    std::sort(sort_deliveries.rbegin(), sort_deliveries.rend()); // sorting in reverse order
//    std::sort(sort_couriers.rbegin(), sort_couriers.rend());

//    for (auto d: deliveries) {
//        std::cout << d.getWeight() << "/ ";
//    }

// fazer overload da operação < dos couriers!!


    return firstFit(sort_couriers, sort_deliveries);
}

int Scheduler::firstFit(std::vector<Courier> couriers, const std::vector<Delivery> deliveries) const {
    std::vector<Courier> couriers_copy = couriers;
    std::vector<Courier> res;

    for (auto d: deliveries) {
        for (auto c: res) {
            if (c.getWeight() >= d.getWeight() && c.getVolume() >= d.getVolume()) {
                c.setWeight(c.getWeight() - d.getWeight());
                c.setVolume(c.getVolume() - d.getVolume());

                break;
            }
        }

        res.push_back(couriers_copy[0]);
        res.rbegin()->setWeight(res.rbegin()->getWeight() - d.getWeight());
        res.rbegin()->setVolume(res.rbegin()->getVolume() - d.getVolume());

    }
    return res.size();
}

*/
