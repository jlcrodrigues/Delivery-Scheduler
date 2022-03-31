#ifndef COURIER_H
#define COURIER_H

/**
 * Each courier has a van with specific attributes. Vans are stored in vans.csv.
 */
class Courier {
public:
   Courier() = default;

   Courier(const int& volume, const int& weight, const int& cost);
private:
   int volume;
   int weight;
   int cost;
};

#endif