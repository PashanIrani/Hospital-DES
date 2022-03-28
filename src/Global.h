#include "Room.h"
#pragma once

/* A class which holds data needed by all systems */
class Global {
  public:
    // Enables debug prints
    bool const DEBUG = true;

    // holds current time of system
    double clock = 0.0;

    // Wait time in E(evaluation) queue 
    double totalWaitE = 0.0;

    // Wait time in P(patient treatment) queue
    double totalWaitP = 0.0;

    // Wait time for cleanup of rooms
    double totalWaitR = 0.0;

    // Total response time for each departing patients
    double totalResponse = 0.0;

    // Total Number of patients in waiting + treatment
    int total_patients = 0;

    // Total patients leave because system is at capacity
    int total_leaving_patients = 0;

    // Capacity of patients in emergency room + waiting area
    int B=40;
    
    // Indicates the number of nurses in the system
    int m1=2;
    
    // Indicates the number of Rooms in the System
    int R=3;
    
    // Indicates the number of Cleaners in the System
    int m2=3;
    
    // Rooms in the system
    Room* rooms; // TODO:  make objects and make global
    
    // Constructor, creates the rooms
    Global (): rooms(new Room[R]){
      for (int i=0; i<R; i++){
        (rooms+i)->roomId= i;
        (rooms+i)->isAvailable = true;
      }
    }

    // Returns a free Room    
    Room* getFreeRoom(){
      for (int i=0; i<R; i++){
        if((rooms+i)->isAvailable)
          return (rooms+i);
      }
      return NULL; //not available
    }
    

    ~Global (){
      // for (Room* cur = rooms; cur!=last; ++cur){
      //   delete cur;
      // }
      delete[] rooms;
    }
};