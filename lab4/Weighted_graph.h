/*****************************************
 * UW User ID:  uwuserid
 * Submitted for ECE 250
 * Semester of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 *  the provided code.
 *****************************************/

#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
#include <limits>
#include <stdio.h>
#include "PriorityQueue.h"

// include whatever classes you want

class Weighted_graph {
	private:
		// your implementation here
		//  you can add both private member variables and private member functions
		static const double INF;
        double **adjacency_matrix;
        int *degree_of;
        double *distance_to;
        int graph_size;
        bool *is_known;
        int total_edges;
        PriorityQueue *unknown_vertices;

        bool exists( int ) const;
        bool is_adjacent( int, int ) const;

	public:
		Weighted_graph( int = 50 );
		~Weighted_graph();

		double adjacent( int, int ) const;
		int degree( int ) const;
		double distance( int, int ) const;
		int edge_count() const;

		void insert( int, int, double );

	// Friends

	friend std::ostream &operator<<( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

// Your implementation here

Weighted_graph::Weighted_graph( int size ):
    total_edges( 0 ),
    graph_size( size )
{
    adjacency_matrix = new double*[graph_size];
    for (int row_index = 0; row_index < graph_size; ++row_index) {
        adjacency_matrix[row_index] = new double[graph_size];
        for (int col_index = 0; col_index < graph_size; ++col_index) {
            adjacency_matrix[row_index][col_index] = INF;
        }
    }
    degree_of = new int[graph_size];
    for (int index = 0; index < graph_size; ++index) {
        degree_of[index] = 0;
    }
    unknown_vertices = new PriorityQueue(graph_size);
    distance_to = new double[graph_size];
    is_known = new bool[graph_size];
}

Weighted_graph::~Weighted_graph() {
    for (int i = 0; i < graph_size; ++i)
    {
        delete [] adjacency_matrix[i];
    }
    delete [] adjacency_matrix;
    delete [] degree_of;
    delete [] distance_to;
    delete [] is_known;
    delete unknown_vertices;
}

double Weighted_graph::adjacent( int vertex1, int vertex2 ) const {
    if (!exists( vertex1 ) || !exists( vertex2 )) {
        throw illegal_argument();
    } 
    else if (vertex1 == vertex2) {
        return 0;
    } 
    else {
        return adjacency_matrix[vertex1][vertex2];
    }
}

int Weighted_graph::degree( int vertex ) const { // O(1)
    //return degree_of[vertex];
    int deg = 0;
    for (int other_vertex = 0; other_vertex < graph_size; ++other_vertex)
    {
        if (is_adjacent( vertex, other_vertex ))
        {
            ++deg;
        }
    }
    return deg;
}

double Weighted_graph::distance( int source, int destination ) const 
{
    // Initialization
    unknown_vertices->clear();
    //unknown_vertices->initialize( source );
    for (int i = 0; i < graph_size; ++i)
    {
        //Vertex v = { i, INF };
        //unknown_vertices->insert( v );
        is_known[i] = false;
        distance_to[i] = INF;
    }
    //unknown_vertices->set_distance( source, 0 );
    unknown_vertices->insert( source, 0 );
    distance_to[source] = 0;

    while (!unknown_vertices->is_empty())
    {
        Vertex min = unknown_vertices->extract_min();

        is_known[min.id] = true;

        //if (min.id == destination)
        if (is_known[destination])
            return min.distance;
            //break;

        // For each unknown and adjacent vertex
        for (int adj = 0; adj < graph_size; ++adj)
        {
            //if (is_adjacent( min.id, adj ) && unknown_vertices->contains( adj ))
            if (is_adjacent( min.id, adj ) && !is_known[adj])
            {
                double cost_to_adjacent = adjacency_matrix[min.id][adj];
                if (distance_to[min.id] + cost_to_adjacent < distance_to[adj])
                //if (min.distance + cost_to_adjacent < unknown_vertices->get(adj).distance)
                {
                    //unknown_vertices->set_distance( adj, min.distance + cost_to_adjacent );
                    distance_to[adj] = distance_to[min.id] + cost_to_adjacent;
                    if (unknown_vertices->contains( adj ))
                    {
                        unknown_vertices->set_distance(adj, distance_to[adj]);
                    }
                    else
                    {
                        //Vertex v = { adj, distance_to[adj] };
                        unknown_vertices->insert( adj, distance_to[adj] );
                    }
                }
            }
        }
    }
    return INF;
    //return distance_to[destination];
}

int Weighted_graph::edge_count() const { // O(1)
    return total_edges;
}

bool Weighted_graph::exists( int vertex ) const {
    return vertex < graph_size && vertex >= 0;
}

void Weighted_graph::insert( int vertex1, int vertex2, double weight ) 
{ // O(1)
    if (weight <= 0) 
    {
        throw illegal_argument();
    } 
    else 
    {
        if (vertex1 == vertex2 || !exists( vertex1 ) || !exists( vertex2 )) 
        {
            throw illegal_argument();
        } 
        else 
        {
            if (adjacency_matrix[vertex1][vertex2] == INF) 
            {
                ++total_edges;
                //degree_of[vertex1] = degree_of[vertex1] + 1;
                //degree_of[vertex2] = degree_of[vertex2] + 1;
            }
            adjacency_matrix[vertex1][vertex2] = weight;
            adjacency_matrix[vertex2][vertex1] = weight;
        }
    }
}

bool Weighted_graph::is_adjacent( int vertex1, int vertex2 ) const {
    double adj = adjacent( vertex1, vertex2 );
    return adj > 0 && adj != INF;
}

// You can modify this function however you want:  it will not be tested

std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
    for (int i = 0; i < graph.graph_size; ++i) {
        std::cout << " " << i << ": ";
        for (int j = 0; j < graph.graph_size; ++j) {
            std::cout << graph.adjacency_matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
	return out;
}


// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
