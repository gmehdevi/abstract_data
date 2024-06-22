#include "vector.hpp"
#include <memory>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cstddef>
#include <limits>
#include <climits>
#ifdef TEST_FT
    #define ns ft
#else
    #define ns std
#endif

template<class T>
std::string to_string(T a) {
    std::stringstream f;
    f << a;
    return f.str();
}

template <typename T>
std::ostream &operator<<(std::ostream &os, ns::vector<T> &v) {
    os << "|";
    for (size_t i = 0; i < v.size(); i++)
        os << v[i] << "|";
    return os;
}

int main(int ac, char **av) {
    (void )ac;
    std::cout << "here" <<std::endl;
    srand(atoi(av[1]));
    ns::vector<int> init;
    for (size_t i = 0; i < 1000 ; i++)
        init.push_back(rand()%INT_MAX);
    {
        ns::vector<int> v_def;
        ns::vector<int> v_it(init.begin(), init.end());
        ns::vector<int> v_count(init.size(),*init.begin());
    	std::cout << "here" <<std::endl;
        ns::vector<int> v_other(v_it);
    	std::cout << "here" <<std::endl;
        v_def.insert(v_def.begin(), 10, 1);
        v_def.insert(v_def.end(), 10, 5);
        std::cout << "here" << v_def << std::endl;
        v_def.insert(v_def.end() - v_def.size()/2, 10, 7);
        std::cout << v_def << std::endl;
    }


    std::cout << "here" <<std::endl;

	{
		ns::vector<int> v(10);
		ns::vector<int> v1(v);
		ns::vector<int> v2(v.begin(), v.end());
		ns::vector<int> v3(7, 7);

		std::cout <<   (v);
		std::cout <<   (v1);
		std::cout <<   (v2);
		v2 = ns::vector<int>(12);
		std::cout <<   (v2);
		std::cout <<   (v3);
	}
	{
		ns::vector<std::string> v(10, "oh");
		ns::vector<std::string> v1(v);
		ns::vector<std::string> v2(v.begin(), v.end());
		ns::vector<std::string> v3(7, "eh");

		std::cout <<   (v);
		std::cout <<   (v1);
		std::cout <<   (v2);
		v2 = ns::vector<std::string>(12, "ah");
		std::cout <<   (v2);
		std::cout <<   (v3);
	}

	{
		ns::vector<int> v(10);
		v.resize(14, 7);
		std::cout <<   (v);
		v.resize(7, -1);
		std::cout <<   (v);
		v.reserve(100);
		std::cout << v.capacity() << std::endl;
		std::cout <<   (v);
		v.reserve(0);
		std::cout <<   (v) << std::endl;
	}
	{

		ns::vector<std::string> v;
		ns::vector<std::string> v1;

		for (int i = 0; i < 10; i++)
			v1.push_back(to_string(i));

		v.assign(5, "pouet");
		std::cout <<   (v) << std::endl;
		v.assign(v1.begin(), v1.end());
		std::cout <<   (v) << std::endl;
		while (!v1.empty()) v1.pop_back();
		std::cout <<   (v1) << std::endl;
	}
	{
		ns::vector<int> v;
		ns::vector<int> v1;
		for (int i = 0; i < 100; i++)
			v.push_back(i);
		std::cout <<   (v) << std::endl;
		v.insert(v.begin() + 12, 42);
		v.insert(v.end() - 12, 24);
		v.insert(v.begin() + 34, 20, 7);
		std::cout << v.back() << " " << v.front() << std::endl;
		std::cout <<   (v) << std::endl;
		v1 = ns::vector<int>(12, -1);
		v1.insert(v1.begin() + 3, v.begin(), v.end());
		std::cout <<   (v)<< std::endl;
		v1.erase(v1.begin());
		std::cout <<   (v1)<< std::endl;
		v1.erase(v1.begin()+1, v1.end());
		std::cout <<   (v1)<< std::endl;
		swap(v1, v);
		std::cout <<   (v)<< std::endl;
		std::cout <<   (v1)<< std::endl;
		v.clear();
		v1.clear();
		std::cout <<   (v);
		std::cout <<   (v1);
	}
	{
		ns::vector<int> v;
		for (int i = 0; i < 12; i++) v.push_back(i);
		try {
			v.at(12) = 42;
		} catch (ns::out_of_range& e) {
			std::cout << "out of range" << std::endl;
		}
		try {
			v.at(-1) = 42;
		} catch (ns::out_of_range& e) {
			std::cout << "out of range" << std::endl;
		}
		try {
			v.at(0) = 42;
		} catch (ns::out_of_range& e) {
			std::cout << "out of range" << std::endl;
		}
	}
	{
		ns::vector<int> v;
		ns::vector<int> v1;
		for (int i = 0; i < 32; i++) v.push_back(i);
		for (int i = 0; i < 32; i++) v.push_back(32 - i);
		std::cout << (v == v1) << std::endl;
		std::cout << (v != v1) << std::endl;
		std::cout << (v <= v1) << std::endl;
		std::cout << (v >= v1) << std::endl;
		std::cout << (v < v1) << std::endl;
		std::cout << (v > v1) << std::endl;
	}
    std::cout << "here" <<std::endl;

	{
    ns::vector<int> v(100);
	for (unsigned int i = 0; i < v.size(); i++) v[i] = i;

	ns::vector<int>::iterator it = v.begin();
	ns::vector<int>::const_iterator cit = v.begin();
	ns::vector<int>::const_iterator cit1(it);
	ns::vector<int>::reverse_iterator rit = v.rbegin();
	ns::vector<int>::const_reverse_iterator crit = v.rbegin() + 8;


	it += 5;
	--it;
	it--;
	while (cit < 2 + it) {
		std::cout << *(cit++) << " ";
	}
	std::cout << std::endl;
	std::cout << (it - cit1) << std::endl;
	while (rit != crit) {
		std::cout << *rit << " ";
		++rit;
	}

	std::cout << (it < it + 3) << std::endl;
	std::cout << (it <= it) << std::endl;
	std::cout << (it > it - 3) << std::endl;
	std::cout << (it >= it + 1) << std::endl;
	std::cout << (it == cit) << std::endl;
	std::cout << (it != it + 3) << std::endl;

	for (;it != v.end(); ++it) {
		std::cout << *it << " ";
	}
	for (;cit != v.end(); ++cit) {
		std::cout << *cit << " ";
	}
	for (;crit != v.rend(); ++crit) {
		std::cout << *crit << " ";
	}
	for (;rit != v.rend(); ++rit) {
		std::cout << *rit << " ";
	}

    ns::vector<int>::const_iterator t = v.begin();
    t++;
	}

    return 0;
}