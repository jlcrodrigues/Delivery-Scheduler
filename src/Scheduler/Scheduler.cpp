#include "Scheduler.h"

Scheduler::Scheduler(const std::string &couriers_file, const std::string &deliveries_file) {
    loadCouriers(couriers_file);
    loadDeliveries(deliveries_file);
    current_day = 0;
    time_available = 28800;
    deliveries_per_day = INT_MAX;
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

int Scheduler::getDeliveriesPerDay() const {
    return deliveries_per_day;
}

void Scheduler::setDeliveriesPerDay(const int &amount) {
    deliveries_per_day = amount;
}

int Scheduler::getDay() const {
    return current_day;
}

int Scheduler::getTimeAvailable() const {
    return time_available;
}

void Scheduler::setTimeAvailable(const int &time_available) {
    this->time_available = time_available;
}

std::vector<Courier> Scheduler::getCouriers() const {
    return couriers;
}

std::vector<Delivery> Scheduler::getDeliveries() const {
    return deliveries;
}

bool Scheduler::hasDeliveries() const {
    return !(deliveries.empty() && daily_deliveries.empty());
}

bool compareCouriersSize(const Courier& c1, const Courier& c2) {
    return (c1.getCapacity() > c2.getCapacity());
}

bool compareDeliveriesSize(const Delivery& d1, Delivery& d2) {
    if (d1.getDay() == d2.getDay())
        return (d1.getCapacity() > d2.getCapacity());
    return (d1.getDay() < d2.getDay());
}

bool compareCouriersCost(const Courier& c1, const Courier& c2) {
    return (c1.getCostRatio() < c2.getCostRatio());
}

bool compareDeliveriesCost(const Delivery& d1, const Delivery& d2) {
    if (d1.getDay() == d2.getDay())
        return (d1.getCompensationRatio() > d2.getCompensationRatio());
    return (d1.getDay() < d2.getDay());
}

bool compareDuration(const Delivery& d1, const Delivery& d2){
    if (d1.getDay() == d2.getDay())
        return (d1.getDuration() < d2.getDuration());
    return (d1.getDay() < d2.getDay());
}

Allocation Scheduler::scenario1() {
    allocation = Allocation();
    std::vector<Courier> couriers_copy(couriers.begin(), couriers.end());
    std::sort(couriers_copy.begin(), couriers_copy.end(), compareCouriersSize);

    setNextDeliveries();
    std::sort(daily_deliveries.begin(), daily_deliveries.end(), compareDeliveriesSize);

    std::list<Courier> available_couriers(couriers_copy.begin(), couriers_copy.end());

    std::vector<Delivery>& non_delivered = allocation.getNonDelivered();

    initValues();

    for (Delivery& delivery : daily_deliveries) {
        if (!getFirstFitUsed(delivery)) {
            if (!getFirstFitNew(available_couriers, delivery))
                non_delivered.push_back(delivery);
        }
    }

    //allocation.clearLosingCouriers();
    daily_deliveries = allocation.getNonDelivered();
    current_day++;
    return allocation;
}

Allocation Scheduler::scenario2() {
    allocation = Allocation();
    std::vector<Courier> couriers_copy(couriers.begin(), couriers.end());
    std::sort(couriers_copy.begin(), couriers_copy.end(), compareCouriersCost);

    setNextDeliveries();
    std::sort(daily_deliveries.begin(), daily_deliveries.end(), compareDeliveriesCost);

    std::list<Courier> available_couriers(couriers_copy.begin(), couriers_copy.end());

    std::vector<Delivery>& non_delivered = allocation.getNonDelivered();

    initValues();

    for (Delivery &delivery: daily_deliveries) {
        if (!getFirstFitUsed(delivery)) {
            if (!getFirstFitNew(available_couriers, delivery)) {
                non_delivered.push_back(delivery);
            }
        }
    }

    allocation.clearLosingCouriers();
    daily_deliveries = allocation.getNonDelivered();
    current_day++;
    return allocation;
}

Allocation Scheduler::scenario3() {
    std::vector<Courier>& used_couriers = allocation.getUsedCouriers();

    setNextDeliveries();
    std::sort(daily_deliveries.begin(), daily_deliveries.end(), compareDuration);

    std::vector<Delivery>& non_delivered = allocation.getNonDelivered();

    initValues();

    used_couriers.push_back({INT_MAX,INT_MAX,0});

    auto it = daily_deliveries.begin();
    for (; it != daily_deliveries.end(); it++) {
        if(!(insertExpressDelivery(*it))){
            break;
        }
    }
    for (; it != daily_deliveries.end(); it++) {
        non_delivered.push_back(*it);
    }

    daily_deliveries = allocation.getNonDelivered();
    current_day++;
    return allocation;
}

Allocation Scheduler::scenario1BruteForce(){
    std::vector<Delivery> deliveries_copy(deliveries.begin(), deliveries.end());
    std::sort(deliveries_copy.begin(), deliveries_copy.end(), compareDeliveriesSize);

    initValues();

    std::vector<Courier> couriers_copy(couriers.begin(), couriers.end());
    std::sort(couriers_copy.begin(), couriers_copy.end(), compareCouriersSize);
    std::list<Courier> available_couriers(couriers_copy.begin(), couriers_copy.end());

}

int Scheduler::recursiveTesting(Allocation &best ,std::vector<Delivery> deliveries ,int deliveryId ,int courierId){
    int courier_amount = INT_MAX;
    if (deliveryId == deliveries.size()){
        best.setVolume(0,0);
        best.setWeight(0,0);
        return 0;
    }

    for (int i=0;i<couriers.size();i++){
        Allocation courier_i;
        int courier_i_amount = recursiveTesting(courier_i,deliveries, deliveryId+1, i);
        if (courier_i_amount < courier_amount){
            best = courier_i;
            courier_amount = courier_i_amount;
        }
    }
    std::vector<Courier>& used_couriers = best.getUsedCouriers();
    if (deliveries[deliveryId].getVolume() <= couriers[courierId].getVolume() &&
        deliveries[deliveryId].getWeight() <= couriers[courierId].getFreeWeight()){

    }

}

void Scheduler::initValues() {
    std::vector<Delivery>& non_delivered = allocation.getNonDelivered();

    non_delivered.clear();
    allocation.clear();
}

bool Scheduler::getFirstFitUsed(const Delivery &delivery) {
    std::vector<Delivery>& non_delivered = allocation.getNonDelivered();
    std::vector<Courier>& used_couriers = allocation.getUsedCouriers();
    for (int i = 0; i < used_couriers.size(); i++) {
        if (delivery.getVolume() <= used_couriers[i].getFreeVolume() &&
            delivery.getWeight() <= used_couriers[i].getFreeWeight())
        {
            used_couriers[i].addDelivery(delivery);
            allocation.addDelivery(delivery);

            return true;
        }
    }
    return false;
}

bool Scheduler::getFirstFitNew(std::list<Courier> &available_couriers, Delivery& delivery) {
    std::vector<Courier>& used_couriers = allocation.getUsedCouriers();
    auto it = available_couriers.begin();
    for (; it != available_couriers.end(); it++) {
        if (delivery.getVolume() <= it->getVolume() &&
            delivery.getWeight() <= it->getWeight()) {

            it->addDelivery(delivery);
            allocation.addCourier(*it);
            allocation.addDelivery(delivery);

            available_couriers.erase(it);
            return true;
        }
    }
    return false;
}

bool Scheduler::insertExpressDelivery(Delivery& delivery){
    std::vector<Courier>& used_couriers = allocation.getUsedCouriers();
    if (delivery.getDuration()<=time_available){
        used_couriers[0].addDelivery(delivery);
        allocation.addWeight(delivery.getWeight(), delivery.getWeight());
        allocation.addVolume(delivery.getVolume(), delivery.getVolume());
        allocation.addProfit(delivery.getCompensation(), 0);
        time_available -= delivery.getDuration();
        return true;
    }
    return false;
}

void Scheduler::setNextDeliveries() {
    auto it = deliveries.begin();
    int i = 0;
    while (it != deliveries.end() && i < deliveries_per_day) {
        it->setDay(current_day);
        daily_deliveries.push_back(*it);
        it = deliveries.erase(it);
        i++;
    }
}
