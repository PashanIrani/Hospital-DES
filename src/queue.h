// FCFS Queue header file
#include <iostream>

#ifndef QUEUE_H_
#define QUEUE_H_

template <class T>
struct QueueNode {
    T * item;             // customer information
    struct QueueNode<T> *next;  // next customer in line; NULL if this is the last customer
};

template <class T>
struct Queue {
    struct QueueNode<T>* head;    // Pointer to queue head: next node to be served
    struct QueueNode<T>* tail;    // Pointer to queue tail: last node to be inserted
    double service_time;       // service time required to serve each customer in the queue
    double arrival_count;      // Total number of arrivals in the queue
    double departure_count;    // Total number of departures from the queue
};

/*
 * Allocate memory for a node of type struct QueueNode and
 * initialize it with the item value and its arrival_time;
 * Return a pointer to the new node.
 */
template <class T>
struct QueueNode<T>* CreateNode(T item, double arrival_time) {
    struct QueueNode<T> *newNode = (struct QueueNode<T> *)malloc(sizeof(struct QueueNode<T>));
    newNode->item = item;
    newNode->arrival_time = arrival_time;
    newNode->next = NULL;
    return newNode;
}

/*
 * Insert node with specified item and arrival time at the tail of the list.
 * If the queue is empty, then both the head and the tail should point to the new node
 * Should increment the arrival_count of the queue
 */
template<class T>
void Insert(struct Queue<T> *q, T * item) {
    struct QueueNode<T> *newNode = (struct QueueNode<T> *)malloc(sizeof(struct QueueNode<T>));
    newNode->item = item;
    newNode->next = NULL;
    q->arrival_count += 1;
    if (q->head==NULL){
        q->head = newNode;
        q->tail = newNode;
        q->arrival_count+=1;
        return;
    }
    q->tail->next = newNode;
    q->tail = newNode;
    q->arrival_count+=1;
}

/*
 * Delete node from head of the list and free its allocated memory
 * head pointer should move to the next node in the list. 
 * If head == NULL, do nothing
 * If the queue has one node, then both the head and the tail should point to NULL after the node is deleted
 * Should decrement the arrival_count of the queue
 */
template <class T>
T * Delete (struct Queue<T> *q) {
    if(q->head == NULL)
        return NULL;
    else if (q->head->next == NULL){
        struct QueueNode<T> *temp = q->head;
        q->head = NULL;
        q->tail = NULL;
        q->arrival_count-=1;
        q->departure_count+=1;
        T * return_item = temp->item;
        free(temp);
        return return_item;
    }
    struct QueueNode<T> *temp = q->head;
    q->head = q->head->next;
  
    q->arrival_count-=1;
    q->departure_count+=1;

    T * return_item = temp->item;
    free(temp);  
    return return_item;
}

/*
 * Count the current number of nodes in the queue.
 * Return 0 if the queue is empty, i.e., head == tail == NULL
 */
template <class T>
double CountNodes(struct Queue<T> *q) {
    if(q->head == NULL)
        return 0;
    int count = 0;
    struct QueueNode<T> *iter = q->head;
    while(iter!=NULL){
        iter = iter->next;
        count++;
    }
    return count;
}

#endif
