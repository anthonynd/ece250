#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
#include <limits>
#include "Exception.h"

struct Vertex 
{
    int id;
    double distance;
};


class PriorityQueue 
{
    private:
        int queue_size;
        int capacity;
        Vertex *heap_array;
        int *index_of;

        int find( int ) const;
        int left( int ) const;
        int parent( int ) const;
        int right( int ) const;

        int bubble_up( int );
        void heapify( int );
        void swap( int, int );

    public:
        PriorityQueue( int = 50 );
        ~PriorityQueue();

        // Accessors
        bool contains( int ) const;
        Vertex get( int ) const;
        bool is_empty() const;
        void print() const;

        // Mutators
        void clear();
        Vertex extract_min();
        void initialize( int );
        void insert( Vertex );
        void insert( int, double );
        void set_distance( int, double );
};


PriorityQueue::PriorityQueue( int size ):
    queue_size( 0 ),
    capacity( size )
{
    heap_array = new Vertex[size + 1]; // 1-indexed array
    index_of = new int[size];
}

PriorityQueue::~PriorityQueue()
{
    delete [] heap_array;
    delete [] index_of;
}


int PriorityQueue::bubble_up( int new_index )
{
    if (new_index < 1 || new_index > capacity)
    {
        throw illegal_argument();
    }

    Vertex parent_vertex = heap_array[parent( new_index )];
    Vertex new_vertex = heap_array[new_index];
    while (parent_vertex.distance > new_vertex.distance && new_index > 1)
    {
        if (new_vertex.distance < parent_vertex.distance)
        {
            int parent_index = parent( new_index );
            swap( parent_index, new_index );
            new_index = parent_index; // Update to current position of the new vertex (its former parent)
        }
        parent_vertex = heap_array[parent( new_index )];
        new_vertex = heap_array[new_index];
    }
}

void PriorityQueue::clear()
{
    queue_size = 0;
    delete [] heap_array;
    delete [] index_of;
    heap_array = new Vertex[capacity + 1]; // 1-indexed array
    index_of = new int[capacity];
}

bool PriorityQueue::contains( int vertex_id ) const
{
    if (vertex_id < 0 || vertex_id >= capacity)
        return false;
    return index_of[vertex_id] > 0 && index_of[vertex_id] <= queue_size;
}

Vertex PriorityQueue::extract_min()
{
    if (queue_size <= 0)
        throw underflow();
    else
    {
        Vertex min = heap_array[1];
        index_of[min.id] = -1;
        heap_array[1] = heap_array[queue_size];
        --queue_size;
        heapify( 1 );
        return min;
    }
}

int PriorityQueue::find( int vertex_key ) const
{
    if (vertex_key >= 0 && vertex_key < capacity)
        return index_of[vertex_key];
    return -1;
}

Vertex PriorityQueue::get( int vertex_id ) const
{
    if (vertex_id < 0 || vertex_id >= capacity)
        throw illegal_argument();
    return heap_array[index_of[vertex_id]];
}

void PriorityQueue::heapify( int index )
{
    int left_index = left( index );
    int right_index = right( index );
    int smallest;

    if (left_index <= queue_size && heap_array[left_index].distance < heap_array[index].distance)
    {
        smallest = left_index;
    }
    else
    {
        smallest = index;
    }

    if (right_index <= queue_size && heap_array[right_index].distance < heap_array[smallest].distance)
    {
        smallest = right_index;
    }

    if (smallest != index)
    {
        swap( index, smallest );
        heapify( smallest );
    }
}

void PriorityQueue::initialize( int src )
{
    double INF = std::numeric_limits<double>::infinity();
    Vertex v = { 0, INF };
    for (int i = 0; i < capacity; ++i)
    {
        v.id = i;
        heap_array[i + 1] = v;
        index_of[i] = i + 1;
    }
    swap( 1, index_of[src] );
    heap_array[1].distance = 0;
    queue_size = capacity;
}

void PriorityQueue::insert( Vertex v )
{
    if (queue_size < capacity)
    {
        // Insert v at next available position in array
        int new_index = queue_size + 1;
        heap_array[new_index] = v;
        index_of[v.id] = new_index;
        ++queue_size;
        bubble_up( new_index );
    }
}

void PriorityQueue::insert( int vertex_id, double distance )
{
    Vertex v = { vertex_id, distance };
    insert( v );
}

bool PriorityQueue::is_empty() const
{
    return queue_size == 0;
}

int PriorityQueue::left( int index ) const
{
    return 2 * index;
}

int PriorityQueue::parent( int index ) const
{
    return (int) index / 2;
}

void PriorityQueue::print() const
{
    std::cout << " [ ";
    for (int i = 1; i <= queue_size; ++i)
    {
        std::cout << heap_array[i].distance << " ";
    }
    std::cout << "]" << std::endl;
}

int PriorityQueue::right( int index ) const
{
    return 2 * index + 1;
}

void PriorityQueue::set_distance( int vertex_key, double new_distance )
{
    int index = find( vertex_key );
    heap_array[index].distance = new_distance;
    bubble_up( index );
}

void PriorityQueue::swap( int index1, int index2 )
{
    if (index1 < 1 || index1 > capacity || index2 < 1 || index2 > capacity)
    {
        throw illegal_argument();
    }

    Vertex vertex1 = heap_array[index1];
    Vertex vertex2 = heap_array[index2];
    heap_array[index1] = vertex2;
    heap_array[index2] = vertex1;
    index_of[vertex1.id] = index2;
    index_of[vertex2.id] = index1;
}

#endif
