#include <iostream>
#include <stdio.h>
#include "PriorityQueue.h"

int main()
{
    PriorityQueue *pq = new PriorityQueue();
    for (int i = 0; i < 10; ++i)
    {
        Vertex v = {i, 20 - i};
        printf("Insert( {key: %i, distance: %f} )\n", v.id, (float) v.distance);
        pq->insert( v );
    }
    pq->print();
    pq->set_distance(0, 0);
    pq->print();
    for (int j = 0; j < 10; ++j)
    {
        Vertex v = pq->extract_min();
        printf("extract_min() -> { id: %i, distance: %f }\n", v.id, (float) v.distance);
        pq->print();
    }
    return 0;
}
