pa14: pa14.o Container.hpp
	$(CXX) $(CXXFLAGS) pa14.o -o pa14

pa14.o: pa14.cpp
	$(CXX) $(CXXFLAGS) pa14.cpp -c

test: test.o Container.hpp
	$(CXX) $(CXXFLAGS) Container_test.o -o test

test.o: Container_test.cpp
	$(CXX) $(CXXFLAGS) Container_test.cpp -c

clean:
	rm -f pa14.o pa14

turnin:
	turnin -c cs202 -p pa14 -v Container.hpp pa14.cpp Container_test.cpp \
		Makefile
