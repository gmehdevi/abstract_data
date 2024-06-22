#include <iostream>
#include <map>
#include "map.hpp"
#include <cstddef>
#include <utility>
#ifdef TEST_FT
# define NAMESPACE ft
#else
# define NAMESPACE std
#endif


using namespace NAMESPACE;

template <class T1, class T2>
std::ostream &operator<<( std::ostream &o, pair<T1,T2> p) {
  o <<"(" << p.first << " | " << p.second << ")";
  return o;
}

template <class Key, class T>
void	print(map<Key, T>& lst)
{
	for (typename map<Key, T>::iterator it = lst.begin(); it != lst.end(); it++)
		std::cout << *it << ' ';
	std::cout << '\n';
}

int main()
{
{
	pair<int, std::string>			my_pair(8, "salut");
	map<int, std::string>			test;
	map<int, std::string>::iterator	it;

	test.insert(my_pair);
  std::cout << test.find(my_pair.first)->first << "|" << test.find(my_pair.first)->second << "\n"  ;
	test.insert(pair<int, std::string>(-4, "bar"));
	test.insert(pair<int, std::string>(2, "machin"));
	test.insert(pair<int, std::string>(3, "foo"));
	test.insert(pair<int, std::string>(746, "Marcel"));
	test.insert(pair<int, std::string>(1, "truc"));

  it = test.begin();
	pair<int, std::string> p = *it;
  std::cout << p.first << "|" << p.second <<'\n';
  it++;

  it = test.find(-4);
	std::cout << it->first << "|" << it->second <<'\n';
  while (it != test.end())
	{
      std::cout << it->first << ", " << it->second << '\n';
      it++;

	}

}
{
  std::cout << "asd";
  map<char,int> mymap;

  std::cout << "asd";
	if (mymap.begin() != mymap.end())
		std::cout << "This should not happen\n";
  mymap['b'] = 100;
  std::cout << "asd";
  mymap['a'] = 200;
  mymap['c'] = 300;

	if (mymap.begin() == mymap.end())
		std::cout << "This is wrong\n";
  // show content:
  for (map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); it++)
    std::cout << it->first << " => " << it->second << '\n';

	std::cout << "Hello there\n";
  map<char,int>::iterator asd;
  std::cout << "past" << "\n";
  asd = mymap.begin();
  std::cout << "past" << "\n";
	for (map<char,int>::const_iterator it=mymap.begin(); it!=mymap.end(); it++)
    std::cout << it->first << " => " << it->second << '\n';
	std::cout << "General Kenobi\n";

	map<char, int>::const_iterator it = mymap.begin();
	map<char, int>::const_iterator ti = mymap.end();
	std::cout << "Wupwup\n";

	it++;
	++it;
	it--;
	--it;

	ti--;
	--ti;
	++ti;
	ti++;

	ti = it;

	std::cout << "Trump is a kiddo\n";
	map<char, int>::iterator end = mymap.end();
	while(it != end)
	{
    	std::cout << it->first << " => " << it->second << '\n';
		it++;
	}
}

{
  map<char,int> mymap;

  mymap['x']=100;
  mymap['y']=200;
  mymap['z']=300;

  std::cout << "mymap contains:\n";
  for (map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  mymap.clear();
  mymap['a']=1101;
  mymap['b']=2202;

  std::cout << "mymap contains:\n";
  for (map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

}


{
  map<char,int> mymap;
  char c;

  mymap ['a']=101;
  std::cout << "assigned 'a'\n";
  mymap ['c']=202;
  std::cout << "assiged 'c'\n";
  mymap ['f']=303;
  std::cout << "assigned 'f'\n";

	std::cout << "end of assignations\n";
  for (c='a'; c<'h'; c++)
  {
    std::cout << c;
    if (mymap.count(c)>0)
      std::cout << " is an element of mymap.\n";
    else 
      std::cout << " is not an element of mymap.\n";
  }

}
{
  map<char,int> mymap;
  char c;

  mymap ['a']=101;
  std::cout << "assigned 'a'\n";
  mymap ['c']=202;
  std::cout << "assiged 'c'\n";
  mymap ['f']=303;
  std::cout << "assigned 'f'\n";

	std::cout << "end of assignations\n";
  for (c='a'; c<'h'; c++)
  {
    std::cout << c;
    if (mymap.count(c)>0)
      std::cout << " is an element of mymap.\n";
    else 
      std::cout << " is not an element of  mymap.\n";
  }

  
}

{
  map<char,int> mymap;

  mymap['a']=10;
  mymap['b']=20;
  mymap['c']=30;
  mymap['A']=30;
  std::cout<< mymap.size() << std::endl;

  while (!mymap.empty())
  {
    std::cout << mymap.begin()->first << " a=> " << mymap.begin()->second << '\n';
    mymap.erase(mymap.begin());
    std::cout<< mymap.size() << std::endl;

  }

  
}



{
  map<char,int> mymap;

  mymap['b'] = 100;
  mymap['a'] = 200;
  mymap['c'] = 300;

  // show content:
  for (map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); it++)
    std::cout << it->first << " => " << it->second << '\n';

std::cout << "\n\n========\n\n";


  for (map<char,int>::iterator it = --mymap.end(); it!=mymap.begin(); it--)
      std::cout << it->first << " => <" << it->second << '\n';
  
}


{
  map<char,int> mymap;

  mymap['a']=10;
  mymap['b']=20;
  mymap['c']=30;

  pair<map<char,int>::iterator,map<char,int>::iterator> ret;
  ret = mymap.equal_range('b');

  std::cout << "lower bound points to: ";
  std::cout << ret.first->first << " => " << ret.first->second << '\n';

  std::cout << "upper bound points to: ";
  std::cout << ret.second->first << " => " << ret.second->second << '\n';

  
}

{
  map<char,int> mymap;
  map<char,int>::iterator it;

  // insert some values:
  mymap['a']=10;
  mymap['b']=20;
  mymap['c']=30;
  mymap['d']=40;
  mymap['e']=50;
  mymap['f']=60;

  it=mymap.find('b');
  std::cout << "found b\n";
  mymap.erase (it);                   // erasing by iterator
  std::cout << "erase iterator to b\n";
  mymap.erase ('c');                  // erasing by key
  std::cout << "erase by key 'c'\n";
  it=mymap.find ('e');
  std::cout << "erase by range 'e' to end\n";
  mymap.erase ( it, mymap.end() );    // erasing by range

  std::cout << " display :\n";
  // show content:
  for (it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  
}


{
  map<char,int> mymap;
  map<char,int>::iterator it;

  mymap['a']=50;
  mymap['b']=100;
  mymap['c']=150;
  mymap['d']=200;

  it = mymap.find('b');
  if (it != mymap.end())
    mymap.erase (it);

  // print content:
  std::cout << "elements in mymap:" << '\n';
  std::cout << "a => " << mymap.find('a')->second << '\n';
  std::cout << "c => " << mymap.find('c')->second << '\n';
  std::cout << "d => " << mymap.find('d')->second << '\n';

  
}



{
  map<char,int> mymap;

  // first insert function version (single parameter):
  mymap.insert ( pair<char,int>('a',100) );
  mymap.insert ( pair<char,int>('z',200) );

  pair<map<char,int>::iterator,bool> ret;
  ret = mymap.insert ( pair<char,int>('z',500) );
  if (ret.second==false) {
    std::cout << "element 'z' already exists";
    std::cout << " with a value of " << ret.first->second << '\n';
  }

  // second insert function version (with hint position):
  map<char,int>::iterator it = mymap.begin();
  mymap.insert (it, pair<char,int>('b',300));  // max efficiency inserting
  mymap.insert (it, pair<char,int>('c',400));  // no max efficiency inserting

  // third insert function version (range insertion):
  map<char,int> anothermap;
  anothermap.insert(mymap.begin(),mymap.find('c'));

  // showing contents:
  std::cout << "mymap contains:\n";
  for (it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  std::cout << "anothermap contains:\n";
  for (it=anothermap.begin(); it!=anothermap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  
}
{
  map<char,int> mymap;

  map<char,int>::key_compare mycomp = mymap.key_comp();

  mymap['a']=100;
  mymap['b']=200;
  mymap['c']=300;


  char highest = mymap.rbegin()->first;     // key value of last element


  std::cout << "mymap contains:\n";
  map<char,int>::iterator it = mymap.begin();
  do {
    std::cout << it->first << " => " << it->second << '\n';
  } while ( mycomp((*it++).first, highest) );

  std::cout << '\n';

  
}

{
  map<char,int> mymap;
  map<char,int>::iterator itlow,itup;

  mymap['a']=20;
  mymap['b']=40;
  mymap['c']=60;
  mymap['d']=80;
  mymap['e']=100;

  itlow=mymap.lower_bound ('b');  // itlow points to b
  itup=mymap.upper_bound ('d');   // itup points to e (not d!)

  std::cout << "low : " << itlow->first << '\n';
  std::cout << "up : " << itup->first << '\n';

  mymap.erase(itlow,itup);        // erases [itlow,itup)

  // print content:
  for (map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  
}


{
  int i;
  map<int,int> mymap;

  if (mymap.max_size()>1000)
  {
    for (i=0; i<1000; i++) mymap[i]=0;
    std::cout << "The map contains 1000 elements.\n";
  }
  else std::cout << "The map could not hold 1000 elements.\n";

  
}
{
  map<char,std::string> mymap;

  mymap['a']="an element";
  mymap['b']="another element";
  mymap['c']=mymap['b'];

  std::cout << "mymap['a'] is " << mymap['a'] << '\n';
  std::cout << "mymap['b'] is " << mymap['b'] << '\n';
  std::cout << "mymap['c'] is " << mymap['c'] << '\n';
  std::cout << "mymap['d'] is " << mymap['d'] << '\n';

  std::cout << "mymap now contains " << mymap.size() << " elements.\n";

  
}

{
  map<char,int> mymap;

  mymap['x'] = 100;
  mymap['y'] = 200;
  mymap['z'] = 300;

  // show content:
  map<char,int>::reverse_iterator rit;
  for (rit=mymap.rbegin(); rit!=mymap.rend(); ++rit)
    std::cout << rit->first << " => " << rit->second << '\n';


	for (map<char,int>::const_reverse_iterator it=mymap.rbegin(); it!=mymap.rend(); it++)
    std::cout << it->first << " => " << it->second << '\n';

	map<char, int>::const_reverse_iterator it = mymap.rbegin();
	map<char, int>::const_reverse_iterator ti = mymap.rend();

	it++;
	++it;
	it--;
	--it;

	ti--;
	--ti;
	++ti;
	ti++;

	ti = it;

	map<char, int>::reverse_iterator end = mymap.rend();
	while(it != end)
	{
    	std::cout << it->first << " => " << it->second << '\n';
		it++;
	}


  
}







{
  map<char,int> mymap;

  mymap['x']=1001;
  mymap['y']=2002;
  mymap['z']=3003;

  std::cout << "mymap contains:\n";

  pair<char,int> highest = *mymap.rbegin();          // last element

  map<char,int>::iterator it = mymap.begin();
  do {
    std::cout << it->first << " => " << it->second << '\n';
  } while ( mymap.value_comp()(*it++, highest) );

  
}

{
  map<char,int> mymap;
  map<char,int>::iterator itlow,itup;

  mymap['a']=20;
  mymap['b']=40;
  mymap['c']=60;
  mymap['d']=80;
  mymap['e']=100;

  itlow=mymap.lower_bound ('b');  // itlow points to b
  itup=mymap.upper_bound ('d');   // itup points to e (not d!)

  mymap.erase(itlow,itup);        // erases [itlow,itup)

  // print content:
  for (map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  
}

{
  map<char,int> mymap;

  mymap['x'] = 100;
  mymap['y'] = 200;
  mymap['z'] = 300;

  // show content:
  map<char,int>::reverse_iterator rit;
  for (rit=mymap.rbegin(); rit!=mymap.rend(); ++rit)
    std::cout << rit->first << " => " << rit->second << '\n';

  
}




}