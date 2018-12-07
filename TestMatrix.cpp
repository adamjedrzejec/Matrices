#include "Matrix.h"
#include "Errors.h"

int main() {
	Matrix m1, m2(3,2), m3;
	cin >> m2;
	m1 = m2;
	m3 = m2;
	m1.detach();
	cout << "m2 matrix: " << m2 << endl << "m2(2,1): " << m2(2,1) << endl;
	m1 = m2 * m1;
	cout << "The sum of m1 and m2 equals: " << m1;
}
