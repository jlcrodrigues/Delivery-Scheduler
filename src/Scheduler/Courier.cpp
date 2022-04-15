#include "Courier.h"

Courier::Courier(const int &volume, const int &weight, const int &cost) {
    this->volume = volume;
    this->weight = weight;
    this->cost = cost;
    free_volume = volume;
    free_weight = weight;
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

double Courier::getCostRatio() const {
    return cost / (weight + volume);
}

float Courier::getCapacity() const {
    return (weight + volume) / 2;
}
