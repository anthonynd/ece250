/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  aat2nguy @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  Winter 2017
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef DYNAMIC_STACK_AS_ARRAY_H
#define DYNAMIC_STACK_AS_ARRAY_H

#ifndef nullptr
#define nullptr 0
#endif

#include <algorithm>
#include "Exception.h"


class Dynamic_range_stack {

    private:
  	    int entry_count;
		int max_count;
		int min_count;
		int initial_capacity;
		int current_capacity;

		int *stack_array;
		int *maximum_array;
		int *minimum_array;

		// You may wish to include a number of helper functions
		// in order to abstract out some operations


	public:
		Dynamic_range_stack( int = 10 );
		Dynamic_range_stack( Dynamic_range_stack const & );
		~Dynamic_range_stack();

		int top() const;
		int size() const;
		bool empty() const;
		int capacity() const;

		int maximum() const;
		int minimum() const;

		
		void push( int const & );
		int pop();
		void clear();


	// Friends
	friend std::ostream &operator<<( std::ostream &, Dynamic_range_stack const & );

};


Dynamic_range_stack::Dynamic_range_stack( int n ):
    entry_count( 0 ),
    min_count( 0 ),
    max_count( 0 ),
    initial_capacity( std::max( 1, n ) ),
    current_capacity( initial_capacity ),
    stack_array( new int[current_capacity] ),
    maximum_array( new int[current_capacity] ),
    minimum_array( new int[current_capacity] ) 
{
	// empty constructor
}

Dynamic_range_stack::~Dynamic_range_stack() 
{
    // Deletes the stack, max and min arrays
    delete [] stack_array;
    delete [] maximum_array;
    delete [] minimum_array;
}

int Dynamic_range_stack::top() const 
{
    // Return top of stack if there are elements on the stack
    if (entry_count > 0)
        return stack_array[entry_count - 1];
    throw underflow();
}

int Dynamic_range_stack::maximum() const 
{
    // Return top of max stack if there are elements
    if (max_count > 0)
        return maximum_array[max_count - 1];
    throw underflow();
}

int Dynamic_range_stack::minimum() const 
{
    // Return top of min stack if there are elements
    if (min_count > 0)
        return minimum_array[min_count - 1];
    throw underflow();
}

int Dynamic_range_stack::size() const 
{
    return entry_count;
}

bool Dynamic_range_stack::empty() const 
{
    if (entry_count == 0)
        return true;
    return false;
}

int Dynamic_range_stack::capacity() const 
{
    return current_capacity;
}


void Dynamic_range_stack::push( int const &obj ) 
{
    // When capacity is exceeded
    if (entry_count >= current_capacity) {
        // Create bigger arrays
        int *bigger_stack = new int[current_capacity*2];
        int *bigger_max_stack = new int[current_capacity*2];
        int *bigger_min_stack = new int[current_capacity*2];

        // Copy original array into new arrays
        std::copy(stack_array, stack_array + current_capacity, bigger_stack);
        std::copy(maximum_array, maximum_array + current_capacity, bigger_max_stack);
        std::copy(minimum_array, minimum_array + current_capacity, bigger_min_stack);

        // Free old array memeory
        delete [] stack_array;
        delete [] maximum_array;
        delete [] minimum_array;

        // Point original arrays to the new bigger arrays
        stack_array = bigger_stack;
        maximum_array = bigger_max_stack;
        minimum_array = bigger_min_stack;

        // Double capacity member
        current_capacity *= 2;
    }

    // Add to stack array
    stack_array[entry_count] = obj;
    entry_count++;
        
    // Add to max stack if bigger than top of max stack
    if (max_count == 0 || maximum_array[max_count - 1] < obj) {
        maximum_array[max_count] = obj;
        max_count++;
    }

    // Add to min stack if small than top of min stack
    if (min_count == 0 || minimum_array[min_count - 1] > obj) {
        minimum_array[min_count] = obj;
        min_count++;
    }

	return;
}

int Dynamic_range_stack::pop() 
{
    // Nothing that can be popped
    if (entry_count == 0)
        throw underflow();

    int popped = stack_array[entry_count-1];

    // Pop the max array as needed
    if (maximum_array[max_count - 1] == popped) {
        max_count--;
        maximum_array[max_count] = 0;
    }

    // Pop the min array as needed
    if (minimum_array[min_count - 1] == popped) {
        min_count--;
        minimum_array[min_count] = 0;
    }

    entry_count--;

    return popped;
}

void Dynamic_range_stack::clear() 
{
    // If current capacity was changed
    if (current_capacity != initial_capacity) {
        // Delete arrays and remake them with initial capacity
        delete [] stack_array;
        delete [] maximum_array;
        delete [] minimum_array;
        stack_array = new int[initial_capacity];
        maximum_array = new int[initial_capacity];
        minimum_array = new int[initial_capacity];
    }
    
    // Resets member variables
    current_capacity = initial_capacity;
    entry_count = 0;
    min_count = 0;
    max_count = 0;
}

// You can modify this function however you want:  it will not be tested

std::ostream &operator<<( std::ostream &out, Dynamic_range_stack const &stack ) 
{
	// Print out your stacks
    out << "Stack: ";
    for (int i = 0; i < stack.size(); i++) {
        out << stack.stack_array[i];
        out << " ";
    }
    out << "\n";

    out << "Max: ";
    for (int i = 0; i < stack.max_count; i++) {
        out << stack.maximum_array[i];
        out << " ";
    }
    out << "\n";

    out << "Min: ";
    for (int i = 0; i < stack.min_count; i++) {
        out << stack.minimum_array[i];
        out << " ";
    }
    out << "\n";

	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
