#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <vector>
#include <iostream>
#include <iterator>

template<typename T>
class Matrix{
public:
    int n;
    int m;
    std::vector<std::vector<T> > mtr;

    Matrix(int, int);
    Matrix();

    void print(); //вывод в std::cout
    void read(); //ввод и размера, и значений из std::cin
    void read_values(); //ввод только значений из std::cin
    void fill(T); //заполнение ячеек матрицы

    bool operator==(const Matrix&); //сравнение матриц
    Matrix<T>& operator=(const Matrix &); //присваивание

    void operator+=(const Matrix&); //сумма двух матрицы
    Matrix<T> operator+(const Matrix&);

    void operator-=(const Matrix&); //разность двух матрицы
    Matrix<T> operator-(const Matrix&);

    void operator/=(int const&); //деление матрицы на скаляр

    Matrix<T> operator*(const Matrix&); //произведение двух матриц

    void operator*=(int const&); //умножение матрицы на скаляр
    friend Matrix<T> operator*(const int& x, const Matrix& m) {
        Matrix<T> ans = m;
        for (int i = 0; i < ans.n; ++i) {
            for (int j = 0; j < ans.m; ++j) {
                ans.mtr[i][j] = x * m.mtr[i][j];
            }
        }
        return ans;
    }

    friend std::ostream& operator<<(std::ostream& o_stream, const Matrix& x) {  //вывод размеров и ячеек матрицы
        o_stream << "SIZE OF MATRIX: " << x.n << ' ' << x.m << '\n';
        o_stream << "MATRIX: " << '\n';
        for (int i = 0; i < x.n; ++i) {
            for (int j = 0; j < x.m; ++j) {
                o_stream << x.mtr[i][j] << ' ';
            }
            o_stream << '\n';
        }
        return o_stream;
    }

    friend std::istream& operator>>(std::istream& i_stream, Matrix& x) { //ввод размеров и ячеек матрицы
        i_stream >> x.n;
        i_stream >> x.m;
        x.mtr.resize(x.n, std::vector<T> (x.m));
        for (int i = 0; i < x.n; ++i) {
            for (int j = 0; j < x.m; ++j) {
                i_stream >> x.mtr[i][j];
            }
        }
        return i_stream;
    }


};

template <typename T>
Matrix<T>::Matrix(int a, int b) : n(a), m(b){
    mtr.resize(n, std::vector<T> (m));
}

template <typename T>
Matrix<T>::Matrix() : Matrix(0, 0){}

template <typename T>
void Matrix<T>::print() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cout << mtr[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

template <typename T>
void Matrix<T>::read() {
    std::cin >> n;
    std::cin >> m;
    mtr.resize(n, std::vector<T> (m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> mtr[i][j];
        }
    }
}

template <typename T>
void Matrix<T>::read_values() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> mtr[i][j];
        }
    }
}

template <typename T>
void Matrix<T>::fill(T val) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            mtr[i][j] = val;
        }
    }
}

template <typename T>
bool Matrix<T>::operator==(const Matrix& x) {
    if (n != x.n || m != x.m) {
        return false;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (mtr[i][j] != x.mtr[i][j])
                return false;
        }
    }
    return true;
}

template <typename T>
void Matrix<T>::operator+=(const Matrix & x) {
    if (n != x.n || m != x.m) {
        std::cerr << "different sizes of matrices!\n";
        exit(1);
    }
    else {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                mtr[i][j] += x.mtr[i][j];
            }
        }
    }
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix & x) {
    if (n != x.n || m != x.m) {
        std::cerr << "incorrect sizes of matrices!\n";
        exit(1);
    }
    else {
        Matrix<T> ans(n, m);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                ans.mtr[i][j] = mtr[i][j] + x.mtr[i][j];
            }
        }
        return ans;
    }
}

template <typename T>
void Matrix<T>::operator-=(const Matrix & x) {
    if (n != x.n || m != x.m) {
        std::cerr << "different sizes of matrices!\n";
        exit(1);
    }
    else {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                mtr[i][j] -= x.mtr[i][j];
            }
        }
    }
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix & x) {
    if (n != x.n || m != x.m) {
        std::cerr << "incorrect sizes of matrices!\n";
        exit(1);
    }
    else {
        Matrix<T> ans(n, m);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                ans.mtr[i][j] = mtr[i][j] - x.mtr[i][j];
            }
        }
        return ans;
    }
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix & x) {
    if (n != x.m || m != x.n) {
        std::cerr << "incorrect sizes of matrices!\n";
        exit(1);
    }
    else {
        Matrix<T> ans(n, m);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                ans[i][j] = mtr[i][j] * x.mtr[j][i];
            }
        }

        return ans;
    }
}


template <typename T>
void Matrix<T>::operator*=(int const& x) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            mtr[i][j] *= x;
        }
    }
}

template <typename T>
void Matrix<T>::operator/=(int const& x) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            mtr[i][j] /= x;
        }
    }
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix & x) {
    if (this == std::addressof(x)) { //проверка на самоприсваивание
        std::cerr << "self - assignment!\n";
        exit(1);
    }
    if (n != x.n || m != x.m) {
        std::cerr << "different sizes of matrices!\n";
        exit(1);
    }
    else {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                mtr[i][j] = x.mtr[i][j];
            }
        }
        return *this;
    }
}

#endif //MATRIX_MATRIX_H
