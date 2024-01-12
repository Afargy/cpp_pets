#utilities
COPMILER = g++
#files
MAIN_HEADER = *.h 
TESTS_SOURCE = tests/*.cc
FOR_CLEAN = a.out valgrind_results.txt *.gcno *.info report
# flags
COPMILER_FLAGS = -Wall -Werror -Wextra -std=c++17 
VALGRIND_FLAGS = --quiet --leak-check=full --track-origins=yes --trace-children=yes --tool=memcheck 
GCOV_FLAGS = -fprofile-arcs -ftest-coverage -fno-elide-constructors
TEST_FLAGS = $(COPMILER_FLAGS) -fsanitize=address
# libs
TESTS_LIBS = -lgtest -lpthread -lgtest_main
GCOV_LIBS = -lgtest -lm -lpthread -lcheck 
# runners and removers
RUN_OUT = ./a.out
REMOVE = rm -rf

all: test

test: clean
	$(COPMILER) $(TEST_FLAGS) $(TESTS_SOURCE) $(TESTS_LIBS) 
	$(RUN_OUT)

gcov: gcov_report

gcov_report:
	$(COPMILER) $(COPMILER_FLAGS) $(GCOV_FLAGS) $(TESTS_SOURCE) $(GCOV_LIBS) $(TESTS_LIBS)
	$(RUN_OUT)
	lcov --no-external --ignore-errors mismatch,empty,gcov -t "test" -o test.info -c -d . -d tests/.
	genhtml -o report test.info
	$(REMOVE) *.gcno *.gcda
	open ./report/index.html


style:
	clang-format -i -style=google $(TESTS_SOURCE) $(MAIN_HEADER)
	clang-format -n -style=google $(TESTS_SOURCE) $(MAIN_HEADER)

clean:
	make clean_for -s

clean_for:
	for elem in $(FOR_CLEAN); do\
		if [ -e $$elem ]; then\
			$(REMOVE) $$elem;\
		fi;\
	done

leaks: test
	leaks -atExit -- $(RUN_OUT)

valgrind: 
	$(COPMILER) $(COPMILER_FLAGS) $(TESTS_SOURCE) $(TESTS_LIBS)
	valgrind $(VALGRIND_FLAGS) --log-file=valgrind_results.txt $(RUN_OUT)



