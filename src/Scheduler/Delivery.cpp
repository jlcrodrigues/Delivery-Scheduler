#include "Delivery.h"

Delivery::Delivery(const int &volume, const int &weight, const int &compensation, const int &duration) {
    this->volume = volume;
    this->weight = weight;
    this->compensation = compensation;
    this->duration = duration;
}

Delivery::Delivery(const std::string &row) {
    loadFromCsv(row);
}

void Delivery::loadFromCsv(const std::string &row) {
    std::string col;
    std::stringstream str(row);
    getline(str, col, ',');
    volume = stoi(col);
    getline(str, col, ',');
    weight = stoi(col);
    getline(str, col, ',');
    compensation = stoi(col);
    getline(str, col, ',');
    duration = stoi(col);
    getline(str, col, ',');
    duration = stoi(col);
}

int Delivery::getCompensation() const {
    return compensation;
}

int Delivery::getDuration() const {
    return duration;
}

int Delivery::getVolume() const {
    return volume;
}

int Delivery::getWeight() const {
    return weight;
}