// ------------------------------------
// projects/allocator/TestAllocator.c++
// Copyright (C) 2015
// Glenn P. Downing
// ------------------------------------

// --------
// includes
// --------

#include <algorithm> // count
#include <memory>    // allocator

#include "gtest/gtest.h"

#include "Allocator.h"

// -------------
// TestAllocator
// -------------

template <typename A>
struct TestAllocator : testing::Test {
    // --------
    // typedefs
    // --------

    typedef          A                  allocator_type;
    typedef typename A::value_type      value_type;
    typedef typename A::difference_type difference_type;
    typedef typename A::pointer         pointer;};

typedef testing::Types<
            std::allocator<int>,
            std::allocator<double>,
            Allocator<int, 100>,
            Allocator<double, 100> >
        my_types;

TYPED_TEST_CASE(TestAllocator, my_types);

TYPED_TEST(TestAllocator, One) {
    typedef typename TestFixture::allocator_type  allocator_type;
    typedef typename TestFixture::value_type      value_type;
    typedef typename TestFixture::difference_type difference_type;
    typedef typename TestFixture::pointer         pointer;

    allocator_type x;
    const difference_type s = 1;
    const value_type      v = 2;
    const pointer         p = x.allocate(s);
    if (p != 0) {
        x.construct(p, v);
        ASSERT_EQ(v, *p);
        x.destroy(p);
        x.deallocate(p, s);}}

TYPED_TEST(TestAllocator, Ten) {
    typedef typename TestFixture::allocator_type  allocator_type;
    typedef typename TestFixture::value_type      value_type;
    typedef typename TestFixture::difference_type difference_type;
    typedef typename TestFixture::pointer         pointer;

    allocator_type x;
    const difference_type s = 10;
    const value_type      v = 2;
    const pointer         b = x.allocate(s);
    if (b != 0) {
        pointer e = b + s;
        pointer p = b;
        try {
            while (p != e) {
                x.construct(p, v);
                ++p;}}
        catch (...) {
            while (b != p) {
                --p;
                x.destroy(p);}
            x.deallocate(b, s);
            throw;}
        ASSERT_EQ(s, std::count(b, e, v));
        while (b != e) {
            --e;
            x.destroy(e);}
        x.deallocate(b, s);}}

/*
    Allocator
*/

TEST(Allocator, basic_1){
    Allocator<double, 100> x;

    ASSERT_EQ(92,x[0]);
    ASSERT_EQ(92,x[96]);
}
TEST(Allocator, basic_2) {
    Allocator<int,24> x;

    ASSERT_EQ(16,x[0]);
    ASSERT_EQ(16,x[20]);
}
TEST(Allocator, bad_alloc){
    try{
        Allocator<double, 3> x;
    } catch (std::bad_alloc){
    }
}

/*
    Allocate
*/

TEST(Allocate, basic){
    Allocator<int, 12> x;

        x.allocate(1);

    ASSERT_EQ(-4,x[0]);
    ASSERT_EQ(-4,x[8]);
}
TEST(Allocate, exact_fit){
    Allocator<int, 24> x;

        x.allocate(4);

    ASSERT_EQ(-16,x[0]);
    ASSERT_EQ(-16,x[20]);
}
TEST(Allocate, slack){
    Allocator<int, 24> x;

        x.allocate(3);

    ASSERT_EQ(-16,x[0]);
    ASSERT_EQ(-16,x[20]);
}
TEST(Allocate, much_bigger){
    Allocator<int, 24> x;

        x.allocate(1);

    ASSERT_EQ(-4,x[0]);
    ASSERT_EQ(-4,x[8]);
    ASSERT_EQ(4,x[12]);
    ASSERT_EQ(4,x[20]);
}
TEST(Allocate, much_bigger2){
    Allocator<int, 24> x;

        x.allocate(1);

    ASSERT_EQ(-4,x[0]);
    ASSERT_EQ(-4,x[8]);
    ASSERT_EQ(4,x[12]);
    ASSERT_EQ(4,x[20]);

        x.allocate(1);

    ASSERT_EQ(-4,x[0]);
    ASSERT_EQ(-4,x[8]);
    ASSERT_EQ(-4,x[12]);
    ASSERT_EQ(-4,x[20]);
}
TEST(Allocate, quiz_21){
    Allocator<double, 100> x;

        x.allocate(5);

    ASSERT_EQ(-40,x[0]);
    ASSERT_EQ(-40,x[44]);
    ASSERT_EQ(44,x[48]);
    ASSERT_EQ(44,x[96]);

        x.allocate(3);

    ASSERT_EQ(-40,x[0]);
    ASSERT_EQ(-40,x[44]);
    ASSERT_EQ(-24,x[48]);
    ASSERT_EQ(-24,x[76]);
    ASSERT_EQ(12,x[80]);
    ASSERT_EQ(12,x[96]);
}
TEST(Allocate, bad_alloc){
    Allocator<int, 12> x;

    try{
        x.allocate(-1);
    } catch (std::bad_alloc){
    }
    ASSERT_EQ(4,x[0]);
    ASSERT_EQ(4,x[8]);
}
TEST(Allocate, zero){
    Allocator<int, 12> x;

        x.allocate(0);

    ASSERT_EQ(4,x[0]);
    ASSERT_EQ(4,x[8]);
}

/*
    Allocate (pointer)
*/

TEST(Allocate, pointer_basic){
    Allocator<int, 12> x;

        int * ptr = x.allocate(1);

    ASSERT_EQ((int*)&(x[4]),ptr);
}
TEST(Allocate, pointer_quiz_21){
    Allocator<double, 100> x;

        double * ptr1 = x.allocate(5);

        double * ptr2 = x.allocate(3);

    ASSERT_EQ((double*)&(x[4]),ptr1);
    ASSERT_EQ((double*)&(x[52]),ptr2);
}

/*
    Deallocate
*/

TEST(Deallocate, basic_1){
    Allocator<int, 12> x;

        int * ptr = x.allocate(1);

    ASSERT_EQ(-4,x[0]);
    ASSERT_EQ(-4,x[8]);

        x.deallocate(ptr,1);

    ASSERT_EQ(4,x[0]);
    ASSERT_EQ(4,x[8]);
}
TEST(Deallocate, basic_2a){
    Allocator<int, 24> x;

    ASSERT_EQ(16,x[0]);
    ASSERT_EQ(16,x[20]);

        int * ptr1 = x.allocate(1);
        int * ptr2 = x.allocate(1);

        x.deallocate(ptr1,1);
        x.deallocate(ptr2,1);

    ASSERT_EQ(16,x[0]);
    ASSERT_EQ(16,x[20]);
}
TEST(Deallocate, basic_2b){
    Allocator<int, 24> x;

    ASSERT_EQ(16,x[0]);
    ASSERT_EQ(16,x[20]);

        int * ptr1 = x.allocate(1);
        int * ptr2 = x.allocate(1);

        x.deallocate(ptr2,1);
        x.deallocate(ptr1,1);

    ASSERT_EQ(16,x[0]);
    ASSERT_EQ(16,x[20]);
}
TEST(Deallocate, basic_3a){
    Allocator<int, 36> x;

    ASSERT_EQ(28,x[0]);
    ASSERT_EQ(28,x[32]);

        int * ptr1 = x.allocate(1);
        int * ptr2 = x.allocate(1);
        int * ptr3 = x.allocate(1);

        x.deallocate(ptr1,1);
        x.deallocate(ptr2,1);
        x.deallocate(ptr3,1);

    ASSERT_EQ(28,x[0]);
    ASSERT_EQ(28,x[32]);
}
TEST(Deallocate, basic_3b){
    Allocator<int, 36> x;

    ASSERT_EQ(28,x[0]);
    ASSERT_EQ(28,x[32]);

        int * ptr1 = x.allocate(1);
        int * ptr2 = x.allocate(1);
        int * ptr3 = x.allocate(1);

        x.deallocate(ptr1,1);
        x.deallocate(ptr3,1);
        x.deallocate(ptr2,1);

    ASSERT_EQ(28,x[0]);
    ASSERT_EQ(28,x[32]);
}
TEST(Deallocate, basic_3c){
    Allocator<int, 36> x;

    ASSERT_EQ(28,x[0]);
    ASSERT_EQ(28,x[32]);

        int * ptr1 = x.allocate(1);
        int * ptr2 = x.allocate(1);
        int * ptr3 = x.allocate(1);

        x.deallocate(ptr2,1);
        x.deallocate(ptr1,1);
        x.deallocate(ptr3,1);

    ASSERT_EQ(28,x[0]);
    ASSERT_EQ(28,x[32]);
}
TEST(Deallocate, basic_3d){
    Allocator<int, 36> x;

    ASSERT_EQ(28,x[0]);
    ASSERT_EQ(28,x[32]);

        int * ptr1 = x.allocate(1);
        int * ptr2 = x.allocate(1);
        int * ptr3 = x.allocate(1);

        x.deallocate(ptr2,1);
        x.deallocate(ptr3,1);
        x.deallocate(ptr1,1);

    ASSERT_EQ(28,x[0]);
    ASSERT_EQ(28,x[32]);
}
TEST(Deallocate, basic_3e){
    Allocator<int, 36> x;

    ASSERT_EQ(28,x[0]);
    ASSERT_EQ(28,x[32]);

        int * ptr1 = x.allocate(1);
        int * ptr2 = x.allocate(1);
        int * ptr3 = x.allocate(1);

        x.deallocate(ptr3,1);
        x.deallocate(ptr2,1);
        x.deallocate(ptr1,1);

    ASSERT_EQ(28,x[0]);
    ASSERT_EQ(28,x[32]);
}
TEST(Deallocate, basic_3f){
    Allocator<int, 36> x;

    ASSERT_EQ(28,x[0]);
    ASSERT_EQ(28,x[32]);

        int * ptr1 = x.allocate(1);
        int * ptr2 = x.allocate(1);
        int * ptr3 = x.allocate(1);

        x.deallocate(ptr3,1);
        x.deallocate(ptr1,1);
        x.deallocate(ptr2,1);

    ASSERT_EQ(28,x[0]);
    ASSERT_EQ(28,x[32]);
}
TEST(Deallocate, basic_4){
    Allocator<int, 36> x;

    ASSERT_EQ(28,x[0]);
    ASSERT_EQ(28,x[32]);

        int * ptr1 = x.allocate(3);
        int * ptr2 = x.allocate(2);
        x.deallocate(ptr1,1);
        ptr1 = x.allocate(1);
        x.deallocate(ptr2,1);
        x.deallocate(ptr1,1);

    ASSERT_EQ(28,x[0]);
    ASSERT_EQ(28,x[32]);
}
TEST(Deallocate, invalid_argument_1){
    Allocator<int, 12> x;
    int num = 2;
    try{
        x.deallocate(&num,1);
    } catch (std::invalid_argument){
    }
    ASSERT_EQ(4,x[0]);
    ASSERT_EQ(4,x[8]);
}
TEST(Deallocate, invalid_argument_2){
    Allocator<int, 12> x;
    try{
        x.deallocate(NULL,1);
    } catch (std::invalid_argument){
    }
    ASSERT_EQ(4,x[0]);
    ASSERT_EQ(4,x[8]);
}
TEST(Deallocate, invalid_argument_3){
    Allocator<int, 12> x;
    try{
        x.deallocate((int*)-1,1);
    } catch (std::invalid_argument){
    }
    ASSERT_EQ(4,x[0]);
    ASSERT_EQ(4,x[8]);
}
TEST(Deallocate, invalid_argument_4){
    Allocator<int, 12> x;
    int * ptr = x.allocate(1);
    try{
        x.deallocate(++ptr,1);
    } catch (std::invalid_argument){
    }
    ASSERT_EQ(-4,x[0]);
    ASSERT_EQ(-4,x[8]);
}
TEST(Deallocate, invalid_argument_5){
    Allocator<int, 12> x;
    int * ptr = x.allocate(1);
    x[8] = 4;
    try{
        x.deallocate(ptr,1);
    } catch (std::invalid_argument){
    }
    ASSERT_EQ(-4,x[0]);
    ASSERT_EQ(4,x[8]);
}

/*
    Valid
*/

TEST(Valid, unmatched_sentinels){
    Allocator<int, 12> x;

    x[8] = -4;

    ASSERT_EQ(0,x.valid());
}
TEST(Valid, adjacent_free_blocks){
    Allocator<int, 24> x;

    x[0] = 4;
    x[8] = 4;
    x[12] = 4;
    x[20] = 4;

    ASSERT_EQ(0,x.valid());
}
TEST(Valid, smaller_sizeof_T){
    Allocator<int, 12> x;

    x[0] = 5;
    x[8] = 5;

    ASSERT_EQ(0,x.valid());
}