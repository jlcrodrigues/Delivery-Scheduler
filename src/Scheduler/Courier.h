#ifndef COURIER_H
#define COURIER_H

#include <string>
#include <sstream>
#include <vector>

/**
 * Each courier has a van with specific attributes. Vans are stored in vans.csv.
 */
class Courier {
public:
   /** Courier's default constructor. **/
   Courier() = default;

   /**
    * Constructor for Courier.
    * @param volume The courier's van's volume.
    * @param weight The courier's van's weight.
    * @param cost The amount the courier charges.
    */
   Courier(const int& volume, const int& weight, const int& cost);

   /**
    * Construct a Courier object from a csv row.
    * @param row A string of the object's attributes separated by commas.
    */
   Courier(const std::string& row);

   /**
    * Load a Courier object from a csv row.
    * @param row A string of the object's attributes separated by commas.
    */
   void loadFromCsv(const std::string& row);

   /**
    * Get the courier's cost of operation.
    * @return Integer with the courier's cost.
    */
   int getCost() const;

   /**
    * Get the courier's van volume.
    * @return Integer with the van's volume.
    */
   int getVolume() const;

    /**
     * Get vans's free Volume.
     * @return Integer with van's free volume.
     */
   int getFreeVolume() const;

    /**
     * Update van's free volume.
     * @param vol Value to subtract to free volume.
     */
   void updateFreeVolume(const int vol);

   /**
    * Get the courier's van weight.
    * @return Integer with the van's weight.
    */
   int getWeight() const;

   /**
    * Get vans's free weight.
    * @return Integer with van's free weight.
    */
   int getFreeWeight() const;

   /**
    * Update van's free weight.
    * @param w Value to subtract to free weight.
    */
   void updateFreeWeight(int w);

   /**
    * Get the price per capacity of the van.
    * @return Double with the amount of space per cost unit.
    */
   double getCostRatio() const;

   /**
    * Get van's capacity considering volume and weight.
    * @return Average of volume and weight.
    */
    float getCapacity() const;

    /**
     * Get van's free space/capacity considering volume and weight
     * @return Average of free volume and free weight.
     */
    float getFreeCapacity() const;
private:
   int cost;
   int volume;
   int weight;
   int free_weight;
   int free_volume;

};

#endif