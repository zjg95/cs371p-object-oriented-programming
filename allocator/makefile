all:

Allocator.log:
	git log > Allocator.log

Doxyfile:
	doxygen -g

TestAllocator: Allocator.h TestAllocator.c++
	g++-4.7 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall TestAllocator.c++ -o TestAllocator -lgtest -lgtest_main -lpthread

TestAllocator.out: TestAllocator
	valgrind TestAllocator        >  TestAllocator.out 2>&1
	gcov-4.7 -b TestAllocator.c++ >> TestAllocator.out

allocator-tests:
	git clone https://github.com/cs371p-spring-2015/allocator-tests.git

html: Doxyfile Allocator.h TestAllocator.c++
	doxygen Doxyfile

check:
	@[ -d html                                  ] && echo "html/                                 found" || echo "html/                                 NOT FOUND"
	@[ -e allocator-tests/EID-TestAllocator.c++ ] && echo "allocator-tests/EID-TestAllocator.c++ found" || echo "allocator-tests/EID-TestAllocator.c++ NOT FOUND"
	@[ -e allocator-tests/EID-TestAllocator.out ] && echo "allocator-tests/EID-TestAllocator.out found" || echo "allocator-tests/EID-TestAllocator.out NOT FOUND"
	@[ -e Allocator.h                           ] && echo "Allocator.h                           found" || echo "Allocator.h                           NOT FOUND"
	@[ -e Doxyfile                              ] && echo "Doxyfile                              found" || echo "Doxyfile                              NOT FOUND"
	@[ -e TestAllocator.c++                     ] && echo "TestAllocator.c++                     found" || echo "TestAllocator.c++                     NOT FOUND"
	@[ -e TestAllocator.out                     ] && echo "TestAllocator.out                     found" || echo "TestAllocator.out                     NOT FOUND"

clean:
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.gcov
	rm -f TestAllocator
	rm -f TestAllocator.out

config:
	git config -l