CC = gcc
CFLAGS = -Wall -Werror -Wextra
GCOVFLAGS = -fprofile-arcs -ftest-coverage
TEST_LIBS = -lcheck -lm
SOURCE = $(wildcard *.c)
HEADER = s21_decimal.h
OBJ := $(patsubst %.c, %.o, $(SOURCE))
OS = $(shell uname)

ifeq ($(OS), Darwin)
	TEST_LIBS = -lcheck -lm
else
	TEST_LIBS = -lcheck -lsubunit -lpthread -lrt -lm -D_GNU_SOURCE
endif

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -g -c $< -o $@

all: s21_decimal.a test gcov_report

s21_decimal.a: $(OBJ) $(HEADER)
	ar rcs s21_decimal.a $(OBJ)
	ranlib s21_decimal.a
	rm -rf *.o

test: s21_decimal.a 
	gcc $(CFLAGS) Tests/tests.c s21_decimal.a $(TEST_LIBS) -o test.out
	./test.out

valgrind: clean s21_decimal.a
	$(CC) Tests/tests.c s21_decimal.a -o test $(TEST_LIBS)
	CK_FORK=no valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose --log-file=RESULT_VALGRIND.txt ./test

style: 
	cp ../materials/linters/.clang-format .
	clang-format -n *c *h
	rm -rf .clang-format

gcov_report: s21_decimal.a test
	gcc $(GCOVFLAGS) Tests/tests.c $(SOURCE) -o report.out $(TEST_LIBS)
	./report.out
	gcov -f $(SOURCE)
	lcov -t "gcov_report" -o Coverage_Report.info -c -d .
	genhtml -o ./report Coverage_Report.info
	rm -f *.gcno *.gcda *.info report.out *.gcov
	
clean: 
	rm -rf *.o *.out *.gcov *.gcno *.info *.gcda *.a test RESULT_VALGRIND.txt

rebuild: clean all
