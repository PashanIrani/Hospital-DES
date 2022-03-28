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

    /*
    Command Line Arguments
    */
    // inter-arrival mean value for high priority patients
    double lambda_high = 0.0;
    
    // inter-arrival mean value for med priority patients
    double lambda_med = 0.0;

    // inter-arrival mean value for low priority patients
    double lambda_low = 0.0;
    
    // mean treatment time for high priority patients
    double mu_high = 0.0;

    // mean treatment time for med priority patients
    double mu_med = 0.0;

    // mean treatment time for low priority patients
    double mu_low = 0.0;

    // mean evalutation time for all patients
    double mu_evaluation = 0.0;

    // mean cleanup time for rooms 
    double mu_cleanup = 0.0;
    
    // Capacity of patients in emergency room + waiting area
    int B = 0;

    // Indicates the number of Rooms in the System
    int R=3;
  
    // Indicates the number of nurses in the system
    int m1=2;
      
    // Indicates the number of Cleaners in the System
    int m2=3;

    // Seed for random generation    
    int seed = 0;
    
    // Rooms in the system
    Room* rooms; // TODO:  make objects and make global
    
    // inits an array of rooms; assigns it's id and it's availability is set to true
    void initRooms() {
      this->rooms = new Room[R];
      for (int i=0; i<R; i++){
        (rooms+i)->roomId= i;
        (rooms+i)->isAvailable = true;
      }
    }
    // Returns a free Room    
    Room* getFreeRoom(){
      // iterate through rooms until once is available, and return that
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