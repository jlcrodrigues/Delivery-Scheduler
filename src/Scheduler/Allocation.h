#ifndef ALLOCATION_H
#define ALLOCATION_H

#include "Courier.h"
#include "Delivery.h"

#include <iostream>
#include <vector>


class Allocation {
public:
   Allocation() = default;

   Allocation(std::vector<Courier> couriers, std::vector<std::vector<Delivery> > deliveries);

   friend std::ostream& operator<<(std::ostream& os, const Allocation& allocation);

   void addWeight(const int& used_weight, const int& total_weight);

   void addVolume(const int& used_volume, const int& total_volume);

   void addProfit(const int& reward, const int& cost);

   void setWeight(const int& used_weight, const int& total_weight);

   void setVolume(const int& used_volume, const int& total_volume);

   void setProfit(const int& reward, const int& cost);

   void setCouriers(const std::vector<Courier> couriers);

   void setDeliveries(const std::vector<std::vector<Delivery> > deliveries);

   void clear();
private:
   int getDeliveriesCount() const;

   int used_weight;
   int total_weight;
   int used_volume;
   int total_volume;
   int reward;
   int cost;
   std::vector<Courier> couriers;
   std::vector<std::vector<Delivery> > deliveries;
};


#endif
