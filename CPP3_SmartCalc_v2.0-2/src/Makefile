CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -std=c++17 -g
COVERAGE_FLAGS = -fprofile-arcs -ftest-coverage
CXX_FILES =  Model/*.cc Controller/*.cc
TEST_FILES = CalcTest.cc
TEST_FLAGS = -lgtest -pthread

.PHONY : all test gcov_report leaks valgrind clean clang

all : test

test : $(CXX_FILES) $(TEST_FILES)
	$(CXX) $(CXXFLAGS) $(CXX_FILES) --coverage $(COVERAGE_FLAGS) $(TEST_FILES) -o test $(TEST_FLAGS)
	# $(CXX) $(CXXFLAGS) $(TEST_FILES) -o test $(TEST_FLAGS)
	./test

gcov_report :
	gcovr -r . --html-details -o test.html
	# gcovr --html-details -o test.html
	open test.html

clean :
	rm -rf test test.dSYM *.gcno *.o *.gcda *.html *.css *.gcov
	rm -rf *.gcno *.gcda 
	# rm -rf Archive
	# rm Archive.tgz

clang :
	clang-format -style=Google -n $(CXX_FILES) $(TEST_FILES) *.h 
	# *.cc *.inc

valgrind :
	valgrind --leak-check=full ./test

leaks :
	leaks -atExit -- test

install:
	make clean
	mkdir build
	cd Culk && qmake && make && make clean && rm Makefile && cd ../ && mv Culk/Culk.app build

uninstall:
	rm -rf build*

dist:
	rm -rf Archive/
	mkdir Archive/
	mkdir Archive/src
	cp -r ./build/Culk.app Archive/src/
	tar cvzf Archive.tgz Archive/
	rm -rf Archive/

dvi:
	cd Docs && doxygen Doxyfile
	 open html/index.html
