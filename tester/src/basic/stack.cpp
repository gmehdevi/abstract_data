#include "stack.hpp"
#include <iostream>
#include <stack>

#ifdef TEST_FT
	#define ns ft
#else
	#define ns std
#endif


typedef ns::stack<int> container_type;

#include <iostream>
#include "stack.hpp"

template <typename T_STACK>
void	printSize(T_STACK &stck, bool print_content = 1)
{
	std::cout << "size: " << stck.size() << std::endl;
	if (print_content)
	{
		std::cout << std::endl << "Content was:" << std::endl;
		while (stck.size() != 0) {
			std::cout << "- " << stck.top() << std::endl;
			stck.pop();
		}
	}
	std::cout << "###############################################" << std::endl;
}


template <class T_STACK>
void	cmp(const T_STACK &lhs, const T_STACK &rhs)
{
	static int i = 0;

	std::cout << "############### [" << i++ << "] ###############"  << std::endl;
	std::cout << "eq: " << (lhs == rhs) << " | ne: " << (lhs != rhs) << std::endl;
	std::cout << "lt: " << (lhs <  rhs) << " | le: " << (lhs <= rhs) << std::endl;
	std::cout << "gt: " << (lhs >  rhs) << " | ge: " << (lhs >= rhs) << std::endl;
}

int		main(void)
{


	{
	container_type st;
	
	for (int i = 0; i < 10; i++)
		st.push(i);

	container_type st2(st);
	container_type st3;
	st3 = st2;

	std::cout << st.size() << std::endl;
	std::cout << st2.size() << std::endl;
	std::cout << st3.size() << std::endl;


	while (!st.empty()) {
		std::cout << st.top() << std::endl;
		st.pop();
	}

	std::cout << "st.empty() : " << st.empty() << std::endl;
	std::cout << "st.size() : " << st.size() << std::endl;
	}
	{	
	container_type	ctnr;

	ctnr.push(21);
	ctnr.push(42);
	ctnr.push(1337);
	ctnr.push(19);
	ctnr.push(0);
	ctnr.push(183792);

	container_type		stck(ctnr);

	std::cout << "empty: " << stck.empty() << std::endl;
	std::cout << "size: " << stck.size() << std::endl;

	stck.push(1);
	stck.push(2);
	stck.push(3);
	stck.push(4);
	stck.push(5);
	stck.push(6);

	std::cout << "Added some elements" << std::endl;

	std::cout << "empty: " << stck.empty() << std::endl;
	printSize(stck);
}
{
	container_type	ctnr;

	ctnr.push(21);
	ctnr.push(42);
	ctnr.push(1337);
	ctnr.push(19);
	ctnr.push(0);
	ctnr.push(183792);

	container_type		stck(ctnr);

	std::cout << "empty: " << stck.empty() << std::endl;
	std::cout << "size: " << stck.size() << std::endl;

	stck.push(41);
	stck.push(29);
	stck.push(10);
	stck.push(42);
	std::cout << "Added some elements" << std::endl;

	std::cout << "empty: " << stck.empty() << std::endl;
	printSize(stck);
}
{

	container_type	ctnr;

	ctnr.push(21);
	ctnr.push(42);
	ctnr.push(1337);
	ctnr.push(19);
	ctnr.push(0);
	ctnr.push(183792);

	container_type stck(ctnr);

	std::cout << "empty: " << stck.empty() << std::endl;
	std::cout << "size: " << stck.size() << std::endl;

	stck.push(1);
	stck.push(2);
	stck.push(3);
	stck.push(4);
	stck.push(5);
	stck.push(6);

	std::cout << "Added some elements" << std::endl;

	std::cout << "empty: " << stck.empty() << std::endl;
	printSize(stck);
}

{
	container_type	ctnr;

	ctnr.push(21);
	ctnr.push(42);
	ctnr.push(1337);
	ctnr.push(19);
	ctnr.push(0);
	ctnr.push(183792);

	container_type	stck(ctnr);
	container_type	stck2(ctnr);

	cmp(stck, stck);  // 0
	cmp(stck, stck2); // 1

	stck2.push(60);
	stck2.push(61);
	stck2.push(62);

	cmp(stck, stck2); // 2
	cmp(stck2, stck); // 3

	stck.push(42);

	cmp(stck, stck2); // 4
	cmp(stck2, stck); // 5

	stck.push(100);

	cmp(stck, stck2); // 6
	cmp(stck2, stck); // 7
}

{
	container_type	ctnr;

	ctnr.push(21);
	ctnr.push(42);
	ctnr.push(1337);
	ctnr.push(19);
	ctnr.push(0);
	ctnr.push(183792);

	container_type	stck(ctnr);
	container_type	stck2(ctnr);

	cmp(stck, stck);  // 0
	cmp(stck, stck2); // 1

	stck2.push(60);
	stck2.push(61);
	stck2.push(62);

	cmp(stck, stck2); // 2
	cmp(stck2, stck); // 3

	stck.push(42);

	cmp(stck, stck2); // 4
	cmp(stck2, stck); // 5

	stck.push(100);

	cmp(stck, stck2); // 6
	cmp(stck2, stck); // 7
}

	return (0);
}
