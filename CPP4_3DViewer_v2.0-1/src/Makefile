CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -std=c++17 -g
COVERAGE_FLAGS = -fprofile-arcs -ftest-coverage
CXX_FILES =  Model/*.cc Controller/*.cc
TEST_FILES = Tests/Tests.cc
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
	@rm -rf test test.dSYM *.gcno *.o *.gcda *.html *.css *.gcov
	@rm -rf *.gcno *.gcda 
	@rm -rf Archive
	@rm -rf Archive.tgz

style:
	find . -name "*.cc" -o -name "*.h" | xargs clang-format -style=google -n

format:
	find . -name "*.cc" -o -name "*.h" | xargs clang-format -style=google -i


valgrind :
	valgrind --leak-check=full ./test

leaks :
	leaks -atExit -- test

install: 
	mkdir -p build
	cd ./View; qmake -o ../build/Makefile
	cd ./build; make
	open build

uninstall:
	rm -rf build*

dist:
	mkdir -p Archive
	cp Makefile Archive
	cp -r Controller Model View Tests gif Docs Archive
	tar -czvf Archive.tar.gz Archive
	rm -rf Archive


dvi:
	cd Docs && doxygen Doxyfile
	 open Docs/html/index.html
