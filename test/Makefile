test_binaryfile:test_binaryfile.o
	g++ -o test_binaryfile test_binaryfile.o

test_dict:test_dict.o dict.o log.o sigil.o
	g++ -o test_dict test_dict.o dict.o log.o sigil.o
test_list:test_list.o list.o log.o
	g++ -o test_list test_list.o list.o log.o
test_server:test_server.o dict.o list.o sigil.o log.o rdb.o
	g++ -o test_server test_server.o dict.o list.o sigil.o log.o rdb.o
test_log:test_log.o log.o
	g++ -o test_log test_log.o log.o
test_rdb:test_rdb.o rdb.o
	g++ -o test_rdb test_rdb.o rdb.o


test_binaryfile.o:test_binaryfile.cc
	g++ -std=c++11 -c -o test_binaryfile.o test_binaryfile.cc
test_dict.o:test_dict.cc
	g++ -std=c++11 -c -o test_dict.o test_dict.cc
test_list.o:test_list.cc
	g++ -std=c++11 -c -o test_list.o test_list.cc
test_server.o:test_server.cc
	g++ -std=c++11 -c -o test_server.o test_server.cc
test_log.o:test_log.cc
	g++ -std=c++11 -c -o test_log.o test_log.cc
test_rdb.o:test_rdb.cc
	g++ -std=c++11 -c -o test_rdb.o test_rdb.cc

dict.o:../dict.cc
	g++ -std=c++11 -c -o dict.o ../dict.cc
list.o:../list.cc
	g++ -std=c++11 -c -o list.o ../list.cc
sigil.o:../sigil.cc
	g++ -std=c++11 -c -o sigil.o ../sigil.cc
log.o:../log.cc
	g++ -std=c++11 -c -o log.o ../log.cc
rdb.o:../rdb.cc
	g++ -std=c++11 -c -o rdb.o ../rdb.cc

clean:
	rm *.o
