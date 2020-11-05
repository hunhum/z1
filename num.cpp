#include"num.h"
#include<algorithm>
#include<cmath>
Num::Num(){
	this->val=0;
	this->eps = DBL_EPSILON;
}
Num::Num(double v,double e){
	this->val = v;
	this->eps = e;
}
int Num::operator==(const Num& q) const{
	if(q.val!=0){
		return (fabs(val)-fabs(q.val))<eps*(fabs(val));
	}
	return fabs(val)<=EPS;
}
int Num::operator!=(const Num& q) const{
	if(q.val!=0){
		return ((fabs(val)-fabs(q.val))>=eps*fabs(val));
	}
	return fabs(val)>EPS;
}
int Num::operator>(const Num& q) const{
	if((*this)!=q){
		if(val>q.val){return 1;}
	}
	return 0;
}	
int Num::operator<(const Num& q) const{
	if((*this)!=q){
		if(val<q.val){return 1;}
	}
	return 0;
}
int Num::operator>=(const Num& q) const{
	return !operator<(q);
}
int Num::operator<=(const Num& q) const{
	return !operator>(q);
}
Num Num::operator+(const Num& q) const{
	return Num(val+q.val,std::max<double>(eps,q.eps));
}
Num Num::operator+(double q) const{
	return operator+(Num(q));
}
Num Num::operator-(const Num& q) const{
	return Num(val-q.val,std::max<double>(eps,q.eps));
}
Num Num::operator-(double q) const{
	return operator-(Num(q));
}
Num Num::operator*(const Num& q) const{
	return Num(val*q.val,eps+q.eps);
}
Num Num::operator*(double q) const{
	return operator*(Num(q));
}
