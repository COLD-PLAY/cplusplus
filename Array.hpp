#pragma once

#include <iostream>

using namespace std;

template<typename T>
class Array {
public:
	Array(int capacity) : m_capacity(capacity), m_size(0) {
		//cout << "Array's constructor" << endl;
		if (capacity <= 0) throw "Capacity must bigger than zero!";
		m_pAddress = new T[capacity];
	}

	~Array() {
		if (m_pAddress) {
			//cout << "Array's deconstructor" << endl;
			delete[] m_pAddress;
			m_pAddress = nullptr;
		}
	}

	Array(const Array& array) {
		//cout << "Array's copy constructor" << endl;
		m_capacity = array.m_capacity;
		m_size = array.m_size;
		m_pAddress = new T[m_capacity];
		for (int i = 0; i < m_size; i++) {
			m_pAddress[i] = array.m_pAddress[i];
		}
	}

	Array& operator=(const Array& array) {
		//cout << "Array's = function" << endl;
		if (m_pAddress) {
			delete[] m_pAddress;
			m_pAddress = nullptr;
		}
		m_capacity = array.m_capacity;
		m_size = array.m_size;
		m_pAddress = new T[m_capacity];
		for (int i = 0; i < m_size; i++) {
			m_pAddress[i] = array.m_pAddress[i];
		}
		return *this;
	}

	void push_back(const T& value) {
		if (m_capacity == m_size) {
			throw "Array is full!";
		}
		m_pAddress[m_size++] = value;
	}

	void pop_back() {
		if (m_size == 0) {
			throw "Array is empty!";
		}
		m_size--;
	}

	bool empty() {
		return m_size == 0;
	}

	T& operator[](int index) {
		if (index >= m_size) {
			throw "Index is out of range!";
		}
		return m_pAddress[index];
	}

	int capacity() {
		return m_capacity;
	}

	int size() {
		return m_size;
	}

	T* begin() {
		return m_pAddress;
	}

	T* end() {
		return m_pAddress + m_size;
	}

private:
	T* m_pAddress;
	int m_capacity;
	int m_size;
};