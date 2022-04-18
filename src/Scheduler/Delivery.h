#ifndef DELIVERY_H
#define DELIVERY_H

#include <string>
#include <sstream>

/**
 * Represent deliveries with specification. Samples in deliveries.csv
 */
class Delivery {
public:
   /** Delivery's default constructor. **/
   Delivery() = default;

   /**
    * Constructor for delivery.
    * @param volume The volume of the package.
    * @param weight The weight of the package.
    * @param compensation The reward for the delivery.
    * @param duration The expected duration of delivery.
    */
   Delivery(const int& volume, const int& weight, const int& compensation, const int& duration);

   /**
    * Construct a Delivery object from a csv row.
    * @param row A string of the object's attributes separated by commas.
    */
   Delivery(const std::string& row);

   /**
    * Load a Delivery object from a csv row.
    * @param row A string of the object's attributes separated by commas.
    */
   void loadFromCsv(const std::string& row);

   /**
    * Get the delivery's reward.
    * @return Integer with the money that will be made with this delivery.
    */
   int getCompensation() const;

   /**
    * Get the delivery's expected duration.
    * @return Integer with the delivery's duration.
    */
   int getDuration() const;

   /**
    * Get the package's volume.
    * @return Integer with the total volume of the package.
    */
   int getVolume() const;

    /**
    * Get the package's weight.
    * @return Integer with the total weight of the package.
    */
   int getWeight() const;

   /**
    * Get the compensation per size ratio.
    * @return Double with the cost per spacing.
    */
   double getCompensationRatio() const;

   /**
    * Get capacity of delivery considering volume and weight.
    * @return Sum of volume and weight.
    */
    float getCapacity() const;
private:
    int compensation;
    int duration;
    int volume;
    int weight;

};

#endif
