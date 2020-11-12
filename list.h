#pragma once
#include<utility>
template<typename T>
class List{
private:
	struct LNode{
		T value;
		LNode *prev = nullptr,*next = nullptr;
	};
	LNode *current,tmp;
public:
	class Iterator{
	public:
		LNode *current;
		Iterator();
		Iterator(List<T>::LNode *);
		void operator++();
		int operator!=(const Iterator&) const;
		int operator==(const Iterator&) const;
		const T& operator*() const;
	};
	List();
	~List();
	List(const List<T>&);
	List<T>& operator=(const List<T>&);
	void insert_b(T&& val);
	void insert_a(T&& val);
	void insert_b(const T& val);
	void insert_a(const T& val);
	void init();
	void reset();
	void up();
	void down();
	const T& get() const;
	void rm();
	int is_empty() const;
	int is_first() const;
	void clear();
	Iterator begin() const;
	Iterator end() const;
};

template<typename T>
List<T>::List(){
	init();
}
template<typename T>
List<T>::~List(){
	clear();
}
template<typename T>
List<T>::List(const List<T>& q){
	init();
	for(List<T>::Iterator i=q.begin(); i!=q.end(); ++i){
		insert_a(*i);
	}
}
template<typename T>
List<T>& List<T>::operator=(const List<T>& q){
	if(&q != this){
		clear();
		for(List<T>::Iterator i=q.begin(); i!=q.end(); ++i){
			insert_a(*i);
		}
	}
	return *this;
}
template<typename T>
List<T>::Iterator::Iterator(){
	this->current=nullptr;
}
template<typename T>
List<T>::Iterator::Iterator(List<T>::LNode *q){
	this->current=q;
}
template<typename T>
void List<T>::Iterator::operator++(){
	this->current = this->current->next;
}
template<typename T>
int List<T>::Iterator::operator!=(const List<T>::Iterator &q)const{
	if(this->current != q.current){return 1;}
	return 0;
}
template<typename T>
int List<T>::Iterator::operator==(const List<T>::Iterator &q)const{
	if(this->current == q.current){return 1;}
	return 0;
}
template<typename T>
const T& List<T>::Iterator::operator*() const{
	return this->current->value;
}
template<typename T>
typename List<T>::Iterator List<T>::begin() const{
	return Iterator(tmp.next);
}
template<typename T>
typename List<T>::Iterator List<T>::end() const{
	return Iterator(const_cast<List<T>::LNode *>(&tmp));
}
template<typename T>
void List<T>::insert_b(T&& val){
	LNode *x = new LNode;
	x->value=std::move(val);	
	x->prev = this->current->prev;
	x->next = this->current;
	x->prev->next = x;
	this->current->prev = x;
	if(is_empty()){down();}
}
template<typename T>
void List<T>::insert_a(T&& val){
	LNode *x = new LNode;
	x->value=std::move(val);
	x->next = this->current->next;
	x->prev = this->current;
	x->next->prev = x;
	this->current->next = x;
	if(is_empty()){up();}
}
template<typename T>
void List<T>::insert_b(const T& val){
	LNode *x = new LNode;
	x->value=val;	
	x->prev = this->current->prev;
	x->next = this->current;
	x->prev->next = x;
	this->current->prev = x;
	if(is_empty()){down();}
}

template<typename T>
void List<T>::insert_a(const T& val){
	LNode *x = new LNode;
	x->value=val;
	x->next = this->current->next;
	x->prev = this->current;
	x->next->prev = x;
	this->current->next = x;
	if(is_empty()){up();}
}

template<typename T>
void List<T>::init(){
	this->tmp.next=this->tmp.prev=&this->tmp;
	this->current=&this->tmp;
}
template<typename T>
void List<T>::reset(){
	this->current=this->tmp.next;
}
template<typename T>
void List<T>::up(){
	this->current = this->current->next;
	if(this->current==&this->tmp){this->current = this->current->next;}
}
template<typename T>
void List<T>::down(){
	this->current = this->current->prev;
	if(this->current==&this->tmp){this->current = this->current->prev;}
}
template<typename T>
const T& List<T>::get() const{
	if(!is_empty()){
		return this->current->value;
	}
	else{
		throw -1;
	}
}
template<typename T>
void List<T>::rm(){
	LNode *x;
	if(is_empty()){
		throw -1;
	}
	else{
		x = this->current;
		this->current->next->prev = this->current->prev;
		this->current->prev->next = this->current->next;
		up();
		delete x;
	}
}
template<typename T>
int List<T>::is_empty() const{
	if(this->current==&this->tmp){
		return 1;
	}
	return 0;
}
template<typename T>
int List<T>::is_first() const{
	if(is_empty()){return 0;}
	if(this->current==this->tmp.next){
		return 1;
	}
	return 0;
}
template<typename T>
void List<T>::clear(){
	while(!is_empty()){
		rm();
	}
}

