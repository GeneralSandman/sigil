gg = g++ -o
goo = g++ -std=c++11 -c -o

test_binaryfile:test_binaryfile.o
	$(gg) test_binaryfile test_binaryfile.o

test_dict:test_dict.o dict.o log.o sigil.o
	$(gg) test_dict test_dict.o dict.o log.o sigil.o
test_list:test_list.o list.o log.o
	$(gg) test_list test_list.o list.o log.o
test_server:test_server.o dict.o list.o sigil.o log.o rdb.o
	$(gg) test_server test_server.o dict.o list.o sigil.o log.o rdb.o
test_log:test_log.o log.o
	$(gg) test_log test_log.o log.o
test_rdb:test_rdb.o rdb.o
	$(gg) test_rdb test_rdb.o rdb.o


test_binaryfile.o:test_binaryfile.cc
	$(goo) test_binaryfile.o test_binaryfile.cc
test_dict.o:test_dict.cc
	$(goo) test_dict.o test_dict.cc
test_list.o:test_list.cc
	$(goo) test_list.o test_list.cc
test_server.o:test_server.cc
	$(goo) test_server.o test_server.cc
test_log.o:test_log.cc
	$(goo) test_log.o test_log.cc
test_rdb.o:test_rdb.cc
	$(goo) test_rdb.o test_rdb.cc

dict.o:../dict.cc
	$(goo) dict.o ../dict.cc
list.o:../list.cc
	$(goo) list.o ../list.cc
sigil.o:../sigil.cc
	$(goo) sigil.o ../sigil.cc
log.o:../log.cc
	$(goo) log.o ../log.cc
rdb.o:../rdb.cc
	$(goo) rdb.o ../rdb.cc

.PHONY: clean
clean:
	rm *.o

.PHONY: cleanall
cleanall:
	find . -maxdepth 1 -type f -perm /111 -exec rm {} \;
	rm *.o

