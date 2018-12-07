#pragma once

#include <iostream>

using namespace std;

class Matrix{
	struct rcmat;
private:
	rcmat *mat;
public:
	Matrix();
	Matrix(unsigned int, unsigned int);
	Matrix(const Matrix&);
	~Matrix();
	bool checkDimensions(const Matrix&);
	bool canMultiply(const Matrix&);
	void detach();
	double operator()(unsigned int, unsigned int) const;
	bool operator==(const Matrix& m);
	Matrix& operator+=(const Matrix&);
	Matrix& operator-=(const Matrix&);
	Matrix& operator*=(const Matrix&);
	Matrix operator+(const Matrix&);
	Matrix operator-(const Matrix&);
	Matrix operator*(const Matrix&);
	void operator= (const Matrix&);
	friend ostream & operator<<(ostream&, const Matrix&);
	friend istream & operator>>(istream&, Matrix&);
};


struct Matrix::rcmat {
	double **data;
	unsigned int sizeX, sizeY, refCount;
	rcmat(unsigned int, unsigned int);
	rcmat(unsigned int, unsigned int, double**);
	~rcmat();
	friend istream & operator>>(istream&, const Matrix&);
};

