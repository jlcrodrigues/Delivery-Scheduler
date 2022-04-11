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

bool compareCouriers(const Courier& c1, const Courier& c2) {
    return (c1.getCostRatio() < c2.getCostRatio());
}
bool compareDeliveries(const Delivery& d1, const Delivery& d2) {
    return (d1.getCompensationRatio() < d2.getCompensationRatio());
}

std::vector<Courier> Scheduler::scenario2() {
    std::sort(couriers.begin(), couriers.end(), compareCouriers);
    std::sort(deliveries.begin(), deliveries.end(), compareDeliveries);

    std::vector<std::pair<int, int> > usedCouriers;
    int w = 0, w2 = 0, c = 0, c2 = 0;

    for (Delivery& delivery : deliveries) {
        c += delivery.getCompensation();
        w += delivery.getVolume();
        bool assigned = false;
        for (int i = 0; i < usedCouriers.size(); i++) {
            if (delivery.getVolume() < (couriers[i].getVolume() - usedCouriers[i].first) &&
                    delivery.getWeight() < (couriers[i].getWeight() - usedCouriers[i].second)) {
                usedCouriers[i].first += delivery.getVolume();
                usedCouriers[i].second += delivery.getWeight();
                assigned = true;
                break;
            }
        }
        if (!assigned) {
            usedCouriers.emplace_back(delivery.getVolume(), delivery.getWeight());
            w2 += couriers[usedCouriers.size() - 1].getVolume();
            c2 += couriers[usedCouriers.size() - 1].getCost();
        }
    }

    std::cout << deliveries.size() << std::endl;
    std::cout << usedCouriers.size() << std::endl;
    std::cout << "c " << c << std::endl;
    std::cout << "c2 " << c2 << std::endl;
    std::cout << "profit " << c - c2 << std::endl;
    std::cout << w << std::endl;
    std::cout << w2 << std::endl;
}
