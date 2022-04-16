#include "Courier.h"

Courier::Courier(const int &volume, const int &weight, const int &cost) {
    this->volume = volume;
    this->weight = weight;
    this->cost = cost;
    this->free_volume = volume;
    this->free_weight = weight;
    this->current_reward = 0;
}

Courier::Courier(const std::string &row) {
    loadFromCsv(row);
}

void Courier::loadFromCsv(const std::string &row) {
    std::string col;
    std::stringstream str(row);
    getline(str, col, ',');
    volume = stoi(col);
    getline(str, col, ',');
    weight = stoi(col);
    getline(str, col, ',');
    cost = stoi(col);
    free_volume = volume;
    free_weight = weight;
}

int Courier::getCost() const {
    return cost;
}

int Courier::getVolume() const {
    return volume;
}

int Courier::getFreeVolume() const{
    return free_volume;
}

void Courier::updateFreeVolume(const int vol) {
    free_volume -= vol;
}

int Courier::getWeight() const {
    return weight;
}

int Courier::getFreeWeight() const{
    return free_weight;
}

void Courier::updateFreeWeight(int w) {
    free_weight -= w;
}

int Courier::getCurrentReward() const {
    return current_reward;
}

int Courier::getProfit() const {
    return current_reward - cost;
}

void Courier::addDelivery(const Delivery& delivery) {
    updateFreeVolume(delivery.getVolume());
    updateFreeWeight(delivery.getWeight());
    current_reward += delivery.getCompensation();
    allocated_deliveries.push_back(delivery);
};

double Courier::getCostRatio() const {
    return cost / (weight + volume);
}

float Courier::getCapacity() const {
    return (weight + volume) / 2;
}

std::vector<Delivery> Courier::getAllocatedDeliveries() const {
    return allocated_deliveries;
}
