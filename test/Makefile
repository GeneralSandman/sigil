test_dict:test_dict.o dict.o
	g++ -o test_dict test_dict.o dict.o
test_server:test_server.o dict.o sigil.o
	g++ -o test_server test_server.o dict.o sigil.o
test_log:test_log.o log.o
	g++ -o test_log test_log.o log.o

test_dict.o:test_dict.cc
	g++ -std=c++11 -c -o test_dict.o test_dict.cc
test_server.o:test_server.cc
	g++ -std=c++11 -c -o test_server.o test_server.cc
test_log.o:test_log.cc
	g++ -std=c++11 -c -o test_log.o test_log.cc

dict.o:../dict.cc
	g++ -std=c++11 -c -o dict.o ../dict.cc
sigil.o:../sigil.cc
	g++ -std=c++11 -c -o sigil.o ../sigil.cc
log.o:../log.cc
	g++ -std=c++11 -c -o log.o ../log.cc

clean:
	rm *.o
