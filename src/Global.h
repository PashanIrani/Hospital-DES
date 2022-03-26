#include "Room.h"
#pragma once

/* A class which holds data needed by all systems */
class Global {
  public:
    double clock = 0.0;
    double totalWaitE = 0.0;
    int m1=2;
    int R=1;
    int m2=3;
    Room* rooms; // TODO:  make objects and make global
    Global (): rooms(new Room[R]){
      Room* last = &rooms[R];
      int i = 0;
      for (Room* cur = rooms; cur!=last; ++cur){
        cur->roomId = i;
        cur->isAvailable = true;
      }
    }
    int getFreeRoom(){
      Room* last = &rooms[R];
      for (Room* cur = rooms; cur!=last; ++cur){
        if(cur->isAvailable)
          return cur->roomId;
      }
      return -1; //not available
    }
    ~Global (){delete rooms;}
};