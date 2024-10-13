GENERATES = prog README prog-a prog-so
TRASH = *.o *~ o.* *.a *.so *.out
CFLAGS = -Wall -fPIC
CC = gcc

%.o:    %.c
	cc $(CFLAGS) $< -c -o $@

all:   README prog prog-a prog-so

liboutput_static: const.o fun.o
	ar rcs liboutput_static.a $^

liboutput: const.o fun.o
	cc -shared  $^ -o liboutput.so 

prog:   const.o fun.o prog.o
	$(CC) $^ -o $@

prog-a: prog.o liboutput_static
	$(CC) prog.o liboutput_static.a -o $@

prog-so: prog.o liboutput
	$(CC) prog.o -L. -loutput -o $@

README: prog
	./$< 2> $@

test: all
    # wihtout params
	./prog > prog_no_params.out 2>&1
	./prog-a > prog-a_no_params.out 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so > prog-so_no_params.out 2>&1
	cmp prog_no_params.out prog-a_no_params.out
	cmp prog-a_no_params.out prog-so_no_params.out

    # 1 param
	./prog testparam > prog_one_param.out 2>&1
	./prog-a testparam > prog-a_one_param.out 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so testparam > prog-so_one_param.out 2>&1
	cmp prog_one_param.out prog-a_one_param.out
	cmp prog-a_one_param.out prog-so_one_param.out

    # 3 params
	./prog param1 param2 param3 > prog_three_params.out 2>&1
	./prog-a param1 param2 param3 > prog-a_three_params.out 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so param1 param2 param3 > prog-so_three_params.out 2>&1
	cmp prog_three_params.out prog-a_three_params.out
	cmp prog-a_three_params.out prog-so_three_params.out

clean:
	rm -vf $(TRASH)

distclean:      clean
	rm -rf $(GENERATES)