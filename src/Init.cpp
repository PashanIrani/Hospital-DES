#include "Init.h"
#include <iostream>
#include <algorithm>

/* Initializes Init class;
* initializes a singular generator with a seed, that will be used for all random numbers for this Init instance
*/
Init::Init(int seed) {
    this->generator = new std::default_random_engine(seed);
}

Init::~Init() {
    delete generator;
}

NumberGenerator * Init::getNumberGenerator(double variable) {
    return new NumberGenerator(generator, variable);
}

Patient** Init::generatePatientsOfClassification(double lambda, int* numPatients, PatientClassification classification) {
    NumberGenerator* ng = new NumberGenerator(generator, lambda);

    int num = 1;
    Patient** patientQueue = (Patient**) malloc(sizeof(Patient*) * num);

    double lastArrival = 0;
    int i = 0;
    
    while (lastArrival < 1440) {
        if (i >= num) {
            patientQueue = (Patient **) realloc(patientQueue, sizeof(Patient *) * (num*2));
            num *= 2;
        }

        lastArrival += ng->next();
        patientQueue[i] = new Patient(lastArrival, classification);
        i++;
    }
    *numPatients = i;

    delete ng;
    return patientQueue;
}

void Init::deleteQueue(Patient** arr, int size) {
    for (int i = 0; i < size; i++) {
        delete arr[i];
    }
    delete arr;
}

/* Returns an array of patients that will be "entering" the "hospital" */
Patient** Init::recieve_patients(double lambda_high, double lambda_med, double lambda_low) {

    int *total_highPatients = (int*) malloc(sizeof (int));
    int *total_medPatients = (int*) malloc(sizeof (int));
    int *total_lowPatients = (int*) malloc(sizeof (int));
   
    // Initialize patients for each classification
    Patient** highPriorityPatients = generatePatientsOfClassification(lambda_high, total_highPatients, HIGH);
    Patient** medPriorityPatients = generatePatientsOfClassification(lambda_med, total_medPatients, MEDIUM);
    Patient** lowPriorityPatients = generatePatientsOfClassification(lambda_low, total_lowPatients, LOW);
    
    totalPatients = *total_highPatients + *total_medPatients + *total_lowPatients;

    // Creating array to store the patients
    patients = (Patient **)malloc(sizeof(Patient *) * totalPatients);

    // merging highPriorityPatients and medPriorityPatients in a tempArray
    int totalHighAndMedPatients = *total_medPatients + *total_highPatients;
    Patient** tempArray = (Patient **)malloc(sizeof(Patient *) * totalHighAndMedPatients);
    int highCount = 0;
    int medCount = 0;
    int i = 0;

    while (medCount < *total_medPatients && highCount < *total_highPatients) {
        if (highPriorityPatients[highCount]->arrival_time < medPriorityPatients[medCount]->arrival_time) {
            tempArray[i] = highPriorityPatients[highCount];
            highCount++;
        }
        else {
            tempArray[i] = medPriorityPatients[medCount];
            medCount++;
        }
        i++;
    }
    if (medCount < *total_medPatients) {
        for (; i < totalHighAndMedPatients; i++) {
            tempArray[i] = medPriorityPatients[medCount];
            medCount++;
        }
    }
    else {
        for (; i < totalHighAndMedPatients; i++) {
            tempArray[i] = highPriorityPatients[highCount];
            highCount++;
        }
    }

    // merging lowPriorityPatients and tempArray into the final patients array
    int lowCount = 0;
    int tempCount = 0;
    i = 0;
    while (lowCount < *total_lowPatients && tempCount < totalHighAndMedPatients) {
        if (lowPriorityPatients[lowCount]->arrival_time < tempArray[tempCount]->arrival_time) {
            patients[i] = lowPriorityPatients[lowCount];
            lowCount++;
            patients[i]->patientID = i;
        }
        else {
            patients[i] = tempArray[tempCount];
            tempCount++;
            patients[i]->patientID = i;
        }
        i++;
    }


    if (lowCount < *total_lowPatients) {
        for (; i < totalPatients; i++) {
            patients[i] = lowPriorityPatients[lowCount];
            lowCount++;
            patients[i]->patientID = i;
        }
    }
    else {
        for (; i < totalPatients; i++) {
            patients[i] = tempArray[tempCount];
            tempCount++;
            patients[i]->patientID = i;
        }
    }

    // Free temp arrays 
    free(highPriorityPatients);
    free(medPriorityPatients);
    free(lowPriorityPatients);
    free(tempArray);

    free(total_highPatients);
    free(total_medPatients);
    free(total_lowPatients);
    
    return patients;
}
