// Метод серединных квадратов. Разрядность при вычислении 32 бита,
// разрядность результата 16 бит.

#include <string>
#include <clocale>
#include <vector>
#include <bitset>
#include <iostream>
#include "windows.h"
#include <stack>
#include <time.h> 

using namespace std;


int random(int& startNumber){
	if (startNumber != 0) {
		bitset<32> randomies = (startNumber << 15);
		bitset<16> create = { 0 };	
		int out;
		for (int i = 0; i < 16; i++)
			create[i] = randomies[i];
		out = create.to_ullong();
		out = out * out;
		//while (out > 10) {
		//	out = out / 10;
		//}
		cout << out << ' ';
		random(out);
	}
	else {
		cout << endl;
		return 0;
	}
}


int main() {
	//time_t timec = time(0);
	//double  startNumber = timec;
	while(true) {
		time_t timec = time(0) * time(0)/21;
		int  startNumber = timec;
		cout << startNumber << ':';
		random(startNumber);
		Sleep(2000);
		//startNumber = startNumber + 2832;
	}
}