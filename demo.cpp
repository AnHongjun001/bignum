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
	jc(100).print(' ');
	return 0;
}