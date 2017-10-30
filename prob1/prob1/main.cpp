//#include "inf_int.h"
//#include <iostream>
//#include <string.h>
//#include <stdlib.h>
//#include <string>
//
//using namespace std;
//
//int main()
//{
//	inf_int a, e;
//	inf_int b(-100);
//	inf_int c("321111111111122222222222233333333333444444444445555555555");
//	inf_int d("123451987651234572749499923455022211");
//	inf_int f(150);
//	inf_int g(f);
//
//	inf_int aa(-9999), bb(9999);
//	// cin >> g ;   // not required
//
//	a = b + c;
//	// e=g/f;       // not required
//	string str;
//	cin >> str;
//	inf_int a1(str.c_str());
//	cin >> str;
//	inf_int a2(str.c_str());
//
//	if (a1 > a2){
//		cout << "a1 + a2 = " << a1 + a2 << endl;
//	}
//	else if (a1 < a2){
//		cout << "a1 - a2 = " << a1 - a2 << endl;
//	}
//	cout << "a1 * a2 = " << a1 * a2 << endl;
//
//
//	/*
//	cout << "a : " << a << endl;
//	cout << "b : " << b << endl;
//	cout << "c : " << c << endl;
//	cout << "d : " << d << endl;
//	// cout << "e : " << e << endl;
//	cout << "f : " << f << endl;
//	// cout << "g : " << g << endl;
//	*/
//
//	return 0;
//}
#include "inf_int.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

inf_int arr[] = { 9234, 1245, 63, 0, -99, -413123 };
long long arr_ll[] = { 9234, 1245, 63, 0, -99, -413123 };

void print_compare(int i, int j, char op, int width);

int main()
{
	for (int i = 0; i < sizeof(arr) / sizeof(*arr); i++)
		for (int j = 0; j < sizeof(arr) / sizeof(*arr); j++)
		{
			//idx [+|-|*] idx: my_result, longlong_result, correct?
			print_compare(i, j, '+', 15);
			print_compare(i, j, '-', 15);
			print_compare(i, j, '*', 15);
		}
	return 0;
}

void print_compare(int i, int j, char op, int width)
{
	stringstream my, ll;

	if (op == '+')
	{
		my << arr[i] + arr[j];
		ll << arr_ll[i] + arr_ll[j];
	}
	else if (op == '-')
	{
		my << arr[i] - arr[j];
		ll << arr_ll[i] - arr_ll[j];
	}
	else if (op == '*')
	{
		my << arr[i] * arr[j];
		ll << arr_ll[i] * arr_ll[j];
	}
	else{
		cout << "check op" << endl;
		return;
	}

	cout << i << op << setw(6) << left << j;
	cout << setw(width) << my.str();
	cout << setw(width) << ll.str();
	cout << setw(width) << (my.str().compare(ll.str()) == 0 ? "Good" : "<!!!>");
	cout << endl;
}