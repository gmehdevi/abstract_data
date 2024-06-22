#ifndef MATRIX_H
#define MATRIX_H
#include "ft_vec.hpp"
#include "./../utils.hpp"
#include <iostream>
#include <stdexcept>
#include "./../iterators.hpp"
#include <iomanip>
#include <sstream>
#include <cmath>
#include <complex>

namespace ft
{
   //--------------------------------------Iterator--------------------------------------------//
    template <typename T>
        class matrix_iterator : public iterator<bidirectional_iterator_tag, T>
        {
        public:
          typedef typename iterator<bidirectional_iterator_tag, T>::iterator_category             iterator_category;
          typedef typename iterator<bidirectional_iterator_tag, T>::value_type                    value_type;
          typedef typename iterator<bidirectional_iterator_tag, T>::difference_type               difference_type;
          typedef  T*                                                                             pointer;
          typedef  T&                                                                             reference;
          typedef  size_t                                                                         size_type;
     
        private :
          vector< vector<T> >          *mat;
          unsigned int                  m;
          unsigned int                  n;

        public :
          explicit matrix_iterator(vector< vector<T> >  &mat): mat(&mat.mat),m(0),n(0) {;}
          matrix_iterator(size_type _n, size_type m, vector< vector<T> >  &mat): mat(&mat),m(m),n(_n) {}
          matrix_iterator(const matrix_iterator &cpy):mat(0) {mat = cpy.mat; m = cpy.m; n = cpy.n;}
          matrix_iterator &operator=(const matrix_iterator &cpy) {mat = cpy.mat; m = cpy.m; n = cpy.n; return *this;}

          T &operator  *() {return  (*mat)[n][m];}
          vector<T> *operator ->()  {return &(*mat)[n];}

          matrix_iterator  operator ++() {
            if (m >= (*mat)[n].size() - 1 && n == (*mat).size() - 1) {
                m = (*mat)[n].size();
                n = (*mat).size();
               return (*this);
            }
            if (m < (*mat)[n].size() - 1)
                ++m;
            else if (n < (*mat).size() - 1) {
                m = 0;
                    ++n;
            }
            return (*this);
          }

          matrix_iterator operator --() {
            if (m == (*mat)[0].size() && n == (*mat).size()) {
                m = (*mat)[0].size() - 1; n = (*mat).size() - 1;
                return (*this);
            }
            if (m > 0)
                --m;
            else if (n > 0) {
                --n;
                m = (*mat)[n].size() - 1;
            }

            return (*this);
          }

          matrix_iterator operator ++(int) {
            matrix_iterator out(*this);
            ++(*this);
            return out;
          }

          matrix_iterator operator --(int) {
            matrix_iterator out(*this);
            --(*this);
            return out;
          }

          matrix_iterator operator +=(const int& d) {
            unsigned int i,j;
            i = d / (*mat)[0].size();
            j = d % (*mat)[0].size();
            n += i;
            m += j;
            if (n + i >= (*mat)[0].size() || n + i < 0 ) {
                n = (*mat).size();
                m = (*mat)[0].size();
                return *this;
            }
            return *this;
          }

          matrix_iterator operator -=(const int& d) {
            unsigned int i,j;
            i = d / (*mat)[0].size();
            j = d % (*mat)[0].size();
            n += i;
            m += j;
            if (n - i >= (*mat)[0].size()) {
                n = (*mat).size();
                m = (*mat)[0].size();
                return *this;
            }
            return *this;
          }

          matrix_iterator operator +(const int &d) {
              matrix_iterator out(*this);
              out += d;
              return out;
          }

          difference_type operator+(const matrix_iterator r) {
              return *this + r.n + (*mat)[0].size()  + r.m;
          }

          friend matrix_iterator operator +(const int &d, matrix_iterator &r) {
              matrix_iterator out(r);
              out += d;
              return out;
          }
          matrix_iterator operator -(const int &d) {
              matrix_iterator out(*this);
              out -= d;
              return out;
          }

          friend matrix_iterator operator -(const int &d, matrix_iterator &r) {
              matrix_iterator out(r);
              out -= d;
              return out;
          }

          difference_type operator-(const matrix_iterator &r) {
              return *this - r.n + (*mat)[0].size()  + r.m;
          }

        friend difference_type operator-(const matrix_iterator &a, const matrix_iterator &b) {
                return a.n * (*a.mat)[0].size() + a.m - b.n * (*b.mat)[0].size() + b.m;
          }

        friend bool operator==(const matrix_iterator &a, const matrix_iterator &b) {return *(a.mat) == *(b.mat) &&  a.n * (*a.mat)[0].size() + a.m == b.n * (*b.mat)[0].size() + b.m;}
        friend bool operator!=(const matrix_iterator &a, const matrix_iterator &b) {return !(a == b);}
        };


   //--------------------------------------matrix--------------------------------------------//
	template <typename T>
    class matrix {

	public:
        typedef vector<vector<T> > Container;
		typedef T value_type;
		typedef typename Container::size_type size_type;
		typedef typename Container::reference reference;
		typedef typename Container::const_reference const_reference;
        typedef typename Container::pointer    pointer;
        typedef matrix_iterator<T>        iterator;
        typedef matrix_iterator<const T>  const_iterator;
        typedef ft::reverse_iterator<iterator>              reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>              const_reverse_iterator;

    protected:
		Container mat;
    
        size_type m;
        size_type n;
    public:



    matrix(size_type n, size_type m, const value_type &val = value_type()) : mat(n, vector<T>(m, val)), m(m), n(n) {if (n == 0 && m > 0)this->n = 1;}
    matrix(size_type n) : mat(n, vector<T>(n, value_type())) , m(n), n(n) {
        for (size_type i = 0; i < n; i++)
            mat[i][i] = 1;
    }
    matrix(vector<vector<T> > &v) : mat(v), m(v[0].size()), n(v.size()) {
        for (typename vector<vector<T> >::iterator it = v.begin(); it != v.end(); it++)
            if (it->size() != m)
                throw std::invalid_argument("matrix variable row size");
    }


    // matrix(std::initializer_list<std::initializer_list<T> > l) : mat(), m(l.begin()->size()), n(l.size()) {
    //     for (auto it = l.begin(); it != l.end(); it++)
    //         if (it->size() != m)
    //             throw std::invalid_argument("matrix variable row size");
    //     for (auto it = l.begin(); it != l.end(); it++)
    //         mat.push_back(vector<T>(it->begin(), it->end()));
    // }
    ~matrix() {}
    matrix(const matrix &other) : mat(other.mat), m(other.m), n(other.n) {}
    matrix(const ft::vector<T> &v){
        matrix tmp = matrix(1, v.size());
        for (size_type i = 0; i < v.size(); i++)
            tmp[0][i] = v[i];
        *this = tmp;
    }   
    
    matrix &operator%=(const value_type &val) {
        if (val == 0)
            throw std::invalid_argument("matrix modulus by zero");
        for (size_type i = 0; i < n; i++)
            for (size_type j = 0; j < m; j++)
                mat[i][j] %= val;
        return *this;
    }
    matrix &operator/=(const value_type &val) {
        if (val == (T)0)
            throw std::invalid_argument("matrix division by zero");
        for (size_type i = 0; i < n; i++)
            for (size_type j = 0; j < m; j++)
                mat[i][j] /= val;
        return *this;
    }

    matrix &operator*=(const value_type &val) {
        for (size_type i = 0; i < n; i++)
            for (size_type j = 0; j < m; j++)
                mat[i][j] *= val;
        return *this;
    }


    matrix& operator*=(const matrix& other) {
        if (other.n != m) {
            throw std::invalid_argument("Matrix multiplication error: Invalid dimensions");
        }

        matrix result(n, other.m);  // Result matrix dimensions: n x other.m

        for (size_type i = 0; i < result.n; i++) {
            for (size_type j = 0; j < result.m; j++) {
                result.mat[i][j] = 0;
                for (size_type k = 0; k < m; k++) {
                    result.mat[i][j] += mat[i][k] * other.mat[k][j];
                }
            }
        }
        
        *this = result;
        return *this;
    }


    matrix &operator-=(const matrix &other) {
        if ((n != other.n) || (m != other.m))
            throw std::invalid_argument("matrix subtraction of " + ft::to_string(n) + "x" + ft::to_string(m) + " and " + ft::to_string(other.n) + "x" + ft::to_string(other.m) + " matrix");
        for (size_type i = 0; i < n; i++)
            for (size_type j = 0; j < m; j++)
                mat[i][j] -= other.mat[i][j];
        return *this;
    }

    matrix &operator+=(const matrix &other) {
        if ((n != other.n) || (m != other.m))
            throw std::invalid_argument("matrix addition of " + ft::to_string(n) + "x" + ft::to_string(m) + " and " + ft::to_string(other.n) + "x" + ft::to_string(other.m) + " matrix");
        for (size_type i = 0; i < n; i++)
            for (size_type j = 0; j < m; j++)
                mat[i][j] += other.mat[i][j];
        return *this;
    }

    ft::vector<T> operator*(const ft::vector<T> &v) {
        if (m != v.size() && (m != 4 && v.size() != 3))
            throw std::invalid_argument("matrix multiplication of " + ft::to_string(n) + "x" + ft::to_string(m) + " and " + ft::to_string(v.size()) + "x1 vector");  
        ft::vector<T> res(n);
        for (size_type i = 0; i < n; i++)
            for (size_type j = 0; j < m; j++)
                res[i] += mat[i][j] * v[j];
        return res;
    }

    matrix &operator=(const matrix &other) {
        mat = other.mat;
        m = other.m;
        n = other.n;
        return *this;
    }

    matrix &operator=(const vector<T> &other) {
        *this = matrix(other);
        return *this;
    }

    reference at (size_type  i, size_type j) {
        if ((n <= i) || (m <= j))
            throw std::out_of_range("matrix");
        return mat[i][j];
    }

    reference at (size_type  i, size_type j) const {
        if ((n <= i) || (m <= j))
            throw std::out_of_range("matrix");
        return mat[i][j];
    }

    reference operator[] (size_type  i) {
        if (i >= n)
            throw std::out_of_range("matrix");
        return mat[i];
    }

    const_reference operator[] (size_type i) const  {
        if (i >= n)
            throw std::out_of_range("matrix");
        return mat[i];
    }

    pointer data() {return mat.data();}
    const pointer data() const {return mat.data();}

    size_type rows() const {return n;}
    size_type cols() const {return m;}
    iterator begin() {return iterator(0, 0, mat);}
    iterator end()   {return iterator(n, m, mat);}
    reverse_iterator rbegin() {return   end();}
    reverse_iterator rend() {return begin();}
    const_iterator begin() const {return const_iterator(0, 0, mat);}
    const_iterator end() const   {return const_iterator(n, m, mat);}
    const_reverse_iterator rbegin() const {return   end();}
    const_reverse_iterator rend() const {return begin();}

    T &operator()(size_type i, size_type j) {
        if ((n <= i) || (m <= j))
            throw std::out_of_range("matrix");
        return mat[i][j];
    }

    T max() const {
        T max = mat[0][0];
        for (size_type i = 0; i < n; i++)
            for (size_type j = 0; j < m; j++)
                if (mat[i][j] > max)
                    max = mat[i][j];
        return max;
    }

    T trace() {
        if (n != m)
            throw std::invalid_argument("matrix must be square");
        T sum = 0;
        for (size_type i = 0; i < n; i++)
            sum += mat[i][i];
        return sum;
    }

    matrix operator+(const matrix &r) {
        matrix tmp(*this);
        tmp += r;
        return tmp;
    }

    matrix transposed() {
        matrix tmp(m, n);
        for (size_type i = 0; i < n; i++)
            for (size_type j = 0; j < m; j++)
                tmp.mat[j][i] = mat[i][j];
        return tmp;
    }

    matrix c_transposed() {
        matrix tmp(m, n);
        for (size_type i = 0; i < n; i++)
            for (size_type j = 0; j < m; j++)
                tmp.mat[j][i] = std::conj(mat[i][j]);
        return tmp;
    }

    size_type i_pivot(const vector<T> &v) {
        size_type i = 0;
        for (i = 0; i < v.size(); i++)
            if (v[i] != (T)0)
                break;
        return i;
    }
    
    matrix row_echelon() {
        matrix tmp = *this;
        for (size_type i = 0; i < tmp.n; i++) {
            size_type pivot = i_pivot(tmp.mat[i]);
            if (pivot == tmp.m)
                continue;
            if (pivot != i)
                std::swap(tmp.mat[i], tmp.mat[pivot]);
            for (size_type j = i + 1; j < tmp.n; j++) {
                T coef = (std::fabs(tmp.mat[i][i]) != static_cast<T>(0)) ? tmp.mat[j][i] / tmp.mat[i][i] : static_cast<T>(1);
                for (size_type k = i; k < tmp.m; k++)
                    tmp.mat[j][k] -= coef * tmp.mat[i][k];
            }
        }
        return tmp;
    }


    matrix r_row_echelon() {
        matrix tmp = *this;
        int lead = 0;
        while (lead < n) {
            for (int r = 0; r < n; r++) {
                T div = (tmp[lead][lead] != static_cast<T>(0)) ? tmp[lead][lead] : static_cast<T>(1);
                T mult = (tmp[lead][lead] != static_cast<T>(0)) ? tmp[r][lead] / tmp[lead][lead] : static_cast<T>(0);
                for (int c = 0; c < m; c++) {
                    if (r == lead)
                        tmp[r][c] /= div;
                    else
                        tmp[r][c] -= tmp[lead][c] * mult;
                }
            }
            lead++;
        }
        for (int i = 0; i < n; i++)
            ft::reverse(tmp[i].begin(), tmp[i].end());
        ft::reverse(tmp.mat.begin(), tmp.mat.end());
        return tmp;
    }


    T det() {
        if (n != m)
            throw std::invalid_argument("matrix must be square");
        matrix tmp = row_echelon();
        T d = 1;
        for (size_type i = 0; i < tmp.n; i++)
            d *= tmp.mat[i][i];
        return d;
    }

    matrix adj() {
        if (n != m)
            throw std::invalid_argument("matrix must be square");
        matrix tmp(n, n);
        for (size_type i = 0; i < n; i++) {
            for (size_type j = 0; j < n; j++) {
                matrix minor(n - 1, n - 1);
                for (size_type k = 0; k < n; k++) {
                    if (k != i) {
                        for (size_type l = 0; l < n; l++) {
                            if (l != j) {
                                minor.mat[k > i ? k - 1 : k][l > j ? l - 1 : l] = mat[k][l];
                            }
                        }
                    }
                }
                tmp.mat[i][j] = minor.det() * static_cast<double>((i + j) % 2 ? -1 : 1);
            }
        }
        return tmp;
    }

    matrix inv() {
        if (n != m)
            throw std::invalid_argument("matrix must be square");
        matrix tmp = adj();
        tmp = tmp.transposed();
        T d = det();
        if (d == T())
            throw std::invalid_argument("matrix is not invertible");
        return tmp / d;
    }


    size_type rank() {
        matrix tmp = r_row_echelon();
        size_type r = 0;
        for (size_type i = 0; i < tmp.n; i++)
            if (tmp.mat[i] != vector<T>(tmp.m, 0))
                r++;
        return r;
    }



    friend matrix operator +(const matrix &lhs, const matrix &rhs) {
        matrix tmp(rhs);
        tmp += lhs;
        return tmp;
    }


    matrix &operator-(const matrix &r) {
        *this -= r;
        return *this;
    }

    friend matrix operator -(const matrix &lhs, const matrix &rhs) {
        matrix tmp = rhs;
        tmp -= lhs;
        return tmp;
    }


    matrix &operator*(const matrix &r) {
        *this *= r;
        return *this;
    }

    friend matrix operator *(const matrix &lhs, const matrix &rhs) {
        matrix tmp = lhs;
        tmp *= rhs;
        return tmp;
    }

    matrix &operator*(const value_type &val) {
        *this *= val;
        return *this;
    }

    friend matrix operator *(const matrix &lhs, const value_type &val) {
        matrix tmp = lhs * val;
        return tmp;
    }


    matrix &operator/(const value_type &val) {
        *this /= val;
        return *this;
    }

    friend matrix operator /(const matrix &lhs, const value_type &val) {
        matrix tmp = lhs / val;
        return tmp;
    }


    matrix &operator%(const value_type &val) {
        *this %= val;
        return *this;
    }

    friend matrix operator %(const matrix &lhs, const value_type &val) {
        matrix tmp = lhs % val;
        return tmp;
    }

    Container to_vecs() {
        return mat;
    }

    vector<T> to_vec() {
        vector<T> tmp(mat.begin(), mat.end());
        return tmp;
    }

    // friend std::ostream &operator<<(std::ostream &os, matrix mat) {
    //     size_type width = 0;
    //     for (auto it = mat.begin(); it != mat.end(); it++)
    //         width = std::max(sstr(*it).length(), width);
    //     for (size_type i = 0; i < mat.n; i++) {
    //         os << "[ " << std::setw(width);
    //         for (size_type j = 0; j < mat.m - 1; j++) {
    //             os  << std::setw(width) << mat[i][j]  << " ,";
    //         }
    //         if (mat.m > 0) os << std::setw(width) << mat[i][mat.m - 1] ;
    //          os << "]";
    //         if (i < mat.n - 1) os << std::endl;
    //     }
    //     return os;
    // } 

        //Non-member functions
        friend matrix linear_interpolation(const matrix &a, const matrix &b, T t) {
            return a + (b - a) * t;
        }

        friend bool operator==(const matrix& lhs, const matrix& rhs) {
                return (lhs.mat == rhs.mat);
        }

        friend bool operator!=( const matrix& lhs,
                        const matrix& rhs ) {
                            return !(lhs.mat == rhs.mat);
        }

        // matrix<float> &rot_z(float theta) {
        //     *this *=  matrix<float> ({
        //         {cosf(theta), sinf(theta), 0, 0},
        //         {-sinf(theta), cosf(theta), 0, 0},
        //         {        0,          0, 1, 0},
        //         {        0,          0, 0, 1}
        //          });
        //     return *this;
        // }

        // matrix<float> &rot_y(float theta) {
        //     *this *=  (matrix<float>) {
        //         {cosf(theta), 0, -sinf(theta), 0},
        //         {        0, 1,           0, 0},
        //         {sinf(theta), 0,  cosf(theta), 0},
        //         {        0, 0,           0, 1}
        //     };
        //     return *this;
        // }

        // matrix<float> &rot_x(float theta) {
        //     *this *=  (matrix<float>) {
        //         {1, 0, 0, 0},
        //         {0, cosf(theta), sinf(theta), 0},
        //         {0, -sinf(theta), cosf(theta), 0},
        //         {0, 0, 0, 1}
        //     };
        //     return *this;
        // }

    };

    // matrix<float> rotate(float theta, vector<float> axis) {
    //     theta = -theta;
    //     axis = axis / norm(axis);
    //     return matrix<float>({
    //             {cosf(theta) + axis[0] * axis[0] * (1 - cosf(theta)), axis[0] * axis[1] * (1 - cosf(theta)) + axis[2] * sinf(theta), axis[0] * axis[2] * (1 - cosf(theta)) - axis[1] * sinf(theta), 0},
    //             {axis[1] * axis[0] * (1 - cosf(theta)) - axis[2] * sinf(theta), cosf(theta) + axis[1] * axis[1] * (1 - cosf(theta)), axis[1] * axis[2] * (1 - cosf(theta)) + axis[0] * sinf(theta), 0},
    //             {axis[2] * axis[0] * (1 - cosf(theta)) + axis[1] * sinf(theta), axis[2] * axis[1] * (1 - cosf(theta)) - axis[0] * sinf(theta), cosf(theta) + axis[2] * axis[2] * (1 - cosf(theta)), 0},
    //             {0, 0, 0, 1}
    //         });
    // }

    // matrix<float> perspective(float fov, float ratio, float near, float far) {
    //     float f = 1 / tanf(fov / 2);
    //     return matrix<float>({
    //         {f / ratio, 0, 0, 0},
    //         {0, f, 0, 0},
    //         {0, 0, (far + near) / (near - far), -1},
    //         {0, 0, 2 * far * near / (near - far), 0}
    //     });
    // }

    
    // matrix<float> translation(vector<float> v) {
    //     return matrix<float>({
    //     {1, 0, 0, 0},
	// 	{0, 1, 0, 0},
	// 	{0, 0, 1, 0},
	// 	{v[0], v[1], v[2], 1}
    //     });
    // }


    // matrix<float> scale(vector<float> v) {
    //     return matrix<float>({
    //     {v[0], 0, 0, 0},
	// 	{0, v[1], 0, 0},
	// 	{0, 0, v[2], 0},
	// 	{0, 0, 0, 1}
    //     });
    // }

    // matrix<float> scale(float s) {
    //     return matrix<float>({
    //     {s, 0, 0, 0},
	// 	{0, s, 0, 0},
	// 	{0, 0, s, 0},
	// 	{0, 0, 0, 1}
    //     });
    // }

    // matrix<float> camera(vector<float> const &eye, vector<float> const &center, vector<float> const &up) {
    //     vector<float> f = normalize(center - eye);
    //     vector<float> u = normalize(up);
    //     vector<float> s = normalize(cross(f, u));
    //     u = cross(s, f);

    //    return matrix<float> ({
    //         {s[0], u[0], -f[0], 0},
    //         {s[1], u[1], -f[1], 0},
    //         {s[2], u[2], -f[2], 0},
    //         {-dot(s, eye), -dot(u, eye), dot(f, eye), 1.0f}
    //     });
    // }

    // matrix<float> rotate(matrix<float> m, double theta, vector<float> axis) {
    //     theta = -theta;
    //     axis = axis / norm(axis);
    //     return matrix<float>({
    //             {cosf(theta) + axis[0] * axis[0] * (1 - cosf(theta)), axis[0] * axis[1] * (1 - cosf(theta)) + axis[2] * sinf(theta), axis[0] * axis[2] * (1 - cosf(theta)) - axis[1] * sinf(theta), 0},
    //             {axis[1] * axis[0] * (1 - cosf(theta)) - axis[2] * sinf(theta), cosf(theta) + axis[1] * axis[1] * (1 - cosf(theta)), axis[1] * axis[2] * (1 - cosf(theta)) + axis[0] * sinf(theta), 0},
    //             {axis[2] * axis[0] * (1 - cosf(theta)) + axis[1] * sinf(theta), axis[2] * axis[1] * (1 - cosf(theta)) - axis[0] * sinf(theta), cosf(theta) + axis[2] * axis[2] * (1 - cosf(theta)), 0},
    //             {0, 0, 0, 1}
    //         }) * m;
    // }
}
#endif