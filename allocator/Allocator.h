// ------------------------------
// projects/allocator/Allocator.h
// Copyright (C) 2015
// Glenn P. Downing
// ------------------------------

#ifndef Allocator_h
#define Allocator_h

// --------
// includes
// --------

#include <cassert>   // assert
#include <cstddef>   // ptrdiff_t, size_t
#include <new>       // bad_alloc, new
#include <stdexcept> // invalid_argument
#include <iostream>
#include <cmath>

using namespace std;

// ---------
// Allocator
// ---------

template <typename T, std::size_t N>
class Allocator {
    public:
        // --------
        // typedefs
        // --------

        typedef T                 value_type;

        typedef std::size_t       size_type;
        typedef std::ptrdiff_t    difference_type;

        typedef       value_type*       pointer;
        typedef const value_type* const_pointer;

        typedef       value_type&       reference;
        typedef const value_type& const_reference;

    public:
        // -----------
        // operator ==
        // -----------

        friend bool operator == (const Allocator&, const Allocator&) {
            return true;}                                              // this is correct

        // -----------
        // operator !=
        // -----------

        friend bool operator != (const Allocator& lhs, const Allocator& rhs) {
            return !(lhs == rhs);}

    private:
        // ----
        // data
        // ----

        char a[N];

        int get_sentinel(int& index) const{
            int * ptr = (int*) &a[index];
            return *ptr;
        }
    public:

        // -----
        // valid
        // -----

        /**
         * O(1) in space
         * O(n) in time
         * iterates through the array making sure that sentinel pairs are
            correct (matching). Also make sure there are no adjacent free blocks.
         */
        bool valid () const {
            /*
                - iterate through the array
                - make sure sentinels are correct
                - make sure there are no two adjacent free blocks
            */
            for (int index1 = 0; index1 < (int)(N - sizeof(int));){
                int sentinel_1 = get_sentinel(index1);
                int index2 = index1 + sizeof(int) + abs(sentinel_1);
                int sentinel_2 = get_sentinel(index2);

                if (sentinel_1 != sentinel_2){ // make sure sentinels are equal
                    return false;
                }

                if (abs(sentinel_1) < (int)sizeof(T)){ // make sure there's room for at least 1 T
                    return false;
                }

                if (index1 > 0){
                    int next = index1- sizeof(int);
                    int neighbor_sentinel = get_sentinel(next); // no two adjacent free blocks (left)
                    if (sentinel_1 > 0 && neighbor_sentinel > 0){
                        return false;
                    }
                }
                if (index2 < (int)(N - sizeof(int))){
                    int next = index2 + sizeof(int);
                    int neighbor_sentinel = get_sentinel(next); // no two adjacent free blocks (right)
                    if (sentinel_2 > 0 && neighbor_sentinel > 0){
                        return false;
                    }
                }

                index1 = sizeof(int) + index2; // progress to next sentinel
            }
            return true;}

        /**
         * O(1) in space
         * O(1) in time
         * returns a modifiable index from the data array
         */
        int& operator [] (int i) {
            return *reinterpret_cast<int*>(&a[i]);}

    private:

        void write_sentinel(int index, int value){
            assert(index>=0);
            int * ptr = (int*) &a[index];
            *ptr = value;
        }
        int get_sentinel(int index){
            assert(index>=0);
            int * ptr = (int*) &a[index];
            return *ptr;
        }
        int get_index(int * ptr){
            assert(ptr>=(int*)&a[0] && ptr<=(int*)&a[(int)(N - sizeof(int))]);
            for (int index = 0; index < (int)(N - sizeof(int));index++){
                if (ptr == (int*)&a[index])
                    return index;
            }
            return -1;
        }
        void print_array(){
            for (int index = 0; index < (int)(N - sizeof(int));){
                int sentinel = get_sentinel(index);
                cout << "[" << sentinel <<"]";
                cout << "...";
                cout << "[" << get_sentinel(index + sizeof(int) + abs(sentinel)) << "]";
                index += sizeof(int) + sizeof(int) + abs(sentinel);
            }
            cout << endl;
        }

    public:
        // ------------
        // constructors
        // ------------

        /**
         * O(1) in space
         * O(1) in time
         * throw a bad_alloc exception, if N is less than sizeof(T) + (2 * sizeof(int))
         */
        Allocator () {
            /*
                - fill in the two sentinels
            */
            if (N < sizeof(T) + (2 * sizeof(int))){
                std::bad_alloc exception;
                throw exception;
            }
            write_sentinel(0,(int)(N- 2 * sizeof(int)));
            write_sentinel((int)(N - sizeof(int)),(int)(N- 2 * sizeof(int)));

            assert(valid());}

        // Default copy, destructor, and copy assignment
        // Allocator  (const Allocator&);
        // ~Allocator ();
        // Allocator& operator = (const Allocator&);

        // --------
        // allocate
        // --------

        /**
         * O(1) in space
         * O(n) in time
         * after allocation there must be enough space left for a valid block
         * the smallest allowable block is sizeof(T) + (2 * sizeof(int))
         * choose the first block that fits
         * throw a bad_alloc exception, if n is invalid
         */
        pointer allocate (size_type n) {
            /*
                - input n, how many elements in array
                - do first fit, linear pass
                - ensure that the block has at least  remaining
                - example:
                    user wants 40 doubles
                    must find space of at least 56 (40 doubles + 1 double (8bytes) + sentinels (2 * 4bytes))
                    if big enough, split into sub blocks
                    otherwise give entire space to user
            */

            if (n == 0){
                return 0;
            }

            pointer ptr = 0;

            int bytes_needed = n * sizeof(T);
            int slack_space = sizeof(T) + 2 * sizeof(int);
            
            if (bytes_needed < 0){
                std::bad_alloc exception;
                throw exception;
            }

            for (int index = 0; index < (int)(N - sizeof(int));){
                int sentinel = get_sentinel(index);
                if (sentinel < 0){
                    index += + sizeof(int) + abs(sentinel) + sizeof(int);
                    continue;
                }
                if (sentinel < bytes_needed){
                    index += + sizeof(int) + abs(sentinel) + sizeof(int);
                }
                else if (sentinel == bytes_needed || sentinel - bytes_needed - slack_space < 0){
                    write_sentinel(index,-sentinel);
                    write_sentinel(index + sizeof(int) + sentinel,-sentinel);

                    ptr = (T*)&a[index + sizeof(int)];
                    
                    break;
                }
                else{
                    int difference = sentinel - bytes_needed;

                    write_sentinel(index,-bytes_needed);
                    write_sentinel(index + sizeof(int) + bytes_needed,-bytes_needed);

                    ptr = (T*)&a[index + sizeof(int)];
                    
                    index +=  sizeof(int) + sizeof(int) + bytes_needed;
                    sentinel = difference- sizeof(int) - sizeof(int);

                    write_sentinel(index, sentinel);
                    write_sentinel(index + sizeof(int) + sentinel, sentinel);

                    break;
                }
            }

            assert(valid());
            return ptr;}

        // ---------
        // construct
        // ---------

        /**
         * O(1) in space
         * O(1) in time
         */
        void construct (pointer p, const_reference v) {
            new (p) T(v);                               // this is correct and exempt
            assert(valid());}                           // from the prohibition of new

        // ----------
        // deallocate
        // ----------

        /**
         * O(1) in space
         * O(1) in time
         * after deallocation adjacent free blocks must be coalesced
         * throw an invalid_argument exception, if p is invalid
         * checks the pointer for validity, then gets flips the
            sentinels to positive. Finds the farthest right/left sentinels
            of adjacent free blocks.
         */
        
        int get_farthest_left(int index){
            if (index <=0)
                return 0;
            int sent = get_sentinel(index - sizeof(int));
            if (sent <= 0)
                return index;
            return get_farthest_left(index - (2 * sizeof(int) + sent));
        }
        int get_farthest_right(int index){
            if (index >= (int)(N - sizeof(int)))
                return (int)(N - sizeof(int));
            int sent = get_sentinel(index + sizeof(int));
            if (sent <= 0)
                return index;
            return get_farthest_right(index + (2 * sizeof(int) + sent));
        }

        void deallocate (pointer p, size_type) {
            /*
                - change sentinels from negative to positive
                - join any free blocks that are in front/behind this one
            */

            int * ptr = (int *)(p);
            ptr--;

            if (ptr < (int*)&a[0] || ptr > (int*)&a[(int)(N - sizeof(int))]){
                throw std::invalid_argument( "pointer argument not in allocator's range!" );
            }

            int indexL = get_index(ptr);
            int sentL = get_sentinel(indexL);
            int indexR = indexL + abs(sentL) + sizeof(int);
            int sentR = get_sentinel(indexR);

            if (sentL != sentR || sentL >= 0 || sentR >=0){
                throw std::invalid_argument( "pointer argument not the start of a block!" );
            }

            indexL = get_farthest_left(indexL);
            indexR = get_farthest_right(indexR);

            int difference = indexR - (indexL + sizeof(int));
            
            write_sentinel(indexL,difference);
            write_sentinel(indexR,difference);

            assert(valid());}

        // -------
        // destroy
        // -------

        /**
         * O(1) in space
         * O(1) in time
         */
        void destroy (pointer p) {
            p->~T();               // this is correct
            assert(valid());}

        /**
         * O(1) in space
         * O(1) in time
         * returns an un-alterable index value.
         */
        const int& operator [] (int i) const {
            return *reinterpret_cast<const int*>(&a[i]);}};

#endif // Allocator_h