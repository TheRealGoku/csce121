// SCLL.h
#ifndef SCLL_H
#define SCLL_H

#include <iostream>
#include "Node.h"

template <typename T>
class SortedCircularList {
  Node<T>* head;  
  Node<T>* tail;
public:
  SortedCircularList() : head(nullptr), tail(nullptr) {}
  void print(std::ostream& out=std::cout) const;
  // insert val into a sorted circular list
  void insertValue(const T& val);
};

// print function
template <typename T>
void SortedCircularList<T>::print(std::ostream& out) const {
   Node<T>* current=head;
   if (current!=nullptr) {
      out<<current->data<<" ";
      while(current->next != head)
   {
         current = current->next;   
         out<<current->data<<" ";
      }
   }
}

// WRITE THIS FUNCTION
template <typename T>
void SortedCircularList<T>::insertValue(const T& val)  {
	if (head != nullptr) {
		Node<T> *x = new Node<T>(val);
		//if val is greater than the larger value in the the SCL
		if (tail != nullptr && val > tail->data) {
			tail->next = x;
			x->next = head;
		}
		//otherwise find the position where the node before is smaller and the node after is larger than val. Then insert the node with val in there.
		else {
			Node<T> *curr = head;
			Node<T> *nex = head->next;
			while (curr != nullptr && nex != nullptr) {
				if (curr->data < val && nex->data > val) {
					curr->next = x;
					x->next = nex;
					break;
				}
				curr = nex;
				nex = curr->next;
			}
		}
	}
}

#endif