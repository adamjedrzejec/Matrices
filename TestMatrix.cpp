#include "Matrix.h"
#include "Errors.h"

using namespace std;

int main() {
	try{
		Matrix m1, m2(3,2), m3, m4;
		cin >> m2;
		m1 = m2;
		m3 = m2;
		
		
		cout << "m2 matrix: " << m2 << endl;
		
		cout << "m2(2,1): " << m2(2,1) << endl << endl;
		
		//m2(2,1) = 3;
		
		m4 = m2;
		m4 += m1;
		
		cout << "The sum of m1 and m2 equals: " << m1 + m2 << endl;
		
		cout << "The same value has m4: " << m4 << endl;
		
	} catch(exception& e) {
		cerr << e.what() << endl;
		abort();
	} 
	return 0;
}
