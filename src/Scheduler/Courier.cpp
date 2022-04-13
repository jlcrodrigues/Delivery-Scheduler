#include "Courier.h"

Courier::Courier(const int &volume, const int &weight, const int &cost) {
    this->volume = volume;
    this->weight = weight;
    this->cost = cost;
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
}

int Courier::getCost() const {
    return cost;
}

int Courier::getVolume() const {
    return volume;
}

int Courier::getWeight() const {
    return weight;
}

double Courier::getCostRatio() const {
    return cost / (weight + volume);
}

int Courier::getCapacity() const {
    return weight + volume;
}
