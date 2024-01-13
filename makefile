tester: sha1/sha1.c sha1/sha1.h hashtable.c hashtable.h  test.c
	gcc -ansi -pedantic -Wall -g $^ -o $@

clean:
	rm -f tester