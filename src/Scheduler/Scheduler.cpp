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

Allocation Scheduler::scenario2() {
    int reward = 0, cost = 0;
    int used_weight = 0, total_weight = 0;
    int used_volume = 0, total_volume = 0;
    std::sort(couriers.begin(), couriers.end(), compareCouriers);
    std::sort(deliveries.begin(), deliveries.end(), compareDeliveries);

    std::vector<std::pair<int, int> > usedSizes; //volume, weight
    std::vector<Courier> used_couriers;
    std::vector<std::vector<Delivery> > allocated_deliveries;

    for (Delivery& delivery : deliveries) {
        reward += delivery.getCompensation();
        used_weight += delivery.getWeight();
        used_volume += delivery.getVolume();
        bool assigned = false;
        for (int i = 0; i < used_couriers.size(); i++) {
            if (delivery.getVolume() < (couriers[i].getVolume() - usedSizes[i].first) &&
                    delivery.getWeight() < (couriers[i].getWeight() - usedSizes[i].second)) {
                usedSizes[i].first += delivery.getVolume();
                usedSizes[i].second += delivery.getWeight();
                assigned = true;
                allocated_deliveries[i].push_back(delivery);
                break;
            }
        }
        if (!assigned) {
            used_couriers.push_back(couriers[usedSizes.size() - 1]);
            allocated_deliveries.push_back({delivery});
            usedSizes.emplace_back(delivery.getVolume(), delivery.getWeight());
            total_weight += couriers[usedSizes.size() - 1].getWeight();
            total_volume += couriers[usedSizes.size() - 1].getVolume();
            cost += used_couriers[used_couriers.size() - 1].getCost();
        }
    }

    Allocation allocation;
    allocation.setWeight(used_weight, total_weight);
    allocation.setVolume(used_volume, total_volume);
    allocation.setProfit(reward, cost);
    allocation.setCouriers(couriers);
    allocation.setDeliveries(allocated_deliveries);
    return allocation;
}
