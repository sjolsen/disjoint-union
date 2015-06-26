#include "disjoint-union.hh"
#include <iostream>
#include <vector>

#define LIFT(fname) \
[] (auto&&... args) -> decltype (auto) \
{ \
	return fname (std::forward <decltype (args)> (args)...); \
}



void print_int (int i)
{
	std::cout << "Is int: " << i << std::endl;
}

void print_vec_impl (const std::vector <int>& v)
{
	std::cout << "[";
	auto p = begin (v);
	if (p != end (v))
		std::cout << *p;
	++p;
	for (; p != end (v); ++p)
		std::cout << ", " << *p;
	std::cout << "]";
}

void print_vec (std::vector <int>& v)
{
	std::cout << "Is lvalue vec: ";
	print_vec_impl (v);
	std::cout << std::endl;
}

void print_vec (const std::vector <int>& v)
{
	std::cout << "Is const lvalue vec: ";
	print_vec_impl (v);
	std::cout << std::endl;
}

void print_vec (std::vector <int>&& v)
{
	std::cout << "Is rvalue vec: ";
	print_vec_impl (v);
	std::cout << std::endl;
}



void print (int i) {print_int (i);}

void print (std::vector <int>& v) {print_vec (v);}
void print (const std::vector <int>& v) {print_vec (v);}
void print (std::vector <int>&& v) {print_vec (std::move (v));}



int main ()
{
	std::cout << "SIZE:" << std::endl;
	std::cout << "Size of int: " << sizeof (int) << std::endl
	          << "Size of vec int: " << sizeof (std::vector <int>) << std::endl
	          << "Size of int + vec int: "
	          << sizeof (sjo::disjoint_union <int, std::vector <int> >)
	          << std::endl;
	std::cout << std::endl;

	std::cout << "ALIGNMENT:" << std::endl;
	std::cout << "Align of int: " << alignof (int) << std::endl
	          << "Align of vec int: " << alignof (std::vector <int>) << std::endl
	          << "Align of int + vec int: "
	          << alignof (sjo::disjoint_union <int, std::vector <int> >)
	          << std::endl;
	std::cout << std::endl;

	auto p = sjo::disjoint_union <int, std::vector <int> >::create <0> (1);
	auto q = sjo::disjoint_union <int, std::vector <int> >::create <1> ({1, 2, 3});
	const auto r = q;

	std::cout << "ELIM:" << std::endl;
	p.elim (print_int, LIFT (print_vec));
	q.elim (print_int, LIFT (print_vec));
	r.elim (print_int, LIFT (print_vec));
	std::move (q).elim (print_int, LIFT (print_vec));
	std::cout << std::endl;

	std::cout << "APPLY:" << std::endl;
	p.apply (LIFT (print));
	q.apply (LIFT (print));
	r.apply (LIFT (print));
	std::move (q).apply (LIFT (print));
}
