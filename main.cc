#include "disjoint-union.hh"
#include <iostream>
#include <vector>
#include "../sjo/lift.hh"

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
	auto p = disjoint_union <int, std::vector <int> >::create <0> (1);
	auto q = disjoint_union <int, std::vector <int> >::create <1> ({1, 2, 3});
	const auto r = q;

	p.elim (print_int, LIFT (print_vec));
	q.elim (print_int, LIFT (print_vec));
	r.elim (print_int, LIFT (print_vec));
	std::move (q).elim (print_int, LIFT (print_vec));

	p.apply (LIFT (print));
	q.apply (LIFT (print));
	r.apply (LIFT (print));
	std::move (q).apply (LIFT (print));
}
