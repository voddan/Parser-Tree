# g++ -Wall -Wno-unused-variable -c "%f"
# g++ -Wall -o "%e" "%f"

## libs list ##
libs_list = token.o


## main ##
main: main.o $(libs_list)
	g++ -Wall -o "main" "main.o" $(libs_list)
	
main.o: main.cpp
	g++ -Wall -c "main.cpp"
	
	
## test ##
testing: test
	./test

test: test.o $(libs_list)
	g++ -Wall -o "test" "test.o" $(libs_list)
	
test.o: test.cpp
	g++ -Wall -c "test.cpp"
	
	
## token lib ##
token.o: token.cpp token.hpp
	g++ -Wall -c "token.cpp"

