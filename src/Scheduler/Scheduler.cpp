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


bool compareCouriersSize(const Courier& c1, const Courier& c2) {
    return (c1.getCapacity() > c2.getCapacity());
}
bool compareDeliveriesSize(const Delivery& d1, Delivery& d2) {
    return (d1.getCapacity() > d2.getCapacity());
}


bool compareCouriersCost(const Courier& c1, const Courier& c2) {
    return (c1.getCostRatio() < c2.getCostRatio());
}
bool compareDeliveriesCost(const Delivery& d1, const Delivery& d2) {
    return (d1.getCompensationRatio() < d2.getCompensationRatio());
}


bool compareDuration(const Delivery& d1, const Delivery& d2){
    return (d1.getDuration() < d2.getDuration());
}


bool compareCouriersFreeSpace(const Courier& c1, const Courier& c2) {
    return (c1.getFreeCapacity() < c2.getFreeCapacity());
}


Allocation Scheduler::scenery1() {
    std::sort(couriers.begin(), couriers.end(), compareCouriersSize);
    std::sort(deliveries.begin(), deliveries.end(), compareDeliveriesSize);

    std::list<Courier> available_couriers(couriers.begin(), couriers.end());

    initValues();

    for (Delivery& delivery : deliveries) {
        if (!getFirstFitUsed(delivery)) {
            getFirstFitNew(available_couriers, delivery);
        }
    }

    allocation.setCouriers(used_couriers);
    allocation.setDeliveries(allocated_deliveries);
    return allocation;
}

Allocation Scheduler::scenery2() {
    std::sort(couriers.begin(), couriers.end(), compareCouriersCost);
    std::sort(deliveries.begin(), deliveries.end(), compareDeliveriesCost);

    std::list<Courier> available_couriers(couriers.begin(), couriers.end());

    initValues();

    for (Delivery &delivery: deliveries) {
        if (!getFirstFitUsed(delivery)) {
            getFirstFitNew(available_couriers, delivery);
        }
    }

    allocation.setCouriers(used_couriers);
    allocation.setDeliveries(allocated_deliveries);
    return allocation;
}

Allocation Scheduler::scenery3() {
    std::sort(deliveries.begin(),deliveries.end(), compareDuration);

    initValues();

    used_couriers.push_back({INT_MAX,INT_MAX,0});

    for (Delivery& delivery : deliveries) {
        if(!(insertExpressDelivery(delivery))){
            break;
        }
    }
    allocation.setDeliveries(allocated_deliveries);
    allocation.setCouriers(used_couriers);
    return allocation;
}

void Scheduler::initValues() {
    used_couriers.clear();
    allocated_deliveries.clear();
    allocation.clear();
    time_available = 28800;
}

bool Scheduler::getFirstFitUsed(const Delivery &delivery) {
    for (int i = 0; i < used_couriers.size(); i++) {
        if (delivery.getVolume() <= used_couriers[i].getFreeVolume() &&
            delivery.getWeight() <= used_couriers[i].getFreeWeight())
        {
            used_couriers[i].updateFreeVolume(delivery.getVolume());
            used_couriers[i].updateFreeWeight(delivery.getWeight());
            allocated_deliveries[i].push_back(delivery);

            allocation.addDelivery(delivery);

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
        allocation.addWeight(delivery.getWeight(), delivery.getWeight());
        allocation.addVolume(delivery.getVolume(), delivery.getVolume());
        allocation.addProfit(delivery.getCompensation(), 0);
        time_available -= delivery.getDuration();
        return true;
    }
    return false;
}

bool Scheduler::getBestFitUsed(const Delivery &delivery) {
    std::sort(used_couriers.begin(), used_couriers.end(), compareCouriersFreeSpace);

    auto it = used_couriers.begin();

    while (it != used_couriers.end()) {
        if (delivery.getVolume() <= it->getFreeVolume() &&
            delivery.getWeight() <= it->getFreeWeight())
        {
            it->updateFreeVolume(delivery.getVolume());
            it->updateFreeWeight(delivery.getWeight());
            allocated_deliveries.push_back({delivery});

            allocation.addDelivery(delivery);
            return true;
        }
        it++;
    }

    return false;
}

bool Scheduler::getBestFitNew(std::list<Courier> &available_couriers, Delivery& delivery) {
    available_couriers.sort(compareCouriersFreeSpace);

    auto it = available_couriers.begin();
    while (it != available_couriers.end()) {
        if (delivery.getVolume() <= it->getVolume() &&
            delivery.getWeight() <= it->getWeight())
        {
            used_couriers.push_back(*it);
            allocated_deliveries.push_back({delivery});

            allocation.addWeight(delivery.getWeight(), it->getWeight());
            allocation.addVolume(delivery.getVolume(), it->getVolume());
            allocation.addProfit(delivery.getCompensation(), it->getCost());

            available_couriers.erase(it);
            return true;
        }
        it++;
    }

    return false;
}
