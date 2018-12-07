#include "Matrix.h"
#include "Errors.h"

#include <iostream>

using namespace std;


Matrix::Matrix(){
	mat = NULL;
}


Matrix::Matrix(unsigned int sizeX, unsigned int sizeY){
	mat = new rcmat(sizeX, sizeY);
}


Matrix::Matrix(const Matrix& mx)
{
	this->mat = mx.mat;
	mx.mat->refCount++;
	this->detach();
}


Matrix::~Matrix()
{
	if(mat){
		mat->refCount--;

		if(mat->refCount == 0)
			delete mat;
		else
			mat = NULL;
	}
}


Matrix::rcmat::rcmat(unsigned int sizeX, unsigned int sizeY){
	
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	
	refCount = 1;

	data = new double* [sizeY];

	for (unsigned int i = 0; i < sizeY; i++) {
		data[i] = new double [sizeX];
	}
}


Matrix::rcmat::rcmat(unsigned int sizeX, unsigned int sizeY, double** data)
{
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	refCount = 1;

	this->data = new double*[sizeY];

	for(unsigned int i = 0; i < sizeY; i++)
	{
		this->data[i] = new double [sizeX];

		for(unsigned int j = 0; j < sizeX; j++)
		{
			this->data[i][j] = data[i][j];
		}
	}
}


Matrix::rcmat::~rcmat(){

	for (unsigned int i = 0; i < sizeY; i++) {
		delete[] data[i];
	}

	delete[] data;
}


double Matrix::operator()(unsigned int x, unsigned int y) const{
	if(this->mat->sizeX >= y && this->mat->sizeY >= x)
		return mat->data[x-1][y-1];
	else abort();
}


bool Matrix::checkDimensions(const Matrix& mx)
{
	return (mat->sizeX == mx.mat->sizeX && mat->sizeY == mx.mat->sizeY);
}


bool Matrix::canMultiply(const Matrix& mx)
{
	return (mat->sizeY == mx.mat->sizeX);
}


void Matrix::detach()
{	
	if(mat)
		if(mat->refCount > 1){
			mat->refCount--;
			mat = new rcmat(mat->sizeX, mat->sizeY, mat->data);
		}
}


bool Matrix::operator==(const Matrix& mx)
{
	return (this->mat) == (mx.mat);
}


Matrix& Matrix::operator+=(const Matrix& mx){

	if(this->checkDimensions(mx))
	{
		this->detach();
		for(unsigned int i = 0; i < this->mat->sizeY; i++)
		{
			for(unsigned int j = 0; j < this->mat->sizeX; j++)
			{
				this->mat->data[i][j] += mx.mat->data[i][j];
			}
		}
		return *this;
	}
	else abort();
		throw WrongMatrixDimensions();
}


Matrix& Matrix::operator-=(const Matrix& mx)
{
	if(this->checkDimensions(mx))
	{
		this->detach();
		for(unsigned int i = 0; i < this->mat->sizeY; i++)
		{
			for(unsigned int j = 0; j < this->mat->sizeX; j++)
			{
				this->mat->data[i][j] -= mx.mat->data[i][j];
			}
		}
		return *this;
	}
	else
		throw WrongMatrixDimensions();
}


Matrix& Matrix::operator*=(const Matrix& m)
{
	*this = *this * m;
	return *this;
}


Matrix Matrix::operator+(const Matrix& m)
{
	Matrix newMat(*this);
	newMat += m;
	return Matrix(newMat);
}


Matrix Matrix::operator-(const Matrix& mx)
{
	Matrix newMat(*this);
	newMat -= mx;
	return Matrix(newMat);
}


Matrix Matrix::operator*(const Matrix& mx)
{
	if(this->canMultiply(mx))
	{
		Matrix newMat(this->mat->sizeX, mx.mat->sizeY);

		for(unsigned int i = 0; i < this->mat->sizeY; i++)
		{
			for(unsigned int j = 0; j < mx.mat->sizeX; j++)
			{
				newMat.mat->data[i][j] = 0;
				for (unsigned int compI = 0; compI < mx.mat->sizeX; compI++)
				{
					newMat.mat->data[i][j] += (mx.mat->data[i][compI] * mx.mat->data[compI][j]);
				}
			}
		}
		return newMat;
	}
	else
		throw WrongMatrixDimensions();
}


void Matrix::operator=(const Matrix& mx)
{

	if(this->mat){
		this->mat->refCount--;
		if(this->mat->refCount == 0)
			delete this->mat;
	}

	this->mat = mx.mat;
	mx.mat->refCount++;
}


ostream & operator<<(ostream& out, const Matrix& mx) {

	out << endl;
	if(mx.mat){
		for(unsigned int i = 0; i < mx.mat->sizeY; i++) {
			for(unsigned int j = 0; j < mx.mat->sizeX; j++) {
				out << mx.mat->data[i][j];
				if (j != mx.mat->sizeX - 1)
					out << "	";
			}
			out << endl;
		}
	}
	else
		out << "Matrix is empty" << endl;
	return out;
}


istream & operator>>(istream& in, Matrix& mx) {
	unsigned int sizeX = 0, sizeY = 0;

	// if(in == cin)
	// 	cout << "Put dimensions: ";

	while(sizeX == 0 || sizeY == 0){
		try{
			while(true){
				if((in >> sizeY) && (in >> sizeX))
					break;
				else{
					fflush(stdin);
					in.clear();
					in.ignore();
					throw WrongInput();
				}
			}
		}
		catch(WrongInput& e){
			cerr << e.what() << endl;

			// if (in != cin)
			// 	abort();
		}
	}

	if(mx.mat)
		delete mx.mat;

	mx.mat = new Matrix::rcmat(sizeX, sizeY);

	cout << "Fill in " << mx.mat->sizeY << "x" << mx.mat->sizeX << " matrix:" << endl;
	for(unsigned int i = 0; i < mx.mat->sizeY; i++) {
		for(unsigned int j = 0; j < mx.mat->sizeX; j++) {
			try{
				while(true){
					if(in >> mx.mat->data[i][j])
						break;
					else{
						in.clear();
						in.ignore();
						throw WrongInput();
					}
				}
			}
			catch(WrongInput& e){
				cerr << e.what() << endl;
				abort();
			}
		}
	}
	return in;
}
