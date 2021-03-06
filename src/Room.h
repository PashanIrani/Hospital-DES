
#pragma once

class Room {
    public:
        
        /*stores the room number*/
        double roomId;

        /*true means available to use and false otherwise*/
        bool isAvailable;

        /*Service time for room cleanup*/
        double service_time;

        /* Stores the time this room needed to be cleaned */
        double needed_cleanup_time; 
};

