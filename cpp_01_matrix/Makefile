# utilities
COPMILER = g++
ARCHIVATOR = ar cr
RANLIB = ranlib
# files
MAIN_SOURCE = *.cc
MAIN_HEADER = *.h
TESTS_SOURCE = tests/*.cc
OBJECT_FILES = *.o
ARCHIVE = s21_matrix_oop.a
FOR_CLEAN = a.out $(OBJECT_FILES) $(ARCHIVE) valgrind_results.txt *.gcno *.info report
# flags
COPMILER_FLAGS = -Wall -Werror -Wextra -std=c++17 
VALGRIND_FLAGS = --quiet --leak-check=full --track-origins=yes --trace-children=yes --tool=memcheck 
GCOV_FLAGS = -fprofile-arcs -ftest-coverage -fno-elide-constructors
TEST_FLAGS = $(COPMILER_FLAGS) -fsanitize=address
# libs
TESTS_LIBS = -lgtest -lpthread
GCOV_LIBS = -lgtest -lm -lpthread -lcheck
# runners and removers
RUN_OUT = ./a.out
REMOVE = rm -rf

# all: clean $(ARCHIVE)
all: $(ARCHIVE)

$(ARCHIVE):
	$(COPMILER) -c $(COPMILER_FLAGS) $(MAIN_SOURCE)
	$(ARCHIVATOR) $(ARCHIVE) $(OBJECT_FILES)
	$(RANLIB) $(ARCHIVE)
	$(RM) $(OBJECT_FILES)

test: clean
	$(COPMILER) $(TEST_FLAGS) $(MAIN_SOURCE) $(TESTS_SOURCE) $(TESTS_LIBS) 
	$(RUN_OUT)

gcov: gcov_report

gcov_report: $(ARCHIVE)
	$(COPMILER) $(COPMILER_FLAGS) $(GCOV_FLAGS) $(MAIN_SOURCE) $(TESTS_SOURCE) $(GCOV_LIBS)
	$(RUN_OUT)
	lcov --no-external -t "test" -o test.info -c -d . -d tests/.
	genhtml -o report test.info
	$(REMOVE) *.gcno *.gcda
	open ./report/index.html

style:
	clang-format -i -style=google $(MAIN_SOURCE) $(TESTS_SOURCE) $(MAIN_HEADER)
	clang-format -n -style=google $(MAIN_SOURCE) $(TESTS_SOURCE) $(MAIN_HEADER)

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
	$(COPMILER) $(COPMILER_FLAGS) $(MAIN_SOURCE) $(TESTS_SOURCE) $(TESTS_LIBS)
	valgrind $(VALGRIND_FLAGS) --log-file=valgrind_results.txt $(RUN_OUT)
