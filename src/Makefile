TARGET = S21_SmartCalc_v1.0

CC = gcc
FLAGS = -Wall -Werror -Wextra
SRC = ./Backend/s21_*.c
OBJ = *.o
LFLAGS = -lcheck

ifeq ($(shell uname), Linux) 
	LFLAGS += -pthread  -lsubunit -lrt -lm
endif

all: install

install:
	@echo "Installation of S21_SmartCalc_v1.0:"
	@mkdir -p ../build
	@cd Frontend/s21_smart_calc && qmake && make && make clean && rm -rf Makefile && mv s21_smart_calc ../../../build/$(TARGET).app
	@echo "Installation completed! You can find app in the ../build/ folder!"
	
uninstall:
	@rm -rf ../build
	@echo "Uninstall completed!"
	
dvi:
	open ../README_RUS.md
	
dist: 
	@mkdir -p ../dist
	@cp -R ../build/$(TARGET).app ../dist
	@cp ../README_RUS.md ../dist 
	@cd ../dist && tar cvzf $(TARGET).tgz *
	@cd ../dist && rm -rf $(TARGET).app README_RUS.md
	@echo "Archive creation completed successfully!"

test: s21_polish.a
	$(CC) $(FLAGS) -c ./Backend/calc_tests.c
	$(CC) calc_tests.o $(FLAGS) $(LFLAGS) -L. s21_polish.a -o test

s21_polish.a:
	$(CC) $(FLAGS) -c $(SRC)
	ar rcs s21_polish.a $(OBJ)
	ranlib s21_polish.a
	rm -rf *.o

add_coverage:
	$(eval FLAGS += --coverage)

gcov_report: clean add_coverage test
	-./test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html

clean:
	rm -rf *.o *.a *.gcno *.gcda test test.info report
