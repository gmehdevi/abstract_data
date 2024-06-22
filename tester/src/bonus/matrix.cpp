#include <iostream>
#include <cassert>
#include "matrix.hpp"

void test_matrix_creation() {
    ft::matrix<int> mat1(2, 3, 5);
    assert(mat1.rows() == 2);
    assert(mat1.cols() == 3);
    assert(mat1[0][0] == 5);
    assert(mat1[1][2] == 5);

    ft::matrix<int> mat2(3);
    assert(mat2.rows() == 3);
    assert(mat2.cols() == 3);
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            if (i == j) {
                assert(mat2[i][j] == 1);
            } else {
                assert(mat2[i][j] == 0);
            }
        }
    }

    ft::vector<ft::vector<int> > init_list;
    ft::vector<int> row1;
    row1.push_back(1);
    row1.push_back(2);
    row1.push_back(3);
    init_list.push_back(row1);

    ft::vector<int> row2;
    row2.push_back(4);
    row2.push_back(5);
    row2.push_back(6);
    init_list.push_back(row2);

    ft::vector<int> row3;
    row3.push_back(7);
    row3.push_back(8);
    row3.push_back(9);
    init_list.push_back(row3);

    ft::matrix<int> mat3(init_list);
    assert(mat3.rows() == 3);
    assert(mat3.cols() == 3);
    assert(mat3[0][0] == 1);
    assert(mat3[2][2] == 9);
}

void test_matrix_arithmetic() {
    ft::matrix<int> mat1(2, 2, 1);
    ft::matrix<int> mat2(2, 2, 2);

    ft::matrix<int> result_add = mat1 + mat2;
    assert(result_add[0][0] == 3);
    assert(result_add[1][1] == 3);

    ft::matrix<int> result_sub = mat1 - mat2;
    assert(result_sub[0][0] == -1);
    assert(result_sub[1][1] == -1);
}

void test_matrix_scalar_operations() {
    ft::matrix<int> mat1(2, 2, 2);

    ft::matrix<int> result_mul = mat1 * 2;
    assert(result_mul[0][0] == 4);
    assert(result_mul[1][1] == 4);
}

void test_matrix_determinant() {
    ft::matrix<int> mat1(2, 2);
    mat1[0][0] = 1;
    mat1[0][1] = 2;
    mat1[1][0] = 3;
    mat1[1][1] = 4;
    assert(mat1.det() == -2);
}

void test_matrix_inverse() {
    ft::matrix<float> mat1(2, 2);
    mat1[0][0] = 4;
    mat1[0][1] = 7;
    mat1[1][0] = 2;
    mat1[1][1] = 6;
    ft::matrix<float> inv1 = mat1.inv();
    assert(std::fabs(inv1[0][0] - 0.6) < 1e-5);
    assert(std::fabs(inv1[0][1] - -0.7) < 1e-5);
    assert(std::fabs(inv1[1][0] - -0.2) < 1e-5);
    assert(std::fabs(inv1[1][1] - 0.4) < 1e-5);
}

void test_matrix_transpose() {
    ft::matrix<int> mat1(2, 3);
    mat1[0][0] = 1;
    mat1[0][1] = 2;
    mat1[0][2] = 3;
    mat1[1][0] = 4;
    mat1[1][1] = 5;
    mat1[1][2] = 6;
    ft::matrix<int> transposed = mat1.transposed();
    assert(transposed.rows() == 3);
    assert(transposed.cols() == 2);
    assert(transposed[0][1] == 4);
    assert(transposed[2][1] == 6);
}

void test_matrix_trace() {
    ft::matrix<int> mat1(2, 2);
    mat1[0][0] = 1;
    mat1[0][1] = 2;
    mat1[1][0] = 3;
    mat1[1][1] = 4;
    assert(mat1.trace() == 5);

    ft::matrix<int> mat2(3, 3);
    mat2[0][0] = 6;
    mat2[0][1] = 1;
    mat2[0][2] = 1;
    mat2[1][0] = 4;
    mat2[1][1] = -2;
    mat2[1][2] = 5;
    mat2[2][0] = 2;
    mat2[2][1] = 8;
    mat2[2][2] = 7;
    assert(mat2.trace() == 11);
}

void test_matrix_iterator() {
    ft::matrix<int> mat1(2, 2);
    mat1[0][0] = 1;
    mat1[0][1] = 2;
    mat1[1][0] = 3;
    mat1[1][1] = 4;
    ft::matrix<int>::iterator it = mat1.begin();
    assert(*it == 1);
    ++it;
    assert(*it == 2);
    ++it;
    assert(*it == 3);
    ++it;
    assert(*it == 4);
    ++it;
    assert(it == mat1.end());

    for (ft::matrix<int>::iterator it = mat1.begin(); it != mat1.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;


}

int main() {
    std::cout << "Running matrix tests..." << std::endl;

    test_matrix_creation();
    std::cout << "Matrix creation test passed." << std::endl;

    test_matrix_arithmetic();
    std::cout << "Matrix arithmetic test passed." << std::endl;

    test_matrix_scalar_operations();
    std::cout << "Matrix scalar operations test passed." << std::endl;

    test_matrix_determinant();
    std::cout << "Matrix determinant test passed." << std::endl;

    test_matrix_inverse();
    std::cout << "Matrix inverse test passed." << std::endl;

    test_matrix_transpose();
    std::cout << "Matrix transpose test passed." << std::endl;

    test_matrix_trace();
    std::cout << "Matrix trace test passed." << std::endl;

    test_matrix_iterator();
    std::cout << "Matrix iterator test passed." << std::endl;

    std::cout << "All tests passed!" << std::endl;

    return 0;
}
