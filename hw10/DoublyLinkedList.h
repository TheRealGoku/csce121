#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
#include "Node.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;
//////////////////////////////////////////////////////////////////////////////
//                         class template definition                        //
//////////////////////////////////////////////////////////////////////////////

template<typename T>
class DoublyLinkedList {
public:
    /* uncomment the declarations as you implement them */
    DoublyLinkedList();
    DoublyLinkedList(T);
    DoublyLinkedList(const DoublyLinkedList<T>&);
    DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>&);
    ~DoublyLinkedList();
    unsigned int size() const { return sz; }
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    void push_back(T);
    void push_front(T);
    void pop_back();
    void pop_front();
    void erase(unsigned int);
    void insert(T data, unsigned int idx);
    void clear();
    std::string to_str() const;
    // breaks encapsulation... gives operator== access to private data... not great approach, but makes the homework easier for you since we haven't talked about iterators :).
    template<typename U> friend bool operator==(DoublyLinkedList<U> const&, DoublyLinkedList<U> const&);
private:
    // do not change ordering.
    Node<T> *head;
    Node<T> *tail;
    unsigned int sz;
};

//////////////////////////////////////////////////////////////////////////////
//                       helper function declarations                       //
//////////////////////////////////////////////////////////////////////////////
template<typename T> std::ostream& operator<<(std::ostream &, DoublyLinkedList<T> const&);

template<typename T> bool operator==(DoublyLinkedList<T> const&, DoublyLinkedList<T> const&);

template<typename T> bool operator!=(DoublyLinkedList<T> const&, DoublyLinkedList<T> const&);

//////////////////////////////////////////////////////////////////////////////
//                     member template function definitions                 //
//////////////////////////////////////////////////////////////////////////////
template<typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr), sz(0) {}

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(T data) : DoublyLinkedList() {
	Node<T>* x = new Node<T>(data);
	head = x;
	tail = x;
	sz = 1;
}

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T> &rhs) : DoublyLinkedList() {
	Node<T>* x = rhs.head;
	while (x) {
		push_back(x->data);
		x = x->next;
	}
}

template<typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T> &rhs) {
	clear();
	Node<T>* x = rhs.head;
	while (x) {
		push_back(x->data);
		x = x->next;
	}
	return *this;
}

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
	clear();
}

template<typename T>
T& DoublyLinkedList<T>::front() {
	return (head->data);
}

template<typename T>
const T& DoublyLinkedList<T>::front() const {
	return (head->data);
}

template<typename T>
T& DoublyLinkedList<T>::back() {
	return (tail->data);
}

template<typename T>
const T& DoublyLinkedList<T>::back() const {
	return (tail->data);
}

template<typename T>
void DoublyLinkedList<T>::push_back(T data) {
	Node<T> *add = new Node<T>(data);
	if (sz) {
		add->prev = tail;
		tail->next = add;
		tail = add;
	}
	else {
		head = add;
		tail = add;
	}
	sz++;
}

template<typename T>
void DoublyLinkedList<T>::push_front(T data) {
	Node<T> *add = new Node<T>(data);
	if (sz) {
		add->next = head;
		head->prev = add;
		head = add;
	}
	else {
		head = add;
		tail = add;
	}
	sz++;
}

template<typename T>
void DoublyLinkedList<T>::pop_back() {
	if (sz) {
		Node<T> *pre = tail->prev;
		delete tail;
		tail = pre;
		if (tail)
			tail->next = nullptr;
		sz--;
		if (!sz)
			head = nullptr;
	}
}

template<typename T>
void DoublyLinkedList<T>::pop_front() {
	if (sz) {
		Node<T> *aft = head->next;
		delete head;
		head = aft;
		if (head)
			head->prev = nullptr;
		sz--;
	}
	if (!sz)
		tail = nullptr;
}

template<typename T>
void DoublyLinkedList<T>::erase(unsigned int idx) {
	if (idx >= sz) {
		return;
	}
	if (!idx) {
		pop_front();
		return;
	}
	if (idx == sz - 1) {
		pop_back();
		return;
	}
	Node<T> *x = head;
	while (idx) {
		x = x->next;
		idx--;
	}
	x->prev->next = x->next;
	x->next->prev = x->prev;
	delete x;
	sz--;
}

template<typename T>
void DoublyLinkedList<T>::insert(T data, unsigned int idx) {
	if (idx >= sz) {
		return;
	}
	if (!idx) {
		push_front(data);
		return;
	}
	
	Node<T> *add = new Node<T>(data);
	Node<T> *x = head;
	while (idx) {
		x = x->next;
		idx--;
	}
	add->prev = x->prev;
	add->next = x;
	x->prev->next = add;
	x->prev = add;
	sz++;
}

template<typename T>
void DoublyLinkedList<T>::clear() {
	while(head) {
		pop_front();
	}
}

template<typename T>
std::string DoublyLinkedList<T>::to_str() const {
    std::stringstream os;
    const Node<T> *curr = head;
    os << std::endl << std::setfill('-') << std::setw(80) << '-' << std::setfill(' ') << std::endl;
    os << "head: " << head << std::endl;
    os << "tail: " << tail << std::endl;
    os << "  sz: " << sz << std::endl;
    os << std::setw(16) << "node" << std::setw(16) << "node.prev" << std::setw(16) << "node.data" <<  std::setw(16) << "node.next" << std::endl;
    while (curr) {
        os << std::setw(16) << curr;
        os << std::setw(16) << curr->prev;
        os << std::setw(16) << curr->data;
        os << std::setw(16) << curr->next;
        os << std::endl;
        curr = curr->next;
    }
    os << std::setfill('-') << std::setw(80) << '-' << std::setfill(' ') << std::endl;
    return os.str();
}

//////////////////////////////////////////////////////////////////////////////
//                     helper template function definitions                 //
//////////////////////////////////////////////////////////////////////////////
template<typename T>
bool operator==(DoublyLinkedList<T> const& lhs, DoublyLinkedList<T> const& rhs) {
    if (lhs.sz != rhs.sz) {
		return false;
	}
	Node<T> *cur = lhs.head;
	Node<T> *cur2 = rhs.head;
	while (cur && cur2) {
		if (cur->data != cur2->data) {
			return false;
		}
		cur = cur->next;
		cur2 = cur2->next;
	}
    return true;
}

template<typename T> 
bool operator!=(DoublyLinkedList<T> const& lhs, DoublyLinkedList<T> const& rhs) {
	return !(lhs == rhs);
}

template<typename T>
std::ostream& operator<<(std::ostream& os, DoublyLinkedList<T> const& rhs)
{
    os << rhs.to_str();
    return os;
}

#endif
