// SmartPointer.h
#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

template <typename T>
class SmartPointer {
  T* data;
public:
  SmartPointer(const T&);
  T& operator*(); // gets value held
  const T& operator*() const; // gets value held
  SmartPointer<T>& operator=(const T&); // assigns value
  // Add Your declarations here
  SmartPointer(SmartPointer<T> x);
  SmartPointer<T>& operator=(SmartPointer<T> x)

};

template <typename T>
SmartPointer<T>::SmartPointer(const T& data) {
  this->data = new T(data); 
  // allocate on heap for T (regardless of size)
}

template <typename T>
T& SmartPointer<T>::operator*() { 
  // get value held in smart pointer
  return *data;
}

template <typename T>
const T& SmartPointer<T>::operator*() const { 
  // get value held in smart pointer
  return *data;
}

// note: this is _not_ copy assignmewnt
template <typename T>
SmartPointer<T>& SmartPointer<T>::operator=(const T& data) { 
  // assign value to smart pointer
  *(this->data) = data;
  return *this;
}

// Add your definitions here


//constructor that takes another smart pointer as the parameter
//and assigns the data value of that to this->data.
template <typename T> 
SmartPointer<T>::SmartPointer(SmartPointer<T> x) {
	this->data = x->data;
}


//function that assigns the data of the smart pointer on the rhs to the data of
//the smart pointer on the left hand side.
template <typename T> 
SmartPointer<T>& SmartPointer<T>::operator=(SmartPointer<T> x) {
	this->data = x.data;
	return *this;
}
#endif