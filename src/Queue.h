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
};

/*
 * Allocate memory for a node of type struct QueueNode and
 * initialize it with the item value and its arrival_time;
 * Return a pointer to the new node.
 */
template <class T>
struct QueueNode<T>* CreateNode(T * item) {
    struct QueueNode<T> *newNode = (struct QueueNode<T> *)malloc(sizeof(struct QueueNode<T>)); // allocates new node
    newNode->item = item;
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
    struct QueueNode<T> *newNode = CreateNode(item);
    // if the inserting item is the first one to be inserted
    if (q->head==NULL){
        q->head = newNode;
        q->tail = newNode;
        return;
    }
    q->tail->next = newNode;  //Inset after the last element (tail)
    q->tail = newNode;
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
    if(q->head == NULL)  //if no element inside queue exit 
        return NULL;
    else if (q->head->next == NULL){ // if only one element inside queue assign head and tail to NULL and delete
        struct QueueNode<T> *temp = q->head;
        q->head = NULL;
        q->tail = NULL;
        T * return_item = temp->item;
        free(temp);          //free the node
        return return_item;  // return the deleted item
    }
    struct QueueNode<T> *temp = q->head;
    q->head = q->head->next;

    T * return_item = temp->item;
    free(temp);           //free the node
    return return_item;   //return the deleted item
}

/*
 * Count the current number of nodes in the queue.
 * Return 0 if the queue is empty, i.e., head == tail == NULL
 */
template <class T>
double CountNodes(struct Queue<T> *q) {
    if(q->head == NULL)  //No element return 0
        return 0;
    int count = 0;
    struct QueueNode<T> *iter = q->head;  //starts from head and count till the end (tail)
    while(iter!=NULL){
        iter = iter->next;
        count++;
    }
    return count;
}

// Free all the Nodes in the queue
template <class T>
void FreeNodes(struct Queue<T> *q) {
    if (q->head == NULL) return;  // No elements to free

    struct QueueNode<T> *iter = q->head;
    while (iter != NULL) {    // iterate to free all elements
        struct QueueNode<T> *temp = iter;
       iter = iter->next; 
       free(temp);   //deallocates the space (memory)
    }
}

#endif
