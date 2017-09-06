test_dict:test_dict.o dict.o
	g++ -o test_dict test_dict.o dict.o
test_server:test_server.o dict.o sigil.o
	g++ -o test_server test_server.o dict.o sigil.o


test_dict.o:test_dict.cc
	g++ -std=c++11 -c -o test_dict.o test_dict.cc
test_server.o:test_server.cc
	g++ -std=c++11 -c -o test_server.o test_server.cc

dict.o:../dict.cc
	g++ -std=c++11 -c -o dict.o ../dict.cc
sigil.o:../sigil.cc
	g++ -std=c++11 -c -o sigil.o ../sigil.cc


clean:
	rm *.o
