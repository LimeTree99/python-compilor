OUT = pycomp.exe

LIB = lib/regex.c\
		lib/log.c\
		lib/parse_settings.c

MAIN = lib/main.c

TEST_MAIN = test/main.c



CC = gcc
FLAGS = -g

compile = $(CC) $(FLAGS) $(MAIN) $(LIB) -o $(OUT)
compile_test = $(CC) $(FLAGS) $(TEST_MAIN) $(LIB) -o test/$(OUT)


make:
	$(compile)
	$(OUT) code_tests\test1.py

comp: lib/main.c
	$(compile)

run:
	$(OUT)

build:
	$(CC) $(FILES) -o bin/$(OUT)


test1: $(TEST_MAIN)
	$(compile_test)
	test/$(OUT)

comp_test1: $(TEST_MAIN)
	$(compile_test)