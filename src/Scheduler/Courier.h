#ifndef COURIER_H
#define COURIER_H

#include <string>
#include <sstream>

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
    * Get the courier's van weight.
    * @return Integer with the van's weight.
    */
   int getWeight() const;

   /**
<<<<<<< HEAD
    * Get the price per capacity of the van.
    * @return Double with the amount of space per cost unit.
    */
   double getCostRatio() const;

   /**
    * Get the capacity of a van considering volume and weight.
    * @return Sum of with and volume.
    */
    int getCapacity() const;
private:
   int cost;
   int volume;
   int weight;

};

#endif