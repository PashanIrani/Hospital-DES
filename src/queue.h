// FCFS Queue header file

#ifndef QUEUE_H_
#define QUEUE_H_

#ifndef uint64
    #define uint64 unsigned long
#endif

struct QueueNode {
    int item;             // customer information
    uint64 arrival_time;  // arrival time for customer
    struct QueueNode *next;  // next customer in line; NULL if this is the last customer
};

struct Queue {
    struct QueueNode* head;    // Pointer to queue head: next node to be served
    struct QueueNode* tail;    // Pointer to queue tail: last node to be inserted
    uint64 service_time;       // service time required to serve each customer in the queue
    uint64 arrival_count;      // Total number of arrivals in the queue
    uint64 departure_count;    // Total number of departures from the queue
};

/*
 * Allocate memory for a node of type struct QueueNode and
 * initialize it with the item value and its arrival_time;
 * Return a pointer to the new node.
 */
struct QueueNode* CreateNode(int item, uint64 arrival_time);

/*
 * Insert node with specified item and arrival time at the tail of the list.
 * If the queue is empty, then both the head and the tail should point to the new node
 * Should increment the arrival_count of the queue
 */
void Insert (struct Queue *q, int item, uint64 arrival_time);

/*
 * Delete node from head of the list and free its allocated memory
 * head pointer should move to the next node in the list. 
 * If head == NULL, do nothing
 * If the queue has one node, then both the head and the tail should point to NULL after the node is deleted
 * Should decrement the arrival_count of the queue
 */
void Delete (struct Queue *q);

/*
 * Count the current number of nodes in the queue.
 * Return 0 if the queue is empty, i.e., head == tail == NULL
 */
uint64 CountNodes (struct Queue *q);

/*
 * Return the first node holding the value item
 * return NULL if none found
 */
struct QueueNode* FindNode(struct Queue *q, int item);

/*
 * Return a pointer to first node that has an arrival time >= t
 * For example, in the queue head:{1,4}, {2, 80}, {3, 500}, {4, 510}, tail:{5, 640}
 * FindNodeAfterTime(q, 505) returns a pointer to QueueNode {4, 510}
 * FindNodeAfterTime(q, 80) returns a pointer to QueueNode {2, 80}
 */
struct QueueNode* FindNodeAfterTime(struct Queue *q, uint64 t);

/*
 * Return the count of all nodes that have an arrival time >= t
 * For example, in the queue head:{1,4}, {2, 80}, {3, 500}, {4, 510}, tail:{5, 640}
 * CountNodesAfterTime(q, 505) returns 2
 * CountNodesAfterTime(q, 80) returns 4
 */
uint64 CountNodesAfterTime(struct Queue *q, uint64 t);




#endif
