#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H

/****************************************
 * UW User ID:  uwuserid
 * Submitted for ECE 250
 * Semester of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 ****************************************/

#include "Exception.h"
#include "ece250.h"

enum state { EMPTY, OCCUPIED, DELETED };

template<typename T>
class DoubleHashTable {
	private:
		int count;
		int power;
		int array_size;
		T *array;
		state *array_state;

		int h1( T const & ) const; // first hash function
		int h2( T const & ) const; // second hash function

        int hash( T const & ) const; 
        int find( T const & ) const; 

	public:
		DoubleHashTable( int = 5 );
		~DoubleHashTable();
		int size() const;
		int capacity() const;		
		bool empty() const;
		bool member( T const & ) const;
		T bin( int ) const;

		void print() const;

		void insert( T const & );
		bool remove( T const & );
		void clear();
};

template<typename T >
DoubleHashTable<T >::DoubleHashTable( int m ):
    count( 0 ), 
    power( m ),
    array_size( 1 << power ),
    array( new T [array_size] ),
    array_state( new state[array_size] ) {
        for ( int i = 0; i < array_size; ++i ) {
		    array_state[i] = EMPTY;
	    }
}

template<typename T >
DoubleHashTable<T >::~DoubleHashTable() {
    delete [] array;
    delete [] array_state;
}

template<typename T >
int DoubleHashTable<T >::size() const {
    return count;
}

template<typename T >
int DoubleHashTable<T >::capacity() const {
    return array_size;
}

template<typename T >
bool DoubleHashTable<T >::empty() const {
    return count == 0;
}

template<typename T >
int DoubleHashTable<T >::h1( T const &obj ) const {
    int k = static_cast<int>(obj);
    int result = k % array_size; // k % M
    if (k < 0) { // If negative, add M
        result += array_size;
    }
    return result;
}

template<typename T >
int DoubleHashTable<T >::h2( T const &obj ) const {
    int k = static_cast<int>(obj);
    int result = (k / array_size) % array_size; // (k/M) % M
    if (result < 0) { // If negative, add M
        result += array_size;
    }
    if (result % 2 == 0) { // If even, add 1
        result += 1;
    }
    return result;
}

// Used for finding bin to insert to
template<typename T >
int DoubleHashTable<T >::hash( T const &obj ) const {
    int bin = h1(obj);
    int binOffset = h2(obj);
    while (array_state[bin] == OCCUPIED) {
        if (array[bin] == obj && array_state[bin] == OCCUPIED)
            break;
        bin = (bin + binOffset) % array_size;
    }
    return bin;
}

// Used for finding bin of existing element
template<typename T >
int DoubleHashTable<T >::find( T const &obj ) const {
    int initialBin = h1(obj);
    int bin = initialBin;
    int binOffset = h2(obj);
    do {
        if (array[bin] == obj && array_state[bin] == OCCUPIED)
            return bin;
        bin = (bin + binOffset) % array_size;
    } while (array_state[bin] != EMPTY && bin != initialBin);
    return -1;
}

template<typename T >
bool DoubleHashTable<T >::member( T const &obj ) const {
    int bin = find(obj);
    if (bin == -1) 
        return false; 
    return true;
}

template<typename T >
T DoubleHashTable<T >::bin( int n ) const {
    return array[n];
}

template<typename T >
void DoubleHashTable<T >::insert( T const &obj ) {
    if (count >= array_size) // Throw overflow error if table is full
        throw overflow();
    if (member(obj)) // If element is a member already, no need to insert
        return;
    else {
        int bin = hash(obj);
        array[bin] = obj;
        array_state[bin] = OCCUPIED;
        ++count;
    }
	return;
}

template<typename T >
bool DoubleHashTable<T >::remove( T const &obj ) {
    if (member(obj) == false) // If not a member, nothing to remove
	    return false;
    else { // Otherwise, remove normally
        int bin = find(obj);
        array[bin] = 0;
        array_state[bin] = DELETED;
        --count;
        return true;
    }
}

template<typename T >
void DoubleHashTable<T >::clear() {
    for (int i = 0; i < array_size; ++i) {
        array[i] = 0;
        array_state[i] = EMPTY;
    }
    count = 0;
	return; 
}

template<typename T >
void DoubleHashTable<T >::print() const {
    for (int i = 0; i < array_size; ++i) {
        std::cout << i << ": " << array[i] << std::endl; 
    }
	return;
}

#endif
