#pragma once
#include <vector>
#include <iterator>

template<typename T> class Pole {
public:
	Pole(size_t chunk = 100) : chunk_(chunk), size_(0) {}
	void push_back(const T& x) { resize(++size_); (*this)[size_ - 1] = x; }
	T& operator[] (size_t i) { return hrabe_[i / chunk_][i % chunk_]; }
	T& at(size_t i) { check(i); return (*this)[i]; }

	iterator begin() { return iterator(...); }
	iterator end() { return iterator(...); }
private:
	void check(size_t i) { if (i >= size_)  throw; }
	void resize(size_t i) {
		for (size_t k = hrabe_.size(); k <= i / chunk_; ++k)
			hrabe_.push_back(std::make_unique< T[]>(chunk_));
	}
	size_t chunk_;
	size_t size_;
	std::vector< std::unique_ptr<T[]>> hrabe_;
};

template <typename T>
class Pole<T>::iterator
{
public:
	iterator() :p_(nullptr), i_(0) {};
	iterator(const iterator& it) :p_(it.p_), i_(it.i_) {};
	iterator(Pole<T>* p, size_t i) :p_(p), i_(i) {};
	bool operator!=(const iterator& it2) {
		return p_ != it2.p_ || i_ != it2.i_;
	}
	T& operator*() { return (*p_)[i_]; }
	iterator operator++() { i_++; return *this; }
private:
	Pole<T>* p_;
	size_t i_;
};

