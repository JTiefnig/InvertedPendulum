#pragma once
#include <vector>
#include <exception>
#include <utility>
#include <sstream>
#include <ostream>

typedef std::size_t uint; // std::size_t // needed for iteration

// Februar 2019 
// Author Johannes Tiefnig
// Simple flexible matrix implementation




class MathException : public std::exception
{
public:
	MathException(const char* msg)
		:exception(msg)
	{}
};



template <class T>
class Matrix
{
protected:

	int m; // Rows // Reihen // Zeilen
	int n; // Columns // Spalten

	std::vector<std::vector<T>> v;

public:

	Matrix<T>(int M, int N);
	Matrix<T>(int M, int N, const T&);
	Matrix<T>();
	Matrix(const Matrix<T>&);
	Matrix<T>(Matrix<T> &&); // Move constructor

	Matrix<T>& operator=(Matrix<T>&& other);
	Matrix<T>& operator=(const Matrix<T>& other);

	virtual ~Matrix();

	int rows() const;
	int cols() const;

	void resize(int, int);


	T getVal(int i, int j) const;

	T& operator() (int i, int j);

	T operator() (int i, int j) const;

	std::vector<T>& operator [] (int);
	const std::vector<T>& operator [] (int) const;

	// Math Operators

	Matrix<T> operator + (const Matrix<T>& b) const;
	Matrix<T> operator - (const Matrix<T>& b) const;
	Matrix<T> operator * (const Matrix<T>& b) const;
	Matrix<T> operator += (const Matrix<T>&);
	Matrix<T> operator -= (const Matrix<T>&);
	Matrix<T> operator *= (const Matrix<T>&);

	Matrix<T> operator * (const T & s) const;
	Matrix<T> operator *= (const T & s);


	void RowSwap(int i1, int i2);
	void ColumnSwap(int j1, int j2);



	Matrix<T> transpose() const;

};


template <class T>
Matrix<T>::Matrix(int M, int N)
	:m(M), n(N), v(M)
{
	for (int i = 0; i < M; i++)
		v[i].resize(N);
}

template<class T>
inline Matrix<T>::Matrix(int M, int N, const T & temp)
	:m(M), n(N), v(M)
{
	for (int i = 0; i < M; i++)
	{
		v[i].resize(N);
		for (int j = 0; j < N; j++)
			v[i][j] = temp;
	}

}

template<class T>
Matrix<T>::Matrix()
{
}

template<class T>
inline Matrix<T>::Matrix(Matrix<T>&& temp)
	:v(std::move(temp.v)), m(temp.m), n(temp.n)
{

}

template<class T>
inline Matrix<T>& Matrix<T>::operator=(Matrix<T>&& other)
{
	v = std::move(other.v);
	m = other.m;
	n = other.n;

	return *this;
}

template<class T>
Matrix<T>::~Matrix()
{

}

template<class T>
Matrix<T>::Matrix(const Matrix & temp)
	:m(temp.m), n(temp.n), v(temp.v)
{
}

template<class T>
int Matrix<T>::rows() const
{
	return this->m;
}

template<class T>
int Matrix<T>::cols() const
{
	return this->n;
}

template<class T>
void Matrix<T>::resize(int M, int N)
{
	v.resize(M);

	for (int i = 0; i < M; i++)
		v[i].resize(N);

	m = M;
	n = N;
}




template<class T>
T Matrix<T>::getVal(int i, int j) const
{
	return v[i][j];
}

template<class T>
T & Matrix<T>::operator()(int i, int j)
{
	return v[i][j];
}

template<class T>
T Matrix<T>::operator()(int i, int j) const
{
	return v[i][j];
}

template<class T>
std::vector<T>& Matrix<T>::operator[](int i)
{
	return v[i];
}

template<class T>
const std::vector<T>& Matrix<T>::operator[](int i) const
{
	return v[i];
}


template<class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> & b) const
{
	if (n != b.n || m != b.m)
		throw MathException("Matrix dimensions did not Match");

	Matrix ret(this->m, this->n);

	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			ret[i][j] = v[i][j] + b[i][j];

	return ret;
}


template<class T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> & b) const
{
	if (n != b.n || m != b.m)
		throw MathException("Matrix dimensions did not Match");

	Matrix ret(this->m, this->n);

	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			ret(i, j) = v[i][j] - b[i][j];

	return ret;
}

template<class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& b) const
{
	if (this->n != b.m)
		throw MathException("Matrix dimensions did not Match");

	int nm = this->m;
	int nn = b.n;
	Matrix ret(nm, nn);

	for (int i = 0; i < nm; i++)
	{
		for (int j = 0; j < nn; j++)
		{
			for (int c = 0; c < b.m; c++)
			{
				ret[i][j] += v[i][c] * b[c][j];
			}
		}
	}
	return ret;
}


template<class T>
Matrix<T> Matrix<T>::operator*(const T & s) const
{
	Matrix ret(this->m, this->n);

	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			ret[i][j] = v[i][j] * s;

	return ret;
}

template<class T>
Matrix<T> Matrix<T>::operator*=(const T & s)
{
	*this = (*this) * s;

	return *this;
}

template<class T>
inline Matrix<T> Matrix<T>::operator+=(const Matrix<T>& m)
{
	return *this = *this + m;
}

template<class T>
inline Matrix<T> Matrix<T>::operator-=(const Matrix<T>& m)
{
	return *this = *this - m;
}

template<class T>
inline Matrix<T> Matrix<T>::operator*=(const Matrix<T>& m)
{
	return *this = *this * m;
}


template<class T>
void Matrix<T>::RowSwap(int i1, int i2)
{
	if (i1 == i2) return;

	T temp;
	for (int j = 0; j < n; j++)
	{
		temp = v[i1][j];
		v[i1][j] = v[i2][j];
		v[i2][j] = temp;
	}
}

template<class T>
void Matrix<T>::ColumnSwap(int j1, int j2)
{
	if (j1 == j2) return;

	T temp;
	for (int i = 0; i < m; i++)
	{
		temp = v[i][j1];
		v[i][j1] = v[i][j2];
		v[i][j2] = temp;
	}
}




template<class T>
Matrix<T> Matrix<T>::transpose() const
{
	Matrix ret(this->n, this->m);

	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			ret[j][i] = v[i][j];


	return ret;
}

template <class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other)
{
	
	if (other.cols() != this->cols() && other.rows() != this->cols())
		throw MathException("dimensionError");

		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				v[i][j] = other[i][j];

	

	return *this;
}


template <class T>
Matrix<T> operator*(T scale, const Matrix<T>& mat)
{
	return mat * scale;
}

template <class T>
std::ostream& operator<<(std::ostream& os, Matrix<T> const& mat)
{
	for (size_t m = 0; m < mat.rows(); m++)
	{
		for (size_t n = 0; n < mat.cols(); n++)
		{
			os << mat(m, n);
			if (n + 1 < mat.cols())
				os << ", ";
		}

		os << std::endl;
	}

	return os;
}