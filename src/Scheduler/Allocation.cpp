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

void Allocation::addWeight(const int& used_weight, const int& total_weight) {
    this->used_weight += used_weight;
    this->total_weight += total_weight;
}

void Allocation::addVolume(const int &used_volume, const int &total_volume) {
    this->used_volume += used_volume;
    this->total_volume += total_volume;
}

void Allocation::addProfit(const int &reward, const int &cost) {
    this->reward += reward;
    this->cost += cost;
}

void Allocation::addCourier(const Courier &courier) {
    this->couriers.push_back(courier);
    this->total_volume += courier.getVolume();
    this->total_weight += courier.getWeight();
    this->cost += courier.getCost();
}

void Allocation::addDelivery(const Delivery &delivery) {
    this->used_weight += delivery.getWeight();
    this->used_volume += delivery.getVolume();
    this->reward += delivery.getCompensation();
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

void Allocation::clear() {
    used_weight = 0;
    total_weight = 0;
    used_volume = 0;
    total_volume = 0;
    reward = 0;
    cost = 0;
    couriers.clear();
}

std::vector<Courier>& Allocation::getUsedCouriers() {
    return couriers;
}

int Allocation::getDeliveriesCount() const {
    int count = 0;
    for (auto & c: couriers) {
       count += c.getAllocatedDeliveries().size();
    }
    return count;
}
