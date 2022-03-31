#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <iomanip>
#include <set>
#include <vector>

#include "App.h"

class App;

class State {
public:
   /**
    * State's main method. Calls display and step.
    * @param app Pointer to the main application.
    */
   void run(App* app);

protected:
   /**
    * Reads an integer until valid input.
    * @param app Pointer to the main application.
    * @return - Returns an integer from user input.
    */
   int readOption(App* app) const;

   /**
    * Print a page break;
    */
   void printBreak() const;

   /**
   * Outputs the invalid option message to the console.
   */
   void printInvalidOption() const;

   /**
    * Handle the specific events in each state.
    * @param app Pointer to the main application.
    */
   virtual void step(App* app) {}

private:

};


#endif