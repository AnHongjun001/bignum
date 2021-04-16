# bignum
A C++ class for big-number operation

```cpp
#include <cstdio>
#include "bigint.h"
using namespace std;

bigint jc(int n){
	if(n == 0){
		bigint res(1);
		return res;
	}
	return jc(n-1)*n;
}

int main(){
	//initialize a big-number to zero
	bigint c;	//0
	//initialize a big-number with a standard integer
	bigint a(12345);
	bigint b = 144556643;
	//operation between big-numbers
	c = a + b;
	c.print();
	c = a - b;
	c.print();
	(b-a).print();
	(a*b).print();
	//operation between big-number and standard integer
	(a + 1234).print();
	(b - 3322).print();
	(a * (-5)).print();
	//operation of power
	a.pow(5).print();	//O(log n)
	//input a big-number from keyboard
	read(a);
	a.print();

	b.read();
	b.print();
	//calculate factorial(100)
	jc(100).print(' ');
	return 0;
}

```
