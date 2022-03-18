#### CMPT305 - Project 1

Members: Pashan Irani, Divij Gupta & Manav Meghpara

![Makefile CI](https://github.com/PashanIrani/CMPT305-Project1/actions/workflows/build-check.yml/badge.svg?branch=master)

# Discrete Event Simulation of a Major Hospital's Emergency Department

## Components

### Emergency Departent

-   **B** total patients
-   **R** single-occupancy patient rooms
-   **B - R** patients inn waiting area

If capacity is full, patients are transferred to a different hospital (turned away).

### Patient classification

1. High-Priority: Patients with critical or life-threatening conditions
2. Medium Priority: Adult patients with high pain levels and children with medium to high pain levels (but not life-threatening)
3. Low Priority: All other patients with medium to low pain levels for adults, and low pain levels for children

## Systems

### Init

1. Generate all times based 1/lambas for each priority and put _patients_ in queue.

### "m1" Nurses System

Arrival: Initial arrival times for patients
Service: 1/mu_e (exponential)
Departure: Patients will enter **"mR" Rooms System**

### "mR" Rooms System

Arrival: Patients will arrive in priority queue (ordered by patient classification and then arrival time) from **"m1" Nurses**'s depatures.
Service: 1/mu_h or 1/mu_m or 1/mu_l (exponetial) times
Departures: Patients will leave... (calculate results), add "room" to **"m2" janitor System**

### "m2" janitor System

Arrival: Rooms will arrive based on their respective patient's departure time.
Service: 1/mu_c (exponential)
Departure: Room will be marked as "cleaned" and ready to intake new patients in **"mR" Rooms System**
