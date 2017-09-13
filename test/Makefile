gg = g++ -o
goo = g++ -std=c++11 -c -o

binaryfile_test:binaryfile_test.o
	$(gg) binaryfile_test binaryfile_test.o
dict_test:dict_test.o dict.o log.o sigil.o
	$(gg) dict_test dict_test.o dict.o log.o sigil.o
list_test:list_test.o list.o log.o
	$(gg) list_test list_test.o list.o log.o
server_test:server_test.o dict.o list.o sigil.o log.o rdb.o
	$(gg) server_test server_test.o dict.o list.o sigil.o log.o rdb.o
log_test:log_test.o log.o
	$(gg) log_test log_test.o log.o
virtual_test:virtual_test.o log.o
	$(gg) virtual_test virtual_test.o log.o
io_test:io_test.o io.o log.o api.o
	$(gg) io_test io_test.o io.o log.o api.o
persist_test:persist_test.o persist.o io.o log.o api.o
	$(gg) persist_test persist_test.o persist.o io.o log.o api.o

binaryfile_test.o:binaryfile_test.cc
	$(goo) binaryfile_test.o binaryfile_test.cc
dict_test.o:dict_test.cc
	$(goo) dict_test.o dict_test.cc
list_test.o:list_test.cc
	$(goo) list_test.o list_test.cc
server_test.o:server_test.cc
	$(goo) server_test.o server_test.cc
log_test.o:log_test.cc
	$(goo) log_test.o log_test.cc
rdb_test.o:rdb_test.cc
	$(goo) rdb_test.o rdb_test.cc
virtual_test.o:virtual_test.cc
	$(goo) virtual_test.o virtual_test.cc
io_test.o:io_test.cc
	$(goo) io_test.o io_test.cc
persist_test.o:persist_test.cc
	$(goo) persist_test.o persist_test.cc

dict.o:../dict.cc
	$(goo) dict.o ../dict.cc
list.o:../list.cc
	$(goo) list.o ../list.cc
sigil.o:../sigil.cc
	$(goo) sigil.o ../sigil.cc
log.o:../log.cc
	$(goo) log.o ../log.cc
persist.o:../persist.cc
	$(goo) persist.o ../persist.cc
io.o:../io.cc
	$(goo) io.o ../io.cc
api.o:../api.cc
	$(goo) api.o ../api.cc

clean:
	rm *.o

cleanall:
	find . -maxdepth 1 -type f -perm /111 -exec rm {} \;
	rm *.o

