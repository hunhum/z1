#include<float.h>
#define EPS 1e-15
class Num{
public:
	double val = 0;
	double eps = 16*DBL_EPSILON;
	Num();
	Num(double v, double e=16*DBL_EPSILON);
	int operator==(const Num&) const;
	int operator!=(const Num&) const;
	int operator>(const Num&) const;
	int operator<(const Num&) const;
	int operator>=(const Num&) const;
	int operator<=(const Num&) const;
	Num operator+(const Num&) const;
	Num operator+(double) const;
	Num operator-(const Num&) const;
	Num operator-(double) const;
	Num operator*(const Num&) const;
	Num operator*(double) const;
};
