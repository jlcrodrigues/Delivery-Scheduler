#ifndef APP_H
#define APP_H

#include <set>

#include "../src/Scheduler/Scheduler.h"
#include "State.h"

class State;

class App
{
public:
   /**
    * App's default constructor. Starts everything needed for the program.
    */
   App();

   /**The application main loop.**/
   void run();

   /**
    * Get the app's scheduler object.
    * @return Pointer to the app's scheduler.
    */
   Scheduler* getScheduler() const;

   /**
    * Reset the scheduler.
    */
   void resetScheduler();

   /**
    * Change the app's current state.
    * @param state Any state derived class.
    */
   void setState(State* state);

private:
   Scheduler* scheduler;
   State* state;
};


#endif