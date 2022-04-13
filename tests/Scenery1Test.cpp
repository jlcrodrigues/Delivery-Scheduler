#include <iostream>
#include <gtest/gtest.h>

#include "Scheduler/Courier.h"
#include "Scheduler/Delivery.h"
#include "Scheduler/Scheduler.h"
#include "App/ChooseSceneryState.h"



TEST(scenery1, binPacking)
{
   App app;
   app.getScheduler()->loadCouriers("data/vansTest.csv");
   app.getScheduler()->loadDeliveries("data/deliveriesTest.csv");


}