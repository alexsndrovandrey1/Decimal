CFLAGS = -Wall -Wextra -Werror -pedantic -std=c11
GCOVFLAGS = -fprofile-arcs -ftest-coverage
OS=$(shell uname)

HEADERS = s21_decimal.h $(wildcard ./headers/*.c)
SOURCES_ALL = $(wildcard ./additional/*.c) 	     \
	$(wildcard ./arithmetic_func/*.c)			 \
	$(wildcard ./comparision_func/*.c)			 \
	$(wildcard ./convertor_func/*.c)			 \
	$(wildcard ./comparison_func/*.c)			 \
	$(wildcard ./other_func/*.c) 				 \


OBJ_LIBRARY := $(patsubst %.c, %.o, $(SOURCES_ALL))

ifeq ($(OS), Linux)
	FLAGS = -lsubunit -lpthread
else
	АLAGS = -lpthread
endif


%.o: %.c $(HEADER)
	gcc $(CFLAGS) -c $< -o $@


all: s21_decimal.a test gcov_report

s21_decimal.a: $(OBJ_LIBRARY) $(HEADERS)
	ar rcs s21_decimal.a $(OBJ_LIBRARY)
	ranlib s21_decimal.a
	rm -rf ./*/*.o

test: s21_decimal.a tests/test.c
	gcc $(CFLAGS) tests/test.c s21_decimal.a -o test.out -lm -lcheck $(FLAGS)
	./test.out

gcov_report: s21_decimal.a tests/test.c
	gcc $(GCOVFLAGS) tests/test.c $(SOURCES_ALL) -o report.out -lm -lcheck $(FLAGS)
	./report.out
	gcov -f $(SOURCES_ALL)
	lcov -t "gcov_report" -o Coverage_Report.info -c -d .
	genhtml -o ./report Coverage_Report.info
	rm -f *.gcno *.gcda *.info report.out *.gcov
	open ./report/index-sort-f.html
	
check:
	clang-format -style=Google -n .c .h

format:
	clang-format -style=Google -i .c .h

rebuild: clean all

clean:
	rm -f *.o *.a *.gcno *.gcda *.info *.out *.gcov
	rm -rf ./report
