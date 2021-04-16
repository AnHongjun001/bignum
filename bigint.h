#ifndef BIGINT_HPP
#define BIGINT_HPP

#define BIGINT_MAXLEN 1000
#define BIGINT_BASE 10000
#define BIGINT_DEBUG OFF

class bigint;
void read(bigint& number);

class bigint{
private:
	int sign = 1;
	int data[BIGINT_MAXLEN];
	bigint abs_plus(const bigint& a, const bigint& b);
	bigint abs_minus(const bigint& a, const bigint& b);
	int abs_cmp(const bigint& a, const bigint& b);
public:
	bigint();
	bigint(int init_number);
	bool operator > (const bigint& b);
	bool operator > (const int& b);
	bool operator < (const bigint& b);
	bool operator < (const int& b);
	bool operator >= (const bigint& b);
	bool operator >= (const int& b);
	bool operator <= (const bigint& b);
	bool operator <= (const int& b);
	bool operator == (const bigint& b);
	bool operator == (const int& b);
	bool operator != (const bigint& b);
	bool operator != (const int& b);
	bigint operator + (const bigint& b);
	bigint operator + (const int& b);
	bigint operator - (const bigint& b);
	bigint operator - (const int& b);
	bigint operator * (const bigint& b);
	bigint operator * (const int& b);
	bigint operator = (int& init_number);
	void read();
	void print();
	void print(char split);
	void print(char split, char end);
	bool zero();
	bigint pow(int n);	//O(log n)
	
	#if BIGNUM_DEBUG == ON
	void debug();
	#endif
};

#endif