GENERATES = move protect_remove.so
TRASH = *.txt
CFLAGS = -Wall
CC = gcc

LIBNAME = protect_remove.so

$(LIBNAME): protect_remove.c
	$(CC) -shared -fPIC $< -o $@ -ldl

move: move.c
	$(CC) $(CFLAGS) $< -o $@


test: move
	strace -e openat -P test1.txt -e fault=openat ./move test1.txt test2.txt || test "$$?" = "20"

	@touch test1.txt
	@rm -f test2.txt
	strace -e openat -P test2.txt -e fault=openat ./move test1.txt test2.txt || test "$$?" = "21"

	echo "SUI" > test1.txt
	strace -e trace=write -e fault=write ./move test1.txt test2.txt || test "$$?" = "23"

	echo "SUI" > test1.txt
	strace -e trace=close -P test2.txt -e fault=close ./move test1.txt test2.txt || test "$$?" = "23"

	echo "SUI" > test1.txt
	strace -e trace=unlink -P test1.txt -e fault=unlink ./move test1.txt test2.txt || test "$$?" = "24"

	echo "SUI" > test1.txt
	./move test1.txt should_stay.txt
	test -f should_stay.txt


test_protected: move protect_remove.so
	echo "SUI" > PROTECTED_FILE.txt
	LD_PRELOAD=$(PWD)/$(LIBNAME) ./move PROTECTED_FILE.txt test2.txt || test "$$?" = "24"

	echo "SUI" > not_prtcd_file.txt
	LD_PRELOAD=$(PWD)/$(LIBNAME) ./move not_prtcd_file.txt test2.txt || test "$$?" = "24"


clean:
	rm -f $(GENERATES)
	rm -rf $(TRASH)