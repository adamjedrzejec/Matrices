#pragma once

#include <iostream>

using namespace std;

class Matrix{
	struct rcmat;
private:
	rcmat *mat;
	void detach();
public:
	class Mref;
	Matrix();
	Matrix(unsigned int, unsigned int);
	Matrix(const Matrix&);
	~Matrix();
	bool checkDimensions(const Matrix&);
	bool canMultiply(const Matrix&);
	Mref operator()(unsigned int x, unsigned int y);
	//double operator()(unsigned int, unsigned int) const;
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
	//friend istream & operator>>(istream&, const Matrix&);
};



class Matrix::Mref {
	friend class Matrix;
	Matrix& mx;
	unsigned int sizeX, sizeY;
	Mref (Matrix& cmx, unsigned int x, unsigned int y): mx(cmx), sizeX(x), sizeY(y) {}
public:
	operator double() const;
	Matrix::Mref& operator=(double n);
	Matrix::Mref& operator=(const Mref& ref);
};