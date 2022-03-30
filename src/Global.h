#include "Room.h"
#pragma once

/* A class which holds data needed by all systems */
class Global {
  public:
    // Enables debug prints
    bool const DEBUG = false;

    // holds current time of system
    double clock = 0.0;

    // Wait time in E(evaluation) queue 
    double totalWaitE = 0.0;

    // Wait time in P(patient treatment) queue
    double totalWaitP = 0.0;

    // Wait time for high patients P(patient treatment) queue
    double totalHighWaitP = 0.0;

    // Wait time in medium patients P(patient treatment) queue
    double totalMedWaitP = 0.0;

    // Wait time in low patients P(patient treatment) queue
    double totalLowWaitP = 0.0;
    
    // Wait time for cleanup of rooms
    double totalWaitR = 0.0;

    // Rooms Cleaned
    int totalRoomsCleaned = 0;

    // Total response time for each departing patients
    double totalResponseSum = 0.0;

    // Total response time for each high departing patients
    double totalHighResponseSum = 0.0;

    // Total response time for each med departing patients
    double totalMedResponseSum = 0.0;
    
    // Total response time for each low departing patients
    double totalLowResponseSum = 0.0;
    
    // Total Number of patients in waiting + treatment
    int total_patients = 0;

    // Total patients leave because system is at capacity
    int total_leaving_patients = 0;

    // Holds the number of patients that left the system
    int total_departed_patients = 0;
    
    // Holds the number of high patients that left the system
    int total_high_departed_patients = 0;

    // Holds the number of medium patients that left the system
    int total_med_departed_patients = 0;

    // Holds the number of low patients that left the system
    int total_low_departed_patients = 0;

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
    
    // The minute the hospital should close
    double terminating_time = 24 * 60;

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

    void printStats() {
        std::string space = " ";
        std::cout << "Stats for Minute " << (int) clock << ": " << std::endl;
        std::cout << space << "Total Departures: " << total_departed_patients << std::endl;
        std::cout << space << "Average # of Patients in System: " << sumOfTotalPatients / numOfTimeClockUpdated << std::endl;
        // std::cout << space << "Current Capcity: " << total_patients << " ("<< ((double) total_patients / (double) B) * 100.0 << "%)" << std::endl;
        std::cout << space << "Average Response Time [ALL]: " << totalResponseSum / total_departed_patients << " mins" << std::endl;
        std::cout << space << "Average Response Time [HIGH]: " << totalHighResponseSum / total_high_departed_patients << " mins" << std::endl;
        std::cout << space << "Average Response Time [MEDIUM]: " << totalMedResponseSum / total_med_departed_patients << " mins" << std::endl;
        std::cout << space << "Average Response Time [LOW]: " << totalLowResponseSum / total_low_departed_patients << " mins" << std::endl;
        std::cout << space << "Average Waiting Time (E): " << totalWaitE / total_departed_patients << " mins" << std::endl;
        std::cout << space << "Average Waiting Time (P) [ALL]: " << totalWaitP / total_departed_patients << " mins" << std::endl;
        std::cout << space << "Average Waiting Time (P) [HIGH]: " << totalHighWaitP / total_high_departed_patients << " mins" << std::endl;
        std::cout << space << "Average Waiting Time (P) [MEDIUM]: " << totalMedWaitP / total_med_departed_patients << " mins" << std::endl;
        std::cout << space << "Average Waiting Time (P) [LOW]: " << totalLowWaitP / total_low_departed_patients << " mins" << std::endl;
        std::cout << space << "Average Cleanup Time: " << totalWaitR / totalRoomsCleaned << " mins" << std::endl;
        std::cout << space << "# of patients who left because system was at full capacity: " << total_leaving_patients << std::endl;
        std::cout << std::endl;
    } 

    void updateClock(double newTime) {
      clock = newTime;

      numOfTimeClockUpdated++; // count the number of times the clock was updated
      sumOfTotalPatients += total_patients; // sum of total patients, so we can later calculate the average

      if ((int) clock == lastPrintHour + 60) {
        printStats();
        lastPrintHour = (int) clock;
      }
    }
    
    ~Global (){
      delete[] rooms;
    }

    private:
      int lastPrintHour = 0;  
      int sumOfTotalPatients = 0;
      int numOfTimeClockUpdated = 0;
};