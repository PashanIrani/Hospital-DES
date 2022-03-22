#include "queue.h"
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

/*
 * Allocate memory for a node of type struct QueueNode and
 * initialize it with the item value and its arrival_time;
 * Return a pointer to the new node.
 */
template <class T>
struct QueueNode* CreateNode(T item, double arrival_time) {
    struct QueueNode *newNode = (struct QueueNode *)malloc(sizeof(struct QueueNode));
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
template <class T>
void Insert (struct Queue *q, T item, double arrival_time) {
    struct QueueNode *newNode = (struct QueueNode *)malloc(sizeof(struct QueueNode));
    newNode->item = item;
    newNode->arrival_time = arrival_time;
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
void Delete (struct Queue *q) {
    if(q->head == NULL)
        return;
    else if (q->head->next == NULL){
        free(q->head);
        q->head = NULL;
        q->tail = NULL;
        q->arrival_count-=1;
        q->departure_count+=1;
        return;
    }
    struct QueueNode *temp = q->head;
    q->head = q->head->next;
    free(temp);
    q->arrival_count-=1;
    q->departure_count+=1;
}

/*
 * Count the current number of nodes in the queue.
 * Return 0 if the queue is empty, i.e., head == tail == NULL
 */
template <class T>
double CountNodes (struct Queue *q) {
    if(q->head == NULL)
        return 0;
    int count = 0;
    struct QueueNode *iter = q->head;
    while(iter!=NULL){
        iter = iter->next;
        count++;
    }
    return count;
}

/*
 * Return the first node holding the value item
 * return NULL if none found
 */
template <class T>
struct QueueNode* FindNode(struct Queue *q, T item) {
    struct QueueNode *iter = q->head;
    while(iter!=NULL){
        if(iter->item==item)
            return iter;
        iter=iter->next;
    }
    return NULL;
}

/*
 * Return a pointer to first node that has an arrival time >= t
 * For example, in the queue head:{1,4}, {2, 80}, {3, 500}, {4, 510}, tail:{5, 640}
 * FindNodeAfterTime(q, 505) returns a pointer to QueueNode {4, 510}
 * FindNodeAfterTime(q, 80) returns a pointer to QueueNode {2, 80}
 */
template <class T>
struct QueueNode* FindNodeAfterTime(struct Queue *q, double t) {
    struct QueueNode *iter = q->head;
    while(iter!=NULL){
        if(iter->arrival_time>= t)
            return iter;
        iter=iter->next;
    }
    return NULL;
}

/*
 * Return the count of all nodes that have an arrival time >= t
 * For example, in the queue head:{1,4}, {2, 80}, {3, 500}, {4, 510}, tail:{5, 640}
 * CountNodesAfterTime(q, 505) returns 2
 * CountNodesAfterTime(q, 80) returns 4
 */
template <class T>
double CountNodesAfterTime(struct Queue *q, double t) {
    struct QueueNode *iter = q->head;
    int count = 0;
    while(iter!=NULL){
        if(iter->arrival_time>= t)
            count++;
        iter=iter->next;
    }
    return count;
}



