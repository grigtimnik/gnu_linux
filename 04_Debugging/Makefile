GENERATES = range provided_results1.txt provided_results2.txt
TRASH = *.o *~ o.* *.a *.so *.out
CFLAGS = -Wall -O0 -g
CC = gcc

range: range.c
	$(CC) $(CFLAGS) $< -o range

test: range
	gdb -x ./scenario1.gdb --args range 1 12 | grep -P "^@@@" > provided_results1.txt
	cmp expected_results1.txt provided_results1.txt

	gdb -x ./scenario2.gdb --args range -100 100 3 | grep -P "^@@@" > provided_results2.txt
	cmp expected_results2.txt provided_results2.txt

clean:
	rm -f $(GENERATES)
