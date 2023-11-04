OUT = pycomp.exe

LIB = lib/regex.c\
		lib/log.c\
		lib/string.c

MAIN = lib/main.c

TEST_MAIN = test/main.c



CC = gcc

compile = $(CC) $(MAIN) $(LIB) -o $(OUT)
compile_test = $(CC) $(TEST_MAIN) $(LIB) -o test/$(OUT)


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