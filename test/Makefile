link = g++ -o
gcc11 = g++ -std=c++11 -c -o

binaryfile_test:binaryfile_test.o
	$(link) binaryfile_test binaryfile_test.o
dict_test:dict_test.o dict.o log.o sigil.o
	$(link) dict_test dict_test.o dict.o log.o sigil.o
list_test:list_test.o list.o log.o sigil.o persist.o io.o
	$(link) list_test list_test.o list.o log.o sigil.o persist.o io.o
server_test:server_test.o dict.o list.o sigil.o log.o persist.o io.o
	$(link) server_test server_test.o dict.o list.o sigil.o log.o persist.o io.o
log_test:log_test.o log.o
	$(link) log_test log_test.o log.o
virtual_test:virtual_test.o log.o
	$(link) virtual_test virtual_test.o log.o
io_test:io_test.o io.o log.o api.o
	$(link) io_test io_test.o io.o log.o api.o
persist_test:persist_test.o persist.o io.o log.o api.o
	$(link) persist_test persist_test.o persist.o io.o log.o api.o

# test= binaryfile_test dict_test list_test server_test log_test db_test virtual_test\
# 	io_test persist_test

# $(complietest XXX_test)
# 	$(gcc11) $(XXX_test).o $(XXX_test).cc

# all:
# 	$(foreach file,$(test),$(gcc11) $(file).o $(file).cc)

binaryfile_test.o:binaryfile_test.cc
	$(gcc11) binaryfile_test.o binaryfile_test.cc
dict_test.o:dict_test.cc
	$(gcc11) dict_test.o dict_test.cc
list_test.o:list_test.cc
	$(gcc11) list_test.o list_test.cc
server_test.o:server_test.cc
	$(gcc11) server_test.o server_test.cc
log_test.o:log_test.cc
	$(gcc11) log_test.o log_test.cc
db_test.o:db_test.cc
	$(gcc11) db_test.o db_test.cc
virtual_test.o:virtual_test.cc
	$(gcc11) virtual_test.o virtual_test.cc
io_test.o:io_test.cc
	$(gcc11) io_test.o io_test.cc
persist_test.o:persist_test.cc
	$(gcc11) persist_test.o persist_test.cc

dict.o:../dict.cc
	$(gcc11) dict.o ../dict.cc
list.o:../list.cc
	$(gcc11) list.o ../list.cc
sigil.o:../sigil.cc
	$(gcc11) sigil.o ../sigil.cc
log.o:../log.cc
	$(gcc11) log.o ../log.cc
persist.o:../persist.cc
	$(gcc11) persist.o ../persist.cc
io.o:../io.cc
	$(gcc11) io.o ../io.cc
api.o:../api.cc
	$(gcc11) api.o ../api.cc

clean:
	rm *.o

cleanall:
	rm *_test
	rm *.o

