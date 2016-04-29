#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
/*
int main()
{
	string st;
	getline(cin,st);
	istringstream iss;
	iss.str(st); //hay que ponerlo
	iss.clear(); //hay que ponerlo
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
*/

int main() {
	vector<int> tiempos;
	for(int i = 0; i<6; i++){
		tiempos[i] = 0;
	}
	string st;
	string s;
	getline(cin,st);
	istringstream iss;
	iss.str(st); //hay que ponerlo
	iss.clear(); //hay que ponerlo
	iss >> s;
	if(s == "CPU") {
		int a,b,c;
		iss >> a >> b >> c;
		tiempos[b]++;
	}

	while(s != ""){

		getline(cin,st);
		istringstream iss;
		iss.str(st); //hay que ponerlo
		iss.clear(); //hay que ponerlo
		iss >> s;
		if(s == "CPU") {
			int a,b,c;
			iss >> a >> b >> c;
			tiempos[b]++;
		}
	}

}
