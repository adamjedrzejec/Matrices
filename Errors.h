#pragma once
using namespace std;

struct WrongInput : public exception {
	const char* what () const throw () {
		return "Wrong input";
	}
};

struct WrongMatrixDimensions : public exception {
	const char* what () const throw () {
		return "Matrices have invalid dimensions";
	}
};

struct NoSuchElement : public exception {
	const char* what () const throw () {
		return "<< element of these coordinates does not exist >>";
	}
};

struct NoMatrixExists : public exception {
	const char* what () const throw () {
		return "Matrix has not been created properly";
	}
};