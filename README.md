# bignum

大整数类（C++）

A C++ class for big-number operation, which can absolutely compatible with standard int.

## How to use my class

Run the command line below first to download the files.
```bash
git clone https://github.com/AnHongjun001/bignum.git
```

Create a new file, such as main.cpp, or directly write in the demo.cpp. You need to include *bigint.h* in your file then you can use the data-type *bigint*, which could store a big integer.

Run command like this when you need to Compile the program.(use demo.cpp for example)

```bash
g++ demo.cpp bigint.cpp
```
Then run *a.out* to start the program.

## Initialize

Here I show three methods to initialize a *bigint* data.

* Initialize without any parament, it will be initialized to 0.
```cpp
bigint a;
```

* Initialize with a standard integer. Here are two methods.
```cpp
bigint a = 12345;
bigint b(12345);
```

## I/O

You can input a *bigint* from your keyboard or ouput a *bigint* to your screen.

* Input: here are two methods.
```cpp
bigint a;
read(a);
```
```cpp
bigint b;
b.read();
```

* Output: use the method bigint.print()
```cpp
bigint a(335599);
a.print();
```

for more:
```
void bigint::print(char split='', char end='\n');
```

## Operation between big-numbers

I have already reloaded the operators. You can use them as you did at past.

```cpp
bigint a;
bigint b;
bigint c;

c = a + b;	//plus
c = a - b;	//minus
c = a * b;	//multiply
```

## Operation between big-number and integer

As I said at top, my class can absolutely compatible with standard int.

```cpp
bigint a;
bigint b;

b = a + 1453; 		//plus
b = a - (-122567); 	//minus
b = a * 33456		//multiply
b = a.pow(32)		//pow
```

## Logical operation between big-numbers
```cpp
bigint a;
bigint b;

a < b;
a > b;
a <= b;
a >= b;
a == b;
a != b;
```

## Logical operation between big-number and integer
```cpp
bigint a;

a < 3;
a > 3;
a <= 3;
a >= 3;
a == 3
a != 3
```

## demo

Here is a demo.


```cpp
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

If you have found any mistake, please contact me at 2637310873@qq.com. Thank you.