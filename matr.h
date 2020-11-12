#include"list.h"
#include<utility>
#include<set>
template<typename T>
class Matrix{
private:
	struct CellY{
		T value;
		int j = 0;
	};
	class CellX{
	private:
		List<Matrix<T>::CellY> *str;
		int i;
	public:
		CellX();
		~CellX();
		CellX(CellX&&);
		CellX(const CellX&);
		CellX& operator=(CellX&&);
		CellX& operator=(const CellX&);
		List<Matrix<T>::CellY>* gstr() const;
		int geti() const;
		void set(int);
		void nstr();
	};
	List<CellX> *ptr;
public:
	Matrix();
	Matrix(const Matrix<T>&);
	Matrix(Matrix<T>&&);
	Matrix<T>& operator=(const Matrix<T>&);
	Matrix<T>& operator=(Matrix<T>&&);
	~Matrix();
	void init();
	void clear();
	int getsizei() const;
	int getsizej() const;
	T get(int,int) const;
	void set(int,int,const T&);
	void replace(int,int);
	void lcomb(int,int,T);
	T ssum(int,int,int);
	Matrix<T> getPM(int,int,int,int);
	Matrix<T> getPM(const std::set<int> &,const std::set<int> &);
	List<CellX>* gptr() const;
	void nptr();
};

template<typename T>
Matrix<T>::Matrix(){
	init();
}
template<typename T>
Matrix<T>::Matrix(const Matrix<T> &q){
	init();
	this->ptr = new List<CellX>(*(q.gptr()));	
}
template<typename T>
Matrix<T>::Matrix(Matrix<T>&& q){
	this->ptr=q.gptr();
	q.nptr();
}
template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T> &q){
	if(this != &q){
		*(this->ptr)=*(q.gptr());
	}
	return *this;
}
template<typename T>
Matrix<T>& Matrix<T>::operator=(Matrix<T> &&q){
	if(this != &q){
		clear();
		this->ptr=q.gptr();
		q.nptr();
	}
	return *this;
}
template<typename T>
Matrix<T>::~Matrix(){
	clear();
}
template<typename T>
void Matrix<T>::nptr(){
	this->ptr = nullptr;
}
template<typename T>
List<typename Matrix<T>::CellX>* Matrix<T>::gptr() const{
	return this->ptr;
}
template<typename T>
Matrix<T>::CellX::CellX(){
	this->str = new List<CellY>;
	i = 0;
}
template<typename T>
Matrix<T>::CellX::~CellX(){
	delete this->str;
}
template<typename T>
Matrix<T>::CellX::CellX(const Matrix<T>::CellX &q){
	this->i = q.geti();
	this->str = new List<CellY>(*(q.gstr()));
}
template<typename T>
Matrix<T>::CellX::CellX(Matrix<T>::CellX &&q){
	this->i=q.geti();
	this->str=q.gstr();
	q.nstr();
}
template<typename T>
typename Matrix<T>::CellX& Matrix<T>::CellX::operator=(Matrix<T>::CellX &&q){
	if(this!=&q){
		this->i=q.geti();
		delete this->str;
		this->str=q.gstr();
		q.nstr();
	}
	return *this;
}
template<typename T>
typename Matrix<T>::CellX& Matrix<T>::CellX::operator=(const Matrix<T>::CellX &q){
	if(this!=&q){
		this->i=q.geti();
		*(this->str)=*(q.gstr());
	}
	return *this;
}
template<typename T>
List<typename Matrix<T>::CellY>* Matrix<T>::CellX::gstr() const{
	return str;
}
template<typename T>
int Matrix<T>::CellX::geti() const{
	return i;
}
template<typename T>
void Matrix<T>::CellX::set(int k){
	this->i=k;
}
template<typename T>
void Matrix<T>::CellX::nstr(){
	this->str=nullptr;
}
template<typename T>
void Matrix<T>::init(){
	this->ptr = new List<CellX>;
}
template<typename T>
void Matrix<T>::clear(){
	delete this->ptr;
}
template<typename T>
void Matrix<T>::set(int i,int j,const T& val){
	List<CellY> *str;
	bool fi=false;
	ptr->reset();
	if(!ptr->is_empty()){
		do{
			if(ptr->get().geti()==i){
				fi = true;
				str=ptr->get().gstr();
				str->reset();
				if(!str->is_empty()){
					do{
						if(str->get().j==j){
							str->rm();
							break;
						}
						str->up();
					}while(!str->is_first());
				}
				if(val!=T{}){
					CellY y={val,j};
					str->insert_a(y);
				}
				if(str->is_empty()){ptr->rm();}
				break;
			}
			ptr->up();
		}while(!ptr->is_first());
	}
	if(!fi && val!=T{}){
		CellY y={val,j};
		CellX x;
		x.gstr()->insert_a(y);
		x.gstr()->up();
		x.set(i);
		ptr->insert_a(std::move(x));
	}
}	
template<typename T>
T Matrix<T>::get(int i,int j) const{
	if(ptr->is_empty()){return T{};}
	List<CellY> *str;
	for(typename List<CellX>::Iterator it=ptr->begin();it!=ptr->end();++it){
		if((*it).geti()==i){
			str=(*it).gstr();
			for(typename List<CellY>::Iterator jt=str->begin();jt!=str->end();++jt){
				if((*jt).j==j){
					return (*jt).value;
				}
			}
		}
	}
	return T{};
}
template<typename T>
int Matrix<T>::getsizei() const{
	if(ptr->is_empty()){return 0;}
	int max = 0;
	for(typename List<CellX>::Iterator it=ptr->begin();it!=ptr->end();++it){
		if((*it).geti() > max){max = (*it).geti();}
	}
	return (!max) ? 0 : max+1;
}
template<typename T>
int Matrix<T>::getsizej() const{
	if(ptr->is_empty()){return 0;}
	int max = 0;
	List<CellY> *str;
	for(typename List<CellX>::Iterator it=ptr->begin();it!=ptr->end();++it){
		str=(*it).gstr();
		for(typename List<CellY>::Iterator jt=str->begin();jt!=str->end();++jt){
			if((*jt).j > max){max = (*jt).j;}
		}
	}
	return (!max) ? 0 : max+1;
}
template<typename T>
void Matrix<T>::replace(int k, int l){
	if(ptr->is_empty()){return;}
	ptr->reset();
	do{
		if(ptr->get().geti()==k){const_cast<CellX&>(ptr->get()).set(l);ptr->up();continue;}
		if(ptr->get().geti()==l){const_cast<CellX&>(ptr->get()).set(k);ptr->up();continue;}
		ptr->up();
	}while(!ptr->is_first());
}
template<typename T>
T Matrix<T>::ssum(int i, int j1, int j2){
	if(ptr->is_empty()){return T{};}
	T sum{};
	List<CellY> *str;
	for(typename List<CellX>::Iterator it=ptr->begin();it!=ptr->end();++it){
		if((*it).geti()==i){
			str=(*it).gstr();
			for(typename List<CellY>::Iterator jt=str->begin();jt!=str->end();++jt){
				if((*jt).j>=j1 && (*jt).j<=j2){
					sum=sum+(*jt).value;
				}
			}
		}
	}
	return sum;
}
template<typename T>
void Matrix<T>::lcomb(int k, int l, T a){
	if(ptr->is_empty()){return;}
	List<CellY> *str;
	CellX tmp;
	for(typename List<CellX>::Iterator it=ptr->begin();it!=ptr->end();++it){
		if((*it).geti()==l){
			tmp=(*it);
			str=tmp.gstr();
			for(typename List<CellY>::Iterator jt=str->begin();jt!=str->end();++jt){
				set(k,(*jt).j,get(k,(*jt).j)+a*((*jt).value));
			}
			return;
		}
	}
}
template<typename T>
Matrix<T> Matrix<T>::getPM(int i0, int i1, int j0, int j1){
	if(ptr->is_empty()){throw -2;}
	List<CellY> *str;
	int i,j;
	Matrix<T> m;
	for(typename List<CellX>::Iterator it=ptr->begin();it!=ptr->end();++it){
		i = (*it).geti();
		if(i>=i0 && i <= i1){
			str=(*it).gstr();
			for(typename List<CellY>::Iterator jt=str->begin();jt!=str->end();++jt){
				j=(*jt).j;
				if(j >= j0 && j <= j1){
					m.set(i-i0,j-j0,(*jt).value);
				}
			}
		}
	}
	return m;
}
template<typename T>
Matrix<T> Matrix<T>::getPM(const std::set<int> &ii,const std::set<int> &jj){
	if(ptr->is_empty()){throw -2;}	
	List<CellY> *str;
	int i,j;
	int i0=0,j0=0;
	Matrix<T> m;
	for(typename List<CellX>::Iterator it = ptr->begin(); it!=ptr->end(); ++it){
		i = (*it).geti();
		i0 = 0;
		for(std::set<int>::iterator sit = ii.begin(); sit!=ii.end() && i >= *sit; ++sit){
		if(i == *sit){
			str=(*it).gstr();
			for(typename List<CellY>::Iterator jt = str->begin(); jt!=str->end(); ++jt){
				j=(*jt).j;
				j0 = 0;
				for(std::set<int>::iterator sjt = jj.begin(); sjt!=jj.end() && j >= *sjt; ++sjt){
				if(j == *sjt){
					m.set(i0,j0,(*jt).value);
				}
				j0++;
				}
			}
		}
		i0++;
		}
	}
	return m;
}
