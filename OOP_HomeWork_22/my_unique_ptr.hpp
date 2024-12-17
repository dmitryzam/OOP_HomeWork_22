#pragma once
#include<iostream>

template<typename T>
class my_unique_ptr {
private:
	T* m_ptr;
public:
	my_unique_ptr() : m_ptr(nullptr);
	~my_unique_ptr();
	my_unique_ptr(const my_unique_ptr& obj) = delete;
	my_unique_ptr(my_unique_ptr&& obj);

};

template<typename T>
inline my_unique_ptr<T>::my_unique_ptr(){
	std::cout << "unique_ptr has been created!\n";
}

template<typename T>
inline my_unique_ptr<T>::~my_unique_ptr(){
	delete m_ptr; 
	std::cout << "unique_ptr has been deleted!\n";
}

template<typename T>
inline my_unique_ptr<T>::my_unique_ptr(my_unique_ptr&& obj){
	if (&obj == this)
		return *this;
	delete m_ptr;
	m_ptr = obj.m_ptr;
	obj.m_ptr = nullptr;
	return *this;
}
