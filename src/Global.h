#include "Room.h"
#pragma once

/* A class which holds data needed by all systems */
class Global {
  public:
    // Enables debug prints
    bool const DEBUG = true;

    // holds current time of system
    double clock = 0.0;

    double totalWaitE = 0.0;
    
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