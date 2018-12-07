#pragma once
using namespace std;

struct WrongInput : public exception {
	const char* what () const throw () {
		return "Wrong input";
	}
};

struct DifferentMatrixDimensions : public exception {
	const char* what () const throw () {
		return "Matrices have invalid dimensions";
	}
};