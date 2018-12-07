TestMatrix: TestMatrix.o Matrix.o
	g++ -g $^ -o $@ -std="c++11"

Matrix.o: Matrix.cpp Matrix.h Errors.h
	g++ -g -c -Wall -pedantic $< -o $@ -std="c++11"

TestMatrix.o: TestMatrix.cpp Matrix.h Errors.h
	g++ -g -c -Wall -pedantic $< -o $@ -std="c++11"

.PHONY: clean

clean:
	-rm Matrix.o TestMatrix.o TestMatrix
