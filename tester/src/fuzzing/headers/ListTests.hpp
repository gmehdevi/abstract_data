
# include "Common.hpp"

template <class Container>
void	merge(Container &a)
{
	std::cout << "a.sort(); other.sort(); a.merge(other)" << std::endl;
	std::vector<typename Container::value_type> v = get_random_vector<typename Container::value_type>();
	Container other(v.begin(), v.end());
	a.sort();
	other.sort();
	a.merge(other);
	std::cout << "other:" << std::endl;
}

template <class Container>
void	splice(Container &a)
{
	FNAME
	typename Container::iterator pos = get_random_it(a);
	std::vector<typename Container::value_type> v = get_random_vector<typename Container::value_type>();
	Container other(v.begin(), v.end());
	std::cout << "a.splice(pos, other) with pos = ";
	print_it(a, pos);
	std::cout << std::endl;
	a.splice(pos, other);
}

template <class Container>
void	splice_range(Container &a)
{
	FNAME
	std::vector<typename Container::value_type> v = get_random_vector<typename Container::value_type>();
	Container other(v.begin(), v.end());
	typename Container::iterator pos = 	get_random_it(a);
	typename Container::iterator first =  	get_random_it(other);
	typename Container::iterator last = get_random_it(first, other.end());

	std::cout << "a.splice(pos, first, last) with pos = ";
	print_it(a, pos);
	std::cout << ", first = ";
	print_it(other, first);
	std::cout << ", last = ";
	print_it(other, last);
	std::cout << std::endl;
	a.splice(pos, other, first, last);
}


template <class Container>
void	splice_it(Container &a)
{
	FNAME
	std::vector<typename Container::value_type> v = get_random_vector<typename Container::value_type>();
	if (a.empty())
		return;
	if (v.empty())
		return;
	Container other(v.begin(), v.end());
	typename Container::iterator pos = get_random_it(a);
	typename Container::iterator first = other.begin();
	size_t n = rand() % (other.size());
	while (n--)
		++first;
	std::cout << "a.splice(pos, first) with pos = ";
	print_it(a, pos);
	std::cout << ", first = ";
	print_it(other, first);
	std::cout << std::endl;
	a.splice(pos, other, first);
}

template <class Container>
void	remove(Container &a)
{
	FNAME
	typename Container::value_type value((generate_value<typename Container::value_type>()));
	std::cout << "a.remove(value) with value = [" << value << "]" << std::endl;
	a.remove(value);
}

template <class Container>
void	remove_if(Container &a)
{
	FNAME
	typename Container::value_type value((generate_value<typename Container::value_type>()));
	std::cout << "a.remove_if(std::bind1st(std::less<std::string>(), value)) with value = [" << value << "]" << std::endl;
	a.remove_if(std::bind1st(std::less<typename Container::value_type>(), value));
}

template <class Container>
void	reverse(Container &a)
{
	FNAME
	std::cout << "a.reverse()" << std::endl;
	a.reverse();
}

template <class Container>
void	sort(Container &a)
{
	FNAME
	std::cout << "a.sort()" << std::endl;
	a.sort();
}

template <class Container>
void	unique(Container &a)
{
	FNAME
	std::cout << "a.unique()" << std::endl;
	a.unique();
}
