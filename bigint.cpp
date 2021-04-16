#include "bigint.h"

#include <memory.h>
#include <cstdio>
#include <cstring>
#include <algorithm>

bigint::bigint(){
	memset(data, 0, BIGINT_MAXLEN * sizeof(int));
	data[0] = 1;
	sign = 1;
}

bigint::bigint(int init_number){
	*this = init_number;
}

bool bigint::operator > (const bigint& b){
	if(sign>0 && b.sign<0) return true;
	if(sign>0 && b.sign>0){
		int cmp = abs_cmp(*this, b);
		return cmp>0 ? true : false;
	}
	if(sign<0 && b.sign<0){
		int cmp = abs_cmp(*this, b);
		return cmp>0 ? false : true;
	}
	if(sign<0 && b.sign>0) return false;
	return true;
}

bool bigint::operator > (const int& b){
	bigint tmp(b);
	return *this > tmp;
}

bool bigint::operator < (const bigint& b){
	if(sign>0 && b.sign<0) return false;
	if(sign>0 && b.sign>0){
		int cmp = abs_cmp(*this, b);
		return cmp<0 ? true : false;
	}
	if(sign<0 && b.sign<0){
		int cmp = abs_cmp(*this, b);
		return cmp<0 ? false : true;
	}
	if(sign<0 && b.sign>0) return true;
	return true;
}

bool bigint::operator < (const int& b){
	bigint tmp(b);
	return *this < tmp;
}

bool bigint::operator >= (const bigint& b){
	return (*this>b || *this==b);
}

bool bigint::operator >= (const int& b){
	bigint tmp(b);
	return *this >= tmp;
}

bool bigint::operator <= (const bigint& b){
	return (*this<b || *this==b);
}

bool bigint::operator <= (const int& b){
	bigint tmp(b);
	return *this <= tmp;
}

bool bigint::operator == (const bigint& b){
	if(sign != b.sign) return false;
	return abs_cmp(*this, b) == 0;
}

bool bigint::operator == (const int& b){
	bigint tmp(b);
	return *this == tmp;
}

bool bigint::operator != (const bigint& b){
	return !(*this == b);
}

bool bigint::operator != (const int& b){
	bigint tmp(b);
	return *this != tmp;
}

bigint bigint::operator + (const bigint& b){
	bigint res;
	if(sign>0 && b.sign<0){
		bigint bb = b;
		bb.sign = 1;
		return *this - bb;
	}
	if(sign>0 && b.sign>0){
		res = abs_plus(*this, b);
		return res;
	}
	if(sign<0 && b.sign<0){
		res = abs_plus(*this, b);
		res.sign = -1;
		return res;
	}
	if(sign<0 && b.sign>0){
		int cmp = abs_cmp(*this, b);
		if(cmp == 0) return res;
		else if(cmp>0){
			res = abs_minus(*this, b);
			res.sign = -1;
			return res;
		}else{
			res = abs_minus(b, *this);
			return res;
		}
	}
	return res;
}

bigint bigint::operator + (const int& b){
	bigint tmp(b);
	return *this + tmp;
}

bigint bigint::operator - (const bigint& b){
	bigint res;
	if(sign>0 && b.sign<0){
		res = abs_plus(*this, b);
		return res;
	}
	if(sign>0 && b.sign>0){
		int cmp = abs_cmp(*this, b);
		if(cmp == 0) return res;
		else if(cmp>0){
			res = abs_minus(*this, b);
			return res;
		}else{
			res = abs_minus(b, *this);
			res.sign = -1;
			return res;
		}
	}
	if(sign<0 && b.sign<0){
		int cmp = abs_cmp(*this, b);
		if(cmp == 0) return res;
		else if(cmp>0){
			res = abs_minus(*this, b);
			res.sign = -1;
			return res;
		}else{
			res = abs_minus(b, *this);
			return res;
		}
	}
	if(sign<0 && b.sign>0){
		res = abs_plus(*this, b);
		res.sign = -1;
		return res;
	}
	return res;
}

bigint bigint::operator - (const int& b){
	bigint tmp(b);
	return *this - tmp;
}

bigint bigint::operator * (const bigint& b){
	bigint res;
	int carry = 0, i, j;
	memset(res.data, 0, sizeof(BIGINT_MAXLEN * sizeof(int)));
	for(i = 1; i<=data[0]; ++i){
		for(j = 1; j<=b.data[0]; ++j){
			res.data[i+j-1] += carry + data[i]*b.data[j];
			carry = res.data[i+j-1] / BIGINT_BASE;
			res.data[i+j-1] %= BIGINT_BASE;
		}
		j = b.data[0] + i;
		while(carry){
			res.data[j++] = carry % BIGINT_BASE;
			carry /= BIGINT_BASE;
		}
	}
	res.data[0] = data[0] + b.data[0];
	while(!res.data[res.data[0]]) --res.data[0];
	if(!res.data[0]) res.data[0] = 1;
	res.sign = sign * b.sign;
	return res;
}

bigint bigint::operator * (const int& b){
	bigint tmp(b);
	return (*this) * tmp;
}

bigint bigint::operator = (int& init_number){
	memset(data, 0, BIGINT_MAXLEN * sizeof(int));
	sign = 1;
	if(init_number<0){
		sign = -1;
		init_number *= -1;
	}
	while(init_number){
		data[++(*data)] = init_number % BIGINT_BASE;
		init_number /= BIGINT_BASE;
	}
	return *this;
}

void bigint::read(){
	char s[BIGINT_MAXLEN/4];
	std::scanf("%s", s);
	char *ss = s;
	std::memset(data, 0, BIGINT_MAXLEN * sizeof(int));
	sign = 1;
	if(s[0] == '-'){
		sign = -1;
		++ss;
	}
	for(char* p = ss + std::strlen(ss) - 4; p>ss; p -= 4){
		data[++data[0]] = atoi(p);
		*p = '\0';
	}
	data[++data[0]] = atoi(ss);
}

void read(bigint& number){
	number.read();
}

void bigint::print(){
	bigint::print('\0', '\n');
}

void bigint::print(char split){
	bigint::print(split, '\n');
}

void bigint::print(char split, char end){
	if(sign<0) std::printf("-");
	std::printf("%d", data[data[0]]);
	if(split != '\0') std::printf("%c", split);
	for(int i = data[0]-1; i>0; --i){
		std::printf("%04d", data[i]);
		if(split != '\0') std::printf("%c", split);
	}
	std::printf("%c", end);
}

bool bigint::zero(){
	if(data[0]>1) return false;
	return data[1] == 0;
}

bigint bigint::pow(int n){
	bigint res(1);
	bigint a = *this;
	while(n){
		if(n & 1) res = res * a;
		a = a * a;
		n >>= 1;
	}
	return res;
}

bigint bigint::abs_plus(const bigint& a, const bigint& b){
	bigint res;
	int carry = 0;
	res.data[0] = std::max(a.data[0], b.data[0]);
	for(int i = 1; i<=res.data[0]; ++i){
		res.data[i] = a.data[i] + b.data[i] + carry;
		carry = res.data[i] / BIGINT_BASE;
		res.data[i] %= BIGINT_BASE;
	}
	while(carry){
		res.data[++res.data[0]] = carry % BIGINT_BASE;
		carry /= BIGINT_BASE;
	}
	return res;
}

bigint bigint::abs_minus(const bigint& a, const bigint& b){	//abs(a)>abs(b)
	bigint res = a;
	for(int i = 1; i<=res.data[0]; ++i){
		res.data[i] -= b.data[i];
		if(res.data[i]<0){
			res.data[i] += BIGINT_BASE;
			--res.data[i+1];
		}
	}
	while(res.data[res.data[0]] == 0) --res.data[0];
	return res;
}

int bigint::abs_cmp(const bigint& a, const bigint& b){
	if(a.data[0] != b.data[0]) return a.data[0] - b.data[0];
	int len = a.data[0];
	for(int i = len; i; --i)
		if(a.data[i] != b.data[i]) return a.data[i] - b.data[i];
	return 0;
}

#if BIGINT_DEBUG == ON
void bigint::debug(){
	std::printf("##---debug---##\n");
	std::printf("sign:%d\n", sign);
	std::printf("len:%d\n", data[0]);
	for(int i = 1; i<data[0]; ++i) 
		std::printf("%04d ", data[i]);
	std::printf("%d\n", data[data[0]]);
	std::printf("##--EndDebug--##");
}
#endif