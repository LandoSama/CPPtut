#include <assert.h>
#include <iostream>


using namespace std;
class Matrix {
public:
	Matrix(int sizeX, int sizeY);
	Matrix();
	~Matrix();
	Matrix(const Matrix& m);
	Matrix& operator=(const Matrix& rhs);
	Matrix operator+(const Matrix & m);
	Matrix& operator+=(const Matrix & m);
	Matrix	operator-(const Matrix & m);
	Matrix&	operator-=(const Matrix & m);
	friend ostream &operator<<
		(ostream &out, const Matrix &m);
	long &operator()(int x, int y);
	bool is_square();
	int det();
	friend Matrix operator*
		(const Matrix & m1, const Matrix & m2);
	friend Matrix operator*
		(long c, const Matrix & m2);
	friend Matrix operator*
		(const Matrix & m1, long c);

private:
	int dx, dy, determ;  // dimensions, dx by dy and determinant 
	long **p;	// pointer to a pointer to a long integer
	void allocArrays() {
		assert(dx>0);
		assert(dy>0);
		p = new long*[dx];
		for (int i = 0; i < dx; i++)	{
			p[i] = new long[dy]; 
		}
	}
};

Matrix::Matrix(int sizeX=1, int sizeY=1)
: dx(sizeX),dy(sizeY)  {
	allocArrays();
	for (int i = 0; i < dx; i++)	{
		for (int j = 0; j < dy; j++) {
			p[i][j] = 0;
		}
	}
}

bool Matrix::is_square(){
		if(dx == dy){
			cout << "is square" << endl;
			return true;
		}
		else{
			cout << "not square" << endl;
			return false;
		}
}

int Matrix::det(){
	if(dy != dx){
		cout << "matrix must be square" << endl;
	}
	if(dy == 2 && dx == 2){
		determ = (p[0][0] * p[1][1]) - (p[0][1] * p[1][0]);
		cout << "determinant: " << determ << endl;
		return determ;
	}
	else if(dy == 3 && dx == 3){
		determ = (p[0][0]*(p[1][1]*p[2][2] - p[1][2]*p[2][1])) - (p[0][1]*(p[1][0]*p[2][2] - p[1][2]*p[2][0])) + (p[0][2]*(p[1][0]*p[2][1] - p[1][1]*p[2][0]));
		cout << "determinant: " << determ << endl;
		return determ;
	}
}

Matrix::Matrix(const Matrix& m) : dx(m.dx), dy(m.dy) {
	allocArrays();
	for (int i=0; i<dx; ++i) {
		for (int j=0; j<dy; ++j) {
			p[i][j] = m.p[i][j];
		}
	}
}

Matrix::~Matrix() {
	for (int i = 0; i < dx; i++) {
		delete [] p[i]; 
	}
	delete [] p;
	p = 0;
}

Matrix &Matrix::operator=(const Matrix& m) {
	if (this == &m) { 
		// avoid self-assignment
		return *this;
	} else {
		if (dx != m.dx || dy != m.dy) {
			this->~Matrix();
			dx = m.dx; dy = m.dy;
			allocArrays();
		}
		for (int i = 0; i < dx; i++) {
			for (int j = 0; j < dy; j++) {
				p[i][j] = m.p[i][j];
			}
		}
		return *this;
	}
}

Matrix& Matrix::operator+=(const Matrix& m) {
	assert(dx==m.dx);
	assert(dy==m.dy);
	// x+=y adds the y-entries into the x-entries
	for (int i=0; i<dx; ++i) {
		for (int j=0; j<dy; ++j) {
			p[i][j] += m.p[i][j];
		}
	}
	return *this;
}

Matrix Matrix::operator+(const Matrix& m) {
	Matrix temp(*this); //copy constructor
	return (temp += m);
}

Matrix &Matrix::operator-=(const Matrix &m){
	assert(dx==m.dx);
	assert(dy==m.dy);
	// x+=y adds the y-entries into the x-entires
	for(int i=0; i<dx; ++i){
		for(int j=0; j<dy; ++j){
			p[i][j] -= m.p[i][j];
		}
	}
	return *this;
}

Matrix Matrix::operator-(const Matrix &m){
	Matrix temp(*this); //copy constructor
	return(temp -= m);
}

ostream &operator<<
(ostream &out, const Matrix &m) 
{
	for (int i = 0; i < m.dx; ++i)	{
		for (int j = 0; j < m.dy; ++j)
			out << m.p[i][j] << "  ";
		out << endl;
	}
	return out;
}

long &Matrix::operator()(int i, int j) {
	assert(i>=0 && i<dx);
	assert(j>=0 && j<dy);
	return p[i][j];
}

Matrix operator*(const Matrix& m1, const Matrix& m2) {
	Matrix prod(m1.dx, m2.dy);
	for (int i=0; i<prod.dx; ++i) {
		for (int j=0; j<prod.dy; ++j) {
			for (int k=0; k<m1.dy; ++k) {
				prod.p[i][j] += m1.p[i][k] * m2.p[k][j];
			}
		}
	};
	return prod;
}

Matrix operator*(long c, const Matrix& m2) {
	Matrix prod(m2);
	for (int i=0; i<prod.dx; ++i) {
		for (int j=0; j<prod.dy; ++j) {
			prod.p[i][j] = c * m2.p[i][j];
		}
	}
	return prod;
}

Matrix operator*(const Matrix& m2, long c) {
	return c*m2;
}

int main() {
	Matrix x(2,2), y(2,2), z(1,1), b(3,3);
	x(0,0) = 1;
	x(0,1) = 1;
	x(1,0) = 1;
	x(1,1) = 1;
	y(0,0) = 3;
	y(0,1) = 4;
	y(1,0) = 1;
	y(1,1) = 1;
	b(0,0) = 2; b(1,0) = 3; b(2,2) = 9; b(2,1) = 5; b(1,1) = 1;
	cout << "Matrix x\n" << x << "\nMatrix y\n" << y << "\nMatrix b\n" << b << endl;
	cout << "x*y = \n" << x*y << endl;
	x.is_square();
	b.det();
	z = x*y;
	cout << "Matrix z = x*y  (note new dimensions)\n" << z << endl;
	Matrix x2(2,1);
	x2 = 2*x;
	cout << "Matrix x2 = 2*x\n" << x2 << endl;
	cout << "x + x2 = \n" << x+x2 << endl;
	return 0;
}
