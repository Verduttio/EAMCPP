#pragma include once

#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;


template <typename T, size_t N, size_t M>
class Matrix{

	T data[N*M];

public:
    using ValueType = T;

 public:
    constexpr size_t numberOfRows() const { return N; }
	constexpr size_t numberOfColumns() const { return M; }
	
	Matrix(int nrows=N, int ncols=M){
	  std::fill_n(data, N*M, T{});
	}
    Matrix(const std::initializer_list<std::initializer_list<T>> & list){
		T * p = data;
		for(const auto & row: list){
	  		T* p2 = std::copy(row.begin(), row.end(), p);
	  		std::fill(p2, p+=M, T{});
		}
    }

	Matrix(const Matrix & m){
		std::copy_n(m.data, N*M, data);
	}
	
	Matrix & operator= (const Matrix & m){
		if(&m != this){
			std::copy_n(m.data, N*M, data);
		}
		return *this;
	}

	const T& operator()(int i, int j) const {
	   return data[(i-1)*M+j-1];
	}

    T& operator()(int i, int j)  {
        return data[(i-1)*M+j-1];
    }

    constexpr friend Matrix operator+(const Matrix & a, const Matrix &b){
		Matrix r;
		for(int i = 1; i <= N; ++i){
			for(int j = 1; j <= M; ++j){
				r(i,j) = a(i,j) + b(i,j) ;
			}
		}
		return r;
	}

    ///Iterators
    template<typename Matrix>
    class MatrixIterator{
    public:
        using ValueType = typename Matrix::ValueType;
        using PointerType = ValueType*;
        using ReferenceType = ValueType&;
    public:
        MatrixIterator(PointerType ptr) : m_Ptr(ptr){}

        MatrixIterator& operator++(){
            m_Ptr++;
            return *this;
        }

        MatrixIterator operator++(int){
            MatrixIterator iterator = *this;
            ++(*this);
            return iterator;
        }

        MatrixIterator& operator--(){
            m_Ptr--;
            return *this;
        }

        MatrixIterator operator--(int){
            MatrixIterator iterator = *this;
            --(*this);
            return iterator;
        }

        PointerType operator->(){
            return m_Ptr;
        }

        ReferenceType operator*(){
            return *m_Ptr;
        }

        bool operator==(const MatrixIterator& other) const  {
            return m_Ptr == other.m_Ptr;
        }

        bool operator!=(const MatrixIterator& other) const {
            return !(*this == other);
        }

    private:
        PointerType m_Ptr;
    };

    template<typename Matrix>
    class MatrixConstIterator{
    public:
        using ValueType = typename Matrix::ValueType;
        using PointerType = ValueType*;
        using ReferenceType = ValueType&;
    public:
        MatrixConstIterator(PointerType ptr) : m_Ptr(ptr){}

        MatrixConstIterator& operator++(){
            m_Ptr++;
            return *this;
        }

        MatrixConstIterator operator++(int){
            MatrixIterator iterator = *this;
            ++(*this);
            return iterator;
        }

        MatrixConstIterator& operator--(){
            m_Ptr--;
            return *this;
        }

        MatrixConstIterator operator--(int){
            MatrixIterator iterator = *this;
            --(*this);
            return iterator;
        }

        PointerType operator->() const {
            return m_Ptr;
        }

        ReferenceType operator*() const {
            return *m_Ptr;
        }

        bool operator==(const MatrixConstIterator& other) const  {
            return m_Ptr == other.m_Ptr;
        }

        bool operator!=(const MatrixConstIterator& other) const {
            return !(*this == other);
        }

    private:
        PointerType m_Ptr;
    };

    template<typename Matrix>
    class MatrixRowIterator{
    public:
        using ValueType = typename Matrix::ValueType;
        using PointerType = ValueType*;
        using ReferenceType = ValueType&;
    public:
        MatrixRowIterator(PointerType ptr, int row) : m_Ptr(ptr+(row*M)){}

        MatrixRowIterator& operator++(){
            m_Ptr++;
            return *this;
        }

        MatrixRowIterator operator++(int){
            MatrixIterator iterator = *this;
            ++(*this);
            return iterator;
        }

        MatrixRowIterator& operator--(){
            m_Ptr--;
            return *this;
        }

        MatrixRowIterator operator--(int){
            MatrixIterator iterator = *this;
            --(*this);
            return iterator;
        }

        PointerType operator->(){
            return m_Ptr;
        }

        ReferenceType operator*(){
            return *m_Ptr;
        }

        bool operator==(const MatrixRowIterator& other) const  {
            return m_Ptr == other.m_Ptr;
        }

        bool operator!=(const MatrixRowIterator& other) const {
            return !(*this == other);
        }

    private:
        PointerType m_Ptr;
    };


    template<typename Matrix>
    class MatrixColIterator{
    public:
        using ValueType = typename Matrix::ValueType;
        using PointerType = ValueType*;
        using ReferenceType = ValueType&;
    public:
        MatrixColIterator(PointerType ptr, int col) : m_Ptr(ptr+col){}

        MatrixColIterator& operator++(){
            m_Ptr += M;
            return *this;
        }

        MatrixColIterator operator++(int){
            MatrixIterator iterator = *this;
            ++(*this);
            return iterator;
        }

        MatrixColIterator& operator--(){
            m_Ptr -= M;
            return *this;
        }

        MatrixColIterator operator--(int){
            MatrixIterator iterator = *this;
            --(*this);
            return iterator;
        }

        PointerType operator->(){
            return m_Ptr;
        }

        ReferenceType operator*(){
            return *m_Ptr;
        }

        bool operator==(const MatrixColIterator& other) const  {
            return m_Ptr == other.m_Ptr;
        }

        bool operator!=(const MatrixColIterator& other) const {
            return !(*this == other);
        }

    private:
        PointerType m_Ptr;
    };


public:
    using Iterator = MatrixIterator<Matrix<T,N,M>>;
    using ConstIterator = MatrixConstIterator<Matrix<T,N,M>>;
    using RowIterator = MatrixRowIterator<Matrix<T, N, M>>;
    using col_iterator = MatrixColIterator<Matrix<T, N, M>>;

    Iterator begin(){
        return Iterator(data);
    }

    Iterator end() {
        return Iterator(data + N*M);
    }

    ConstIterator begin() const{
        return ConstIterator(data);
    }

    ConstIterator end() const{
        return ConstIterator(data + N*M);
    }

    RowIterator row_begin(int n) {
        return RowIterator(data, n-1);
    }

    RowIterator row_end(int n) {
        return RowIterator(data, n);
    }

    col_iterator col_begin(int n) {
        return col_iterator(data, n-1);
    }

    col_iterator col_end(int n) {
        return col_iterator(data + N*M, n-1);
    }

};

template <typename T, size_t N, size_t M>
void printMatrix(const Matrix<T,N,M> & m, int width = 10){   // added const
	for(int i = 1; i <= m.numberOfRows(); ++i){
		for(int j = 1; j <= m.numberOfColumns(); ++j){
			if(j != 1) 
				cout << " ";
			cout << setw(width) <<  m(i,j) ;
		}
		cout << endl;
	}
}




