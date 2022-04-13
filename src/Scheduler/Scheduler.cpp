#include "Scheduler.h"

Scheduler::Scheduler(const std::string &couriers_file, const std::string &deliveries_file) {
    loadCouriers(couriers_file);
    loadDeliveries(deliveries_file);
    time_available = 28800;
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
bool compareDuration(const Delivery& d1, const Delivery& d2){
    return (d1.getDuration() < d2.getDuration());
}

Allocation Scheduler::scenario2() {
    std::sort(couriers.begin(), couriers.end(), compareCouriers);
    std::sort(deliveries.begin(), deliveries.end(), compareDeliveries);

    std::list<Courier> available_couriers(couriers.begin(), couriers.end());

    initValues();

    for (Delivery& delivery : deliveries) {
        if (!getFirstFitUsed(delivery)) {
            getFirstFitNew(available_couriers, delivery);
        }
    }

    allocation.setCouriers(couriers);
    allocation.setDeliveries(allocated_deliveries);
    return allocation;
}

Allocation Scheduler::scenario3() {
    std::sort(deliveries.begin(),deliveries.end(), compareDuration);
    couriers.clear();
    couriers.push_back({0,0,0});

    initValues();

    for (Delivery& delivery : deliveries) {
        if(!(insertExpressDelivery(delivery))){
            break;
        }
    }
    allocation.setDeliveries(allocated_deliveries);
    allocation.setCouriers(couriers);
    return allocation;
}

void Scheduler::initValues() {
    used_couriers.clear();
    used_sizes.clear();
    allocated_deliveries.clear();
    allocation.clear();
}

bool Scheduler::getFirstFitUsed(const Delivery &delivery) {
    for (int i = 0; i < used_couriers.size(); i++) {
        if (delivery.getVolume() <= (couriers[i].getVolume() - used_sizes[i].first) &&
            delivery.getWeight() <= (couriers[i].getWeight() - used_sizes[i].second)) {
            used_sizes[i].first += delivery.getVolume();
            used_sizes[i].second += delivery.getWeight();
            allocated_deliveries[i].push_back(delivery);

            allocation.addWeight(delivery.getWeight(), 0);
            allocation.addVolume(delivery.getVolume(), 0);
            allocation.addProfit(delivery.getCompensation(), 0);

            return true;
        }
    }
    return false;
}

bool Scheduler::getFirstFitNew(std::list<Courier> &available_couriers, Delivery& delivery) {
    auto it = available_couriers.begin();
    for (; it != available_couriers.end(); it++) {
        if (delivery.getVolume() <= it->getVolume() &&
            delivery.getWeight() <= it->getWeight()) {
            used_couriers.push_back(*it);
            allocated_deliveries.push_back({delivery});
            used_sizes.emplace_back(delivery.getVolume(), delivery.getWeight());

            allocation.addWeight(delivery.getWeight(), it->getWeight());
            allocation.addVolume(delivery.getVolume(), it->getVolume());
            allocation.addProfit(delivery.getCompensation(), it->getCost());

            available_couriers.erase(it);
            return true;
        }
    }
    return false;
}

bool Scheduler::insertExpressDelivery(Delivery& delivery){
    if (delivery.getDuration()<=time_available){
        allocated_deliveries.push_back({delivery});
        allocation.addWeight(delivery.getWeight(), 0);
        allocation.addVolume(delivery.getVolume(), 0);
        allocation.addProfit(delivery.getCompensation(), 0);
        time_available -= delivery.getDuration();
        return true;
    }
    return false;
}