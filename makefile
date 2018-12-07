TestMatrix: TestMatrix.o Matrix.o
	g++ -g $^ -o $@

Matrix.o: Matrix.cpp Matrix.h Errors.h
	g++ -g -c -Wall -pedantic $< -o $@

TestMatrix.o: TestMatrix.cpp Matrix.h Errors.h
	g++ -g -c -Wall -pedantic $< -o $@

.PHONY: clean

clean:
	-rm Matrix.o TestMatrix.o TestMatrix