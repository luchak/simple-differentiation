CXXFLAGS = -g -Wall -Wextra

test: differentiation_test
	./differentiation_test

differentiation_test: differentiation_test.cc differentiation.h vector.h
	$(CXX) $(CXXFLAGS) -lgtest $< -o $@

clean:
	rm -f differentiation_test

.PHONY : clean test
