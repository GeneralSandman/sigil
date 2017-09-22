link = g++ -o
gcc11 = g++ -std=c++11 -c
gcc11o = $(gcc11) -o
readline = /usr/lib/x86_64-linux-gnu/libreadline.so -I -lreadline\
	-ltermcap -lncurses -g

datastruct = list dict rbtree
datastruct.o = $(foreach file,$(datastruct),$(file).o)
datastruct.cc = $(foreach file,$(datastruct),../$(file).cc)

lib = sigil command persist io log api exception
lib.o = $(foreach file,$(lib),$(file).o)
lib.cc = $(foreach file,$(lib),../$(file).cc)


server_test:server_test.o $(datastruct.cc) $(lib.cc)
	$(gcc11) $(datastruct.cc) $(lib.cc)
	$(link) server_test server_test.o $(datastruct.o) $(lib.o) $(readline)
	


binaryfile_test:binaryfile_test.o
	$(link) binaryfile_test binaryfile_test.o
dict_test:dict_test.o dict.o list.o sigil.o log.o persist.o io.o
	$(link) dict_test dict_test.o dict.o list.o sigil.o log.o persist.o io.o
list_test:list_test.o list.o log.o sigil.o persist.o io.o
	$(link) list_test list_test.o list.o log.o sigil.o persist.o io.o
rbtree_test:rbtree_test.o server_test
	$(link) rbtree_test rbtree_test.o rbtree.o log.o
log_test:log_test.o log.o
	$(link) log_test log_test.o log.o
virtual_test:virtual_test.o log.o
	$(link) virtual_test virtual_test.o log.o
io_test:io_test.o io.o log.o api.o
	$(link) io_test io_test.o io.o log.o api.o
persist_test:persist_test.o persist.o io.o log.o api.o sigil.o
	$(link) persist_test persist_test.o persist.o io.o log.o api.o sigil.o
readline_test:readline_test.cc
	g++ -std=c++11 -o readline_test readline_test.cc $(readline)

binaryfile_test.o:binaryfile_test.cc
	$(gcc11o) binaryfile_test.o binaryfile_test.cc
dict_test.o:dict_test.cc
	$(gcc11o) dict_test.o dict_test.cc
list_test.o:list_test.cc
	$(gcc11o) list_test.o list_test.cc
rbtree_test.o:rbtree_test.cc
	$(gcc11o) rbtree_test.o rbtree_test.cc
server_test.o:server_test.cc
	$(gcc11o) server_test.o server_test.cc
log_test.o:log_test.cc
	$(gcc11o) log_test.o log_test.cc
db_test.o:db_test.cc
	$(gcc11o) db_test.o db_test.cc
virtual_test.o:virtual_test.cc
	$(gcc11o) virtual_test.o virtual_test.cc
io_test.o:io_test.cc
	$(gcc11o) io_test.o io_test.cc
persist_test.o:persist_test.cc
	$(gcc11o) persist_test.o persist_test.cc



clean:
	rm *.o

cleanall:
	rm *_test
	rm *.o

