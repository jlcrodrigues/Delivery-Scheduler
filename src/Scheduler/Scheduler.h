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
   /** Scheduler's default constructor. **/
   Scheduler() = default;

   /**
    * Constructor for Scheduler.
    * @param couriers_file A csv file containing the delivery vans.
    * @param deliveries_file A csv file containing the deliveries.
    */
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
    * Get the amount of deliveries being attempted to allocate per day.
    * @return Integer with the amount of deliveries tried to allocate daily.
    */
   int getDeliveriesPerDay() const;

   /**
    * Get the time available for the express deliveries.
    * @return Time available for scenario 3 in seconds.
    */
   int getTimeAvailable() const;

   /**
    * Set the time available for the express deliveries.
    * @param time_available  Time available for scenario 3 in seconds.
    */
   void setTimeAvailable(const int& time_available);

   /**
    * Change the amount of deliveries considered in a day.
    * @param amount The amount of deliveries to be allocated in a day.
    */
   void setDeliveriesPerDay(const int& amount);

   /**
    * Get the current day.
    * @return Integer with the current day.
    */
   int getDay() const;

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

   /**
    * Check if the scheduler still has deliveries remaining.
    * @return True if there are any deliveries left and false otherwise.
    */
   bool hasDeliveries() const;

   /**
    * Get allocation for the scenario 1. Allocates the deliveries to optimize number of couriers.
    * @return An allocation object with the results of the algorithm.
    */
   Allocation scenario1();

   /**
    * Get an allocation for the scenario 2. Allocates the deliveries to maximize profit.
    * @return An allocation object with the results of the algorithm.
    */
   Allocation scenario2();

   /**
    * Get an allocation for the scenario 3. Allocates the deliveries to minimize the average time for each delivery.
    * @return An allocation object with the results of the algorithm.
    */
   Allocation scenario3();

private:
   /** Resets all the values needed for the scenario's algorithms.**/
   void initValues();

   /**
    * Try to allocate a delivery on the already in use couriers.
    * @param delivery A Delivery object to be allocated.
    * @return Returns true if the delivery was successful allocated in the used couriers.
    */
   bool getFirstFitUsed(const Delivery& delivery);

   /**
    * Try to find a new courier to allocate a delivery.
    * @param available_couriers The list of available couriers order by priority.
    * @param delivery A Delivery object to be allocated.
    * @return Returns true if the delivery was successful allocated and a new courier is used.
    */
   bool getFirstFitNew(std::list<Courier>& available_couriers, Delivery& delivery);

   /**
    * Try to allocate an express delivery on the company's courier.
    * @param delivery A Delivery object to be allocated.
    * @param courier The courier being used.
    * @return Returns true if the express delivery was successful allocated in the company's courier.
    */
   bool insertExpressDelivery(Delivery& delivery);

   /**
    * Get all the deliveries for the next day.
    */
   void setNextDeliveries();

   Allocation allocation;
   std::vector<Courier> couriers;
   std::vector<Delivery> deliveries;
   std::vector<Delivery> daily_deliveries;
   int current_day;
   int deliveries_per_day;
   int time_available;

    int knapSack(std::vector<Delivery> &deliveries_copy, Courier &courier);
};


#endif
