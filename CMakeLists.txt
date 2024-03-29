cmake_minimum_required(VERSION 3.10)
project(delivery-scheduler)

set(CMAKE_CXX_STANDARD 11)

set(CREATE_EXE TRUE)

set(SOURCE_FILES
        src/App/App.cpp
        src/App/App.h
        src/App/ChooseSceneryState.cpp
        src/App/ChooseSceneryState.h
        src/App/InitialState.cpp
        src/App/InitialState.h
        src/App/NoDeliveriesState.cpp
        src/App/NoDeliveriesState.h
        src/App/Scenery1State.cpp
        src/App/Scenery1State.h
        src/App/Scenery2State.cpp
        src/App/Scenery2State.h
        src/App/Scenery3State.cpp
        src/App/Scenery3State.h
        src/App/SettingsState.cpp
        src/App/SettingsState.h
        src/App/State.cpp
        src/App/State.h

        src/Scheduler/Allocation.cpp
        src/Scheduler/Allocation.h
        src/Scheduler/Courier.cpp
        src/Scheduler/Courier.h
        src/Scheduler/Delivery.cpp
        src/Scheduler/Delivery.h
        src/Scheduler/Scheduler.cpp
        src/Scheduler/Scheduler.h
        )


set(TEST_FILES
        tests/Scenery1Test.cpp src/App/Scenery1State.cpp src/App/Scenery1State.h)

include_directories(src)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_subdirectory(tests/googletest)
    include_directories(tests/googletest/googletest/include)
    include_directories(tests/googletest/googlemock/include)

    add_executable(${CMAKE_PROJECT_NAME}_run mainTest.cpp ${TEST_FILES} ${SOURCE_FILES})

    target_link_libraries(${CMAKE_PROJECT_NAME}_run gtest gtest_main)
    message("Debug mode")
endif()

if (CMAKE_BUILD_TYPE MATCHES Release)
    add_executable(${CMAKE_PROJECT_NAME}_run main.cpp ${SOURCE_FILES})
    message("Release mode")
endif()