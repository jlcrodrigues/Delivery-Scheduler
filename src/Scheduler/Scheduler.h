#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <list>

#include "Courier.h"
#include "Delivery.h"
#include "Allocation.h"

class Scheduler {

public:
   Scheduler() = default;

   Scheduler(const std::string& couriers_file, const std::string& deliveries_file);

   /**
    * Load the couriers vector from a csv file.
    * @param file_path The path of the csv file.
    */
   void loadCouriers(const std::string& file_path);

   /**
    * Load the deliveries vector from a csv file.
    * @param file_path The path of the csv file.
    */
   void loadDeliveries(const std::string& file_path);

   /**
    * Get the courier's vector.
    * @return A Vector of courier's objects.
    */
   std::vector<Courier> getCouriers() const;

   /**
    * Get the deliveries vector.
    * @return A Vector of deliveries objects.
    */
   std::vector<Delivery> getDeliveries() const;

   Allocation scenario2();

private:
   void initValues();
   bool getFirstFitUsed(const Delivery& delivery);
   bool getFirstFitNew(std::list<Courier>& available_couriers, Delivery& delivery);

   Allocation allocation;
   std::vector<Courier> couriers;
   std::vector<Delivery> deliveries;

   std::vector<Courier> used_couriers;
   std::vector<std::pair<int, int> > used_sizes; //volume, weight
   std::vector<std::vector<Delivery> > allocated_deliveries;

};


#endif
