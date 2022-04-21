#include "Allocation.h"

Allocation::Allocation() {
    used_weight = 0;
    total_weight = 0;
    used_volume = 0;
    total_volume = 0;
    reward = 0;
    cost = 0;
    couriers = {};
    non_delivered = {};
}

std::ostream& operator<<(std::ostream& os, const Allocation& allocation) {
    os << "Allocated " << allocation.getDeliveriesCount();
    os << " (" << allocation.getDeliveriesRatio() << "%)" << " packages through ";
    os << allocation.couriers.size() << " vans.\n";
    os << "Used volume: " << allocation.getVolumeRatio() << "% ("
        << allocation.used_volume << "/" << allocation.total_volume << ").\n";
    os << "Used weight: " << allocation.getWeightRatio() << "% ("
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

std::vector<Delivery>& Allocation::getNonDelivered() {
    return non_delivered;
}

void Allocation::clearLosingCouriers() {
    auto it = couriers.begin();
    for (; it != couriers.end();) {
        if (it->getProfit() < 0) {
            clearLosingCouriersAux(*it);
            used_weight -= it->getWeight() - it->getFreeWeight();
            total_weight -= it->getWeight();
            used_volume -= it->getVolume() - it->getFreeVolume();
            total_volume -= it->getVolume();
            reward -= it->getCurrentReward();
            cost -= it->getCost();
            it = couriers.erase(it);
        }
        else it++;
    }
}

void Allocation::clearLosingCouriersAux(const Courier& courier) {
    for (auto d: courier.getAllocatedDeliveries()) {
        non_delivered.push_back(d);
    }
}

int Allocation::getDeliveriesCount() const {
    int count = 0;
    for (auto & c: couriers) {
       count += c.getAllocatedDeliveries().size();
    }
    return count;
}

int Allocation::getDeliveriesRatio() const {
    int delivered = getDeliveriesCount();
    if (delivered + non_delivered.size() == 0) return 0;
    return delivered * 100 / (delivered + non_delivered.size());
}

int Allocation::getVolumeRatio() const {
    if (total_volume == 0) return 0;
    return used_volume  * 100 / total_volume;
}

int Allocation::getWeightRatio() const {
    if (total_weight == 0) return 0;
    return used_weight  * 100 / total_weight;
}
