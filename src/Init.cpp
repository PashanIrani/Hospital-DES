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
    //dequeue(patients);
}

NumberGenerator * Init::getNumberGenerator(double variable) {
    return new NumberGenerator(generator, variable);
}

Patient** Init::generatePatientsOfClassification(double lambda, int numPatients, PatientClassification classification) {
    NumberGenerator* ng = new NumberGenerator(generator, lambda);

    Patient** patientQueue = (Patient**) malloc(sizeof(Patient*) * numPatients);

    // todo: look into it
    //Patient* patient = (Patient*) malloc(sizeof (Patient) * totalPatients);

    double lastArrival = 0;
    for (int i = 0; i < numPatients; i++) {
        lastArrival += ng->next();
        patientQueue[i] = new Patient(lastArrival, classification);
    }
    return patientQueue;
}

void Init::deleteQueue(Patient** arr, int size) {
    for (int i = 0; i < size; i++) {
        delete arr[i];
    }
    delete arr;
}

Patient* Init::dequeue(Patient** patientList) {
    // assume that patient list is not empty
}

/* Returns an array of patients that will be "entering" the "hospital" */
Patient** Init::recieve_patients(int n) {

    double lambda_high = 2; // 2 high priority patients every hour or 1 high priority patient every 30 mins
    double lambda_med = 4;  // 4 med priority patients every hour or 1 med priority patient every 15 mins
    double lambda_low = 6;  // 6 low priority patients every hour or 1 low priority patient every 10 mins

    /*// total number of possible patients to arrive in 24 hours
    int total_highPatients = lambda_high * 24 * 2;
    int total_medPatients = lambda_med * 24 * 2;
    int total_lowPatients = lambda_low * 24 * 2;*/

    // total number of possible patients to arrive in 24 hours
    int total_highPatients = lambda_high * 10;
    int total_medPatients = lambda_med * 12;
    int total_lowPatients = lambda_low * 13;

    totalPatients = total_highPatients + total_medPatients + total_lowPatients;

    // Creating array to store the patients
    patients = (Patient **)malloc(sizeof(Patient *) * totalPatients);

    Patient** highPriorityPatients = generatePatientsOfClassification(lambda_high, total_highPatients, HIGH);
    Patient** medPriorityPatients = generatePatientsOfClassification(lambda_med, total_medPatients, MEDIUM);
    Patient** lowPriorityPatients = generatePatientsOfClassification(lambda_low, total_lowPatients, LOW);

    // std::cout << "------------Low priority patients ------------" << std::endl;
    // for (int i = 0; i < total_lowPatients; i++) {
    //     lowPriorityPatients[i]->print();
    // }
    // std::cout << "------------Medium priority patients ------------" << std::endl;
    // for (int i = 0; i < total_medPatients; i++) {
    //     medPriorityPatients[i]->print();
    // }
    // std::cout << "------------High priority patients ------------" << std::endl;
    // for (int i = 0; i < total_highPatients; i++) {
    //     highPriorityPatients[i]->print();
    // }

    // merging highPriorityPatients and medPriorityPatients in a tempArray
    int totalHighAndMedPatients = total_medPatients + total_highPatients;
    Patient** tempArray = (Patient **)malloc(sizeof(Patient *) * totalHighAndMedPatients);
    int highCount = 0;
    int medCount = 0;
    int i = 0;
    while (medCount < total_medPatients && highCount < total_highPatients) {
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
    if (medCount < total_medPatients) {
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
    while (lowCount < total_lowPatients && tempCount < totalHighAndMedPatients) {
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


    if (lowCount < total_lowPatients) {
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


    // std::cout << "------------Final patients array ------------" << std::endl;
    // for (int i = 0; i < totalPatients; i++) {
    //     patients[i]->print();
    //     std::cout << patients[i]->patientID << std::endl;;
    // }

    // std::cout << total_lowPatients << ", " << total_medPatients << ", " << total_highPatients << ", " << totalPatients << std::endl;

    /*deleteQueue(highPriorityPatients, total_highPatients);
    deleteQueue(medPriorityPatients, total_medPatients);
    deleteQueue(lowPriorityPatients, total_lowPatients);
    deleteQueue(tempArray, totalHighAndMedPatients);*/

    return patients;
}
