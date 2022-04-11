#include "Allocation.h"

std::ostream& operator<<(std::ostream& os, const Allocation& allocation) {
    os << "Allocated " << allocation.getDeliveriesCount() << " packages through ";
    os << allocation.couriers.size() << " vans.\n";
    os << "Used volume: " << (double)(allocation.used_volume  * 100 / allocation.total_volume) << "% ("
        << allocation.used_volume << "/" << allocation.total_volume << ").\n";
    os << "Used weight: " << (allocation.used_weight * 100/ allocation.total_weight) << "% ("
        << allocation.used_weight << "/" << allocation.total_weight << ").\n";
    os << "Total profit: " << allocation.reward - allocation.cost << ".\n\n";
    return os;
}

void Allocation::setWeight(const int& used_weight, const int& total_weight) {
    this->used_weight = used_weight;
    this->total_weight = total_weight;
}

void Allocation::setVolume(const int &used_volume, const int &total_volume) {
    this->used_volume = used_volume;
    this->total_volume = total_volume;
}

void Allocation::setProfit(const int &reward, const int &cost) {
    this->reward = reward;
    this->cost = cost;
}

void Allocation::setCouriers(const std::vector<Courier> couriers) {
    this->couriers = couriers;
}

void Allocation::setDeliveries(const std::vector<std::vector<Delivery>> deliveries) {
    this->deliveries = deliveries;
}

int Allocation::getDeliveriesCount() const {
    int count = 0;
    for (auto & v : deliveries)
        count += v.size();
    return count;
}