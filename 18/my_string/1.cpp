#include <iostream>
#include "my_string.h"
using namespace std;

int main()
{
	/*
	my_string a("hello world!");
	my_string b(" hello Linux!");
	my_string c;
	c = a + b;
	cout << c << endl;
	getchar();
	*/
	my_string str("There are two needles in this haystack with needles.");
	my_string str2("needle");
	cout << str.npos << endl;
	// different member versions of find in the same order as above:
	int found = str.find(str2);
	//if (found != my_string::npos)
		cout << "first 'needle' found at: " << found << '\n';

	found = str.find("needles are small", found + 1, 6);
	//if (found != my_string::npos)
		cout << "second 'needle' found at: " << found << '\n';

	found = str.find("haystack");
	//if (found != my_string::npos)
		cout << "'haystack' also found at: " << found << '\n';

	found = str.find('.');
	//if (found != my_string::npos)
		cout << "Period found at: " << found << '\n';

	// let's replace the first needle:
	str.replace(str.find(str2), str2.length(), "preposition");
	cout << str << '\n';
		getchar();
	return 0;
}
