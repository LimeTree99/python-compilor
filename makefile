OUT = pycomp.exe

FILES = lib/main.c \
		lib/regex.c\
		lib/log.c\
		lib/string.c

CC = gcc

compile = $(CC) $(FILES) -o $(OUT)

make:
	$(compile)
	
	pycomp.exe code_tests\test1.py

comp: lib/main.c
	$(compile)

run:
	pycomp.exe

build:
	$(CC) $(FILES) -o bin/$(OUT)