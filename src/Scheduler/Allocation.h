#ifndef ALLOCATION_H
#define ALLOCATION_H

#include "Courier.h"
#include "Delivery.h"

#include <iostream>
#include <vector>


class Allocation {
public:
   /** Allocation's default constructor. **/
   Allocation() = default;

   /**
    * ostream operator for Allocation.
    * @param os Output stream.
    * @param allocation Allocation object.
    * @return Outputs the allocation object in a formatted way.
    */
   friend std::ostream& operator<<(std::ostream& os, const Allocation& allocation);

   /**
    * Add weight to the allocation's weight values.
    * @param used_weight The total weight used.
    * @param total_weight The total weight from all the used vans.
    */
   void addWeight(const int& used_weight, const int& total_weight);

   /**
    * Add volume to the allocation's volume values.
    * @param used_volume The total volume used.
    * @param total_volume The total volume from all the used vans.
    */
   void addVolume(const int& used_volume, const int& total_volume);

   /**
    * Update the profit values.
    * @param reward Total reward from deliveries.
    * @param cost Total cost from couriers.
    */
   void addProfit(const int& reward, const int& cost);

   /**
    * Add a delivery to the allocation values.
    * @param delivery Delivery object.
    */
   void addDelivery(const Delivery& delivery);

   /**
    * Add a courier to the used ones.
    * @param courier Courier object.
    */
   void addCourier(const Courier& courier);

   /**
    * Set the Allocation's weight values.
    * @param used_weight The total weight used.
    * @param total_weight The total weight from all the used vans.
    */
   void setWeight(const int& used_weight, const int& total_weight);

   /**
    * Set the Allocation's volume values.
    * @param used_weight The total volume used.
    * @param total_weight The total volume from all the used vans.
    */
   void setVolume(const int& used_volume, const int& total_volume);

   /**
    * Update the profit values.
    * @param reward Total reward from deliveries.
    * @param cost Total cost from couriers.
    */
   void setProfit(const int& reward, const int& cost);

   /**
    * Clear the allocation's value to default.
    */
   void clear();

   /**
    * Get the couriers used for the allocation.
    * @return Vector of Courier objects.
    */
   std::vector<Courier>& getUsedCouriers();

   /**
    * Get the non delivered Deliveries.
    * @return Vector with non delivered Deliveries.
    */
   std::vector<Delivery>& getNonDelivered();

   /**
    * Remove the couriers that are not generating profit.
    */
   void clearLosingCouriers();


   void clearLosingCouriersAux(const Courier& courier);

private:
   /**
    * Count the total number of deliveries.
    * @return Integer with the total amount of allocated deliveries.
    */
   int getDeliveriesCount() const;

   /**
    * Get the percentage of delivered packages.
    * @return Integer representing the percentage of packages delivered.
    */
   int getDeliveriesRatio() const;

   int used_weight;
   int total_weight;
   int used_volume;
   int total_volume;
   int reward;
   int cost;
   std::vector<Courier> couriers;
   std::vector<Delivery> non_delivered;
};


#endif
