#include <iostream>
#include <sstream>

using namespace std;

int main()
{
	string st;
	getline(cin,st);
	istringstream iss;
	iss.str(st);
	iss.clear();
	string s;
	iss >> s;
	cout << s << " ";
	if(s == "CPU")
	{
		int a,b,c;
		iss >> a >> b >> c;
		if(a == 2)
		{
			cout << "LUyManu" << endl;
		}
	}
}