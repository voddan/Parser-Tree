# g++ -Wall -Wno-unused-variable -c "%f"
# g++ -Wall -o "%e" "%f"

## libs list ##
libs_list = token.o expr_tree.o


## main ##
main: BUILD.H main.o $(libs_list)
	g++ -Wall -o "main" "main.o" $(libs_list)
	
main.o: BUILD.H main.cpp
	g++ -Wall -c "main.cpp"
	
	
## test ##
testing: test
	./test

test: BUILD.H test.o $(libs_list)
	g++ -Wall -o "test" "test.o" $(libs_list)
	
test.o: BUILD.H test.cpp
	g++ -Wall -c "test.cpp"
	
	
## token lib ##
token.o: BUILD.H token.cpp token.hpp
	g++ -Wall -c "token.cpp"
	
## expr_tree lib ##
expr_tree.o: BUILD.H expr_tree.cpp expr_tree.hpp
	g++ -Wall -c "expr_tree.cpp"

