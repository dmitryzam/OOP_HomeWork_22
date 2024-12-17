#pragma once
#include<iostream>

namespace my_std {
	// Свой класс unique_ptr:
	template<typename T>
	class unique_ptr {
	private:
		T* m_ptr;
	public:
		unique_ptr() : m_ptr(nullptr) {}
		~unique_ptr() { delete m_ptr; }
		unique_ptr(const unique_ptr& obj) = delete;		// конструктор копирования блокируем
		unique_ptr(unique_ptr&& obj) : m_ptr(obj.m_ptr) { obj.m_ptr = nullptr; }
		unique_ptr& operator=(const unique_ptr& obj) = delete;	// оператор присваивания копированием блокируем
		unique_ptr& operator=(unique_ptr&& obj) {
			if (&obj == this)
				return* this;
			delete m_ptr;
			m_ptr = obj.m_ptr;
			obj.m_ptr = nullptr;
			return *this;
		}
		unique_ptr(T* ptr) { m_ptr = ptr; }

		T& operator*() { return *m_ptr; }
		T* operator->() { return m_ptr; }
		T* get() { return m_ptr; }

		void reset() {
			delete m_ptr;
			m_ptr = nullptr;
		}	
		bool isEmpty()const { return m_ptr == nullptr; }
	};
	
	class Counter {
	private:
		unsigned int m_counter{};
	public:
		Counter() : m_counter(0){}
		Counter(const Counter&) = delete;
		Counter& operator=(const Counter&) = delete;
		~Counter(){}
		void reset() { m_counter = 0; }
		unsigned int get() { return m_counter; }
		void operator++() { m_counter++; }
		void operator++(int) { m_counter++; }
		void operator--() { m_counter--; }
		void operator--(int) { m_counter--; }
		friend std::ostream& operator<<(std::ostream& out, const Counter& obj) {
			out << "Counter value: " << obj.m_counter;
			return out;
		}	
	};
	template<typename T>
	class shared_ptr {
	private:
		Counter* m_counter;
		T* m_ptr;
	public:
		shared_ptr(T* ptr = nullptr) { m_ptr = ptr; m_counter = new Counter(); (*m_counter)++; }
		shared_ptr(shared_ptr<T>& sp) {
			m_ptr = sp.m_ptr;
			m_counter = sp.m_counter;
			(*m_counter)++;
		}
		unsigned int use_count() { return m_counter->get(); }
		T* get() { return m_ptr; }
		T& operator*() { return *m_ptr; }
		T* operator->() { return m_ptr; }
		void operator=(shared_ptr sp){
			if (m_ptr != sp.m_ptr) {
				if (m_ptr && m_counter) {
					(*m_counter)--;
					if ((m_counter->get()) == 0) {
						delete m_counter;
						delete m_ptr;
					}
				}
				m_ptr = sp.m_ptr;
				if (m_ptr) {
					m_counter = sp.m_counter;
					(*m_counter)++;
				}
			}
		}
		~shared_ptr() {
			(*m_counter)--;
			if (m_counter->get() == 0) {
				delete m_counter;
				delete m_ptr;
			}
		}
		friend std::ostream& operator<<(std::ostream& out, shared_ptr<T>& obj) {
			out << "Address pointed: " << obj.get() << std::endl;
			out << *(obj.m_counter) << std::endl;
			return out;
		}	
	};
}