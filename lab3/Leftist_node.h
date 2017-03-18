/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  uwuserid @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter|Spring|Fall) 201N
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

#ifndef LEFTIST_NODE_H
#define LEFTIST_NODE_H

#include <algorithm>
// You may use std::swap and std::min

#ifndef nullptr
#define nullptr 0
#endif

template <typename Type>
class Leftist_node {
	private:
		Type element;
		Leftist_node *left_tree;
		Leftist_node *right_tree;
		int heap_null_path_length;

	public:
		Leftist_node( Type const & );

		Type retrieve() const;
		bool empty() const;
		Leftist_node *left() const;
		Leftist_node *right() const;
		int count( Type const & ) const;
		int null_path_length() const;

		void push( Leftist_node *, Leftist_node *& );
		void clear();
};

template <typename Type>
Leftist_node<Type>::Leftist_node( Type const &obj ):
element( obj ),
left_tree( nullptr ),
right_tree( nullptr ),
heap_null_path_length( 0 ) {
	// does nothing
}

template <typename Type>
Type Leftist_node<Type>::retrieve() const {
    return element;
}

template <typename Type>
bool Leftist_node<Type>::empty() const {
	return ( this == nullptr );
}

template <typename Type>
Leftist_node<Type> *Leftist_node<Type>::left() const {
    return left_tree;
}

template <typename Type>
Leftist_node<Type> *Leftist_node<Type>::right() const {
    return right_tree;
}

template <typename Type>
int Leftist_node<Type>::count( Type const &obj ) const {
    if ( empty() )
        return 0;
    else
    {
        // jint left_tree_count = 0;
        // jint right_tree_count = 0;
        // jif ( left_tree->empty() == false )
        // j    left_tree_count = left_tree->count( obj );
        // jif ( right_tree->empty() == false )
        // j    right_tree_count = right_tree->count( obj );
        if ( element == obj )
        {
            return 1 + left_tree->count( obj ) + right_tree->count( obj );
        }
        else
        {
            return left_tree->count( obj ) + right_tree->count( obj );
        }
    }
}

template <typename Type>
int Leftist_node<Type>::null_path_length() const {
    if ( empty() )
        return -1;
    return heap_null_path_length;
}

template <typename Type>
void Leftist_node<Type>::push( Leftist_node *new_heap, Leftist_node *&ptr_to_this ) {
    if ( new_heap == nullptr )
        return;
    else
    {
        if ( empty() )
        {
            ptr_to_this = new_heap;
            return;
        }
        else if ( element <= new_heap->element )
        {
            right_tree->push( new_heap, right_tree );
            heap_null_path_length = 1 + std::min( left_tree->null_path_length(), right_tree->null_path_length() );
            if ( left_tree->null_path_length() < right_tree->null_path_length() )
            {
                std::swap( left_tree, right_tree );
            }
            return;
        }
        else
        {
            Leftist_node *old_ptr_to_this = ptr_to_this;
            ptr_to_this = new_heap;
            ptr_to_this->push( old_ptr_to_this, ptr_to_this );
        }
    }
}

template <typename Type>
void Leftist_node<Type>::clear() {
    if ( empty() )
        return;
    left_tree->clear();
    right_tree->clear();
    delete this;
}

#endif
