C_COMPILER     = gcc
C_OPTIONS      = -Wall -pedantic -g --coverage -g -O0
C_LINK_OPTIONS = -lm 
CUNIT_LINK     = -lcunit

main: hash_table.c unit_tests.c
	$(C_COMPILER) $(C_OPTIONS) $^ $(CUNIT_LINK) -o compiled/main

tests: hash_table.c unit_tests.c
	$(C_COMPILER) $^ $(C_OPTIONS) $(CUNIT_LINK) -o compiled/tests
	./compiled/unit_tests.o

git:
	git add .
	git commit -m "updates"
	git push

valgrind: main
	valgrind --leak-check=full compiled/compiled.o