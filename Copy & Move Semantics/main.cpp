#include <iostream>
#include <algorithm> // for fill method
#include <initializer_list>
#include <utility>

class Matrix {
    int N = 0;
    int M = 0;
    double* data = nullptr;

public:
    Matrix() {
        std::cout << "Matrix default constructor\n";
    }

    Matrix(int N_con, int M_con)
            : N(N_con), M(M_con), data(new double [N_con*M_con]) {
        std::cout << "Matrix " << N << "x" << M << " two argument constructor\n";
        std::fill(data+0, data+N*M, 0);
    }

    Matrix(std::initializer_list<std::initializer_list<double>> data_con) {
        int max_column_size = getMaxSize_InitializerList(data_con);
        N = data_con.size();
        M = max_column_size;
        std::cout << "Matrix " << N << "x" << M << " initializer_list constructor\n";
        data = new double [N*M];
        prepareData_InitializerListConstructor(data_con);
    }

    Matrix(const Matrix& copy) : N(copy.N), M(copy.M), data(new double[copy.N*copy.M]){
        std::cout << "Matrix " << N << "x" << M << " copy constructor\n";
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < M; j++) {
                data[i*M+j] = copy.data[i*M+j];
            }
        }
    }

    Matrix(Matrix&& other) noexcept{
        std::cout << "Move constructor\n";
        N = other.N;
        M = other.M;
        data = other.data;

        other.N = 0;
        other.M = 0;
        other.data = nullptr;
    }


    ~Matrix() {
        //std::cout << "Matrix " << N << "x" << M << " destructor\n";
        delete [] data;
    }

    double operator()(int row, int column) const {
        int normalizedRow = row-1;
        int normalizedColumn = column-1;
        return data[M*normalizedRow + normalizedColumn];
    }


    Matrix operator-() {
        Matrix out(N, M);
        for(int i = 0; i < N*M; i++) {
            out.data[i] = data[i]*-1;
        }

        return out;
    }


    Matrix& operator=(const Matrix& copy) {
        std::cout << "Copy assignment operator\n";
        // Guard self assignment
        if(this == &copy)
            return *this;

        if(!(N == copy.N && M == copy.M)) {
            delete[] data;
            N = copy.N;
            M = copy.M;
            data = new double[N * M];
        }
        std::copy(copy.data, copy.data+N*M, data);
        return *this;
    }

    Matrix& operator=(Matrix&& other) noexcept {
        std::cout << "Move assignment operator\n";
        if(this != &other) {
            delete [] data;

            N = other.N;
            M = other.M;
            data = other.data;

            other.N = 0;
            other.M = 0;
            other.data = nullptr;
        }
        return *this;
    }

    friend std::ostream& operator << (std::ostream& out, const Matrix& matrix);


private:
    int getMaxSize_InitializerList(const std::initializer_list<std::initializer_list<double>>& list) {
        int size = list.begin()->size();
        for(const auto& row : list) {
            size = max(row.size(), size);
        }
        return size;
    }

    int max(const int& a, const int& b) {
        return a<b ? b : a;
    }

    void prepareData_InitializerListConstructor(std::initializer_list<std::initializer_list<double>>& list) {
        int iterator = 0;
        for(auto& row : list) {
            // copying existing data from list
            for(int i = 0; i < row.size(); i++) {
                const double* element = row.begin()+i;
                //std::cout << *element << std::endl;
                data[iterator++] = *element;
            }
            // filling remaining space with zeros
            for(int i = row.size(); i < M; i++) {
                data[iterator++] = 0;
            }
        }
    }
};

std::ostream& operator << (std::ostream& out, const Matrix& matrix){
    for(int i = 0; i < matrix.N; i++) {
        out << "{ ";
        for(int j = 0; j < matrix.M; j++) {
            out << matrix.data[matrix.M*i + j] << ", ";
        }
        out << "}\n";
    }
    return out;
}


class MatrixWithLabel : Matrix{
    std::string label = "A";

public:
    using Matrix::Matrix; // inheriting all constructors
    MatrixWithLabel(std::string label, int N, int M) : Matrix(N, M), label(std::move(label)) {
        std::cout << "MatrixWithLabel " << N << "x" << M << " two argument constructor\n";
    }

    MatrixWithLabel(std::string label, std::initializer_list<std::initializer_list<double>> data_con)
        : Matrix(data_con), label(std::move(label)){
        std::cout << "MatrixWithLabel initializer_list constructor\n";
    }

//     default move constructor stops working
    MatrixWithLabel(const MatrixWithLabel& copy) : Matrix(copy), label(copy.label) {
        std::cout << "MatrixWithLabel copy constructor\n";
    }

    // when we add move constructor everything works properly
    MatrixWithLabel(MatrixWithLabel&& other) = default;

    MatrixWithLabel& operator=(const MatrixWithLabel& other) = default;

    MatrixWithLabel& operator=(MatrixWithLabel&& other) = default;

    std::string getLabel() {
        return label;
    }

    void setLabel(std::string label_con) {
        label = std::move(label_con);
    }
};



using namespace std;

int main() {
    Matrix m1;
    Matrix m2(3,4);
    Matrix m3({{1,2,3},{32, 23, 22},{3,234,23,44}});
    cout << m2(1,1) << endl;  // 0
    cout << m3(2,2) << endl;  // 23
    cout << m3;


    cout << "----Copy semantics----\n";
    Matrix m4 = m2;
    cout << m4 << endl;
    m4 = m3;
    cout << m4;

    cout << "----Move semantics---- \n";
    Matrix m7 = std::move(m2);
    m4 = -m3;

    cout << "----Copy elision---- \n";
    Matrix m6 = -m4;
    Matrix * pm = new Matrix(-m4);
    cout << m6(2,1) << endl; // 32

    cout << "----Inheritance---- \n";
    MatrixWithLabel l0("B", 3, 4);
    MatrixWithLabel l1({{1,2},{4,5}});
    l1.setLabel("A");
    MatrixWithLabel l2 = l1;
    MatrixWithLabel l3 = std::move(l1);
    cout << l2.getLabel() << " " << l3.getLabel() << endl;
//     	cout << l1.getLabel() << endl;



    cout << "----END----\n";



//    Matrix m8;
//
//    cout << "m3: \n";
//    cout << m3;
//    cout << "m8: \n";
//    cout << m8;
//
//    m8 = std::move(m3);
//
//    cout << "m3: \n";
//    cout << m3;
//    cout << "m8: \n";
//    cout << m8;

    return 0;
}
