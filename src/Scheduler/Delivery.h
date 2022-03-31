#ifndef DELIVERY_H
#define DELIVERY_H

/**
 * Represent deliveries with specification. Samples in deliveries.csv
 */
class Delivery {
public:
   Delivery() = default;

   Delivery(const int& volume, const int& weight, const int& compensation, const int& duration);
private:
   int volume;
   int weight;
   int compensation;
   int duration;

};

#endif
