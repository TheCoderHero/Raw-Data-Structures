#ifndef STACK_H
#define STACK_H

#include <cassert>  // debugging checks

namespace custom
{

/************************************************
* STACK
* A class for the stack container
***********************************************/
template <class T>
class stack
{
public:
	// Constructors
	stack(); // Default
	stack(int numCapacity)
		throw (const char *); // Non-Default
	stack(const stack & rhs)
		throw (const char *); // Copy
	stack & operator = (const stack & rhs)
		throw (const char *); // Assignment

	~stack() { delete[] data; }	//Destructor

	// Stack Container Interfaces
	int  capacity()  const { return numCapacity; }
	int  size()      const { return numElements; }
	bool empty()     const;
	void clear();
	void push(const T &t);
	void pop();
	T top() throw (const char*);

private:
	// Private Functions
	void resize(int numCapacity);

	//Private Variables
	T * data = NULL; // pointer to T data type
	int numCapacity; // the current capacity of the stack
	int numElements; // the number of elements in the stack
};

// Member Function Definitions

/********************************************
* STACK : DEFAULT CONSTRUCTOR
*******************************************/
template <class T>
stack <T> ::stack()
{
	numCapacity = 0;
	numElements = 0;
}

/**********************************************
* STACK : NON-DEFAULT CONSTRUCTOR
**********************************************/
template <class T>
stack <T> ::stack(int numCapacity) throw (const char*)
{
	assert(numCapacity >= 0);

	data = new T[numCapacity];
	this->numCapacity = numCapacity;
	numElements = 0;
}

/*******************************************
* STACK :: COPY CONSTRUCTOR
*******************************************/
template <class T>
stack <T> ::stack(const stack <T> & rhs) throw (const char *)
{
	numElements = rhs.numElements;
	numCapacity = rhs.numCapacity;
	data = new T[rhs.numCapacity];
	for (int i = 0; i < numCapacity; i++)
		data[i] = rhs.data[i];
}

/*******************************************
* STACK:: ASSIGNMENT OPERATOR
*******************************************/
template <class T>
stack <T> & stack <T> :: operator = (const stack <T> & rhs)
	throw (const char *)
{
	if (capacity() < rhs.size())
		resize(rhs.size());

	T * newData = new T[rhs.size()];
	for (int i = 0; i < rhs.size(); i++)
		newData[i] = rhs.data[i];
	delete[] data;
	data = newData;
	numElements = rhs.numElements;
	return *this;
}

/********************************************
* STACK : EMPTY
* Return a boolean value for an empty stack
*******************************************/
template <class T>
bool stack <T> ::empty() const
{
	if (numElements == 0)
		return true;
	else
		return false;
}

/********************************************
* STACK : CLEAR
* Set the number of elements to 0
*******************************************/
template <class T>
void stack <T> ::clear()
{
	numElements = 0;
}

/********************************************
* STACK : PUSH
* Add an element to the top of the stack
*******************************************/
template <class T>
void stack <T>::push(const T &t) 
{
	if (capacity() == 0)
		numCapacity++;

	if (size() == capacity())
		resize(capacity() * 2);

	T* newData = new T[numCapacity];
	for (int i = 0; i < numElements; i++)
		newData[i] = data[i];
	newData[numElements++] = t;
	delete[] data;
	data = newData;
}

/********************************************
* STACK :: POP
* Remove the top element of the stack
********************************************/
template <class T>
void stack <T> ::pop()
{
	if (!empty())
	{
		numElements--;
	}
	else
		return;
}

/********************************************
* STACK : TOP
* Return the top element on the stack
*******************************************/
template <class T>
T stack <T> ::top() throw (const char*)
{
	if (!empty())
		return data[size() - 1];
	else
		throw "ERROR: Unable to reference the element from an empty Stack";
}


/********************************************
* STACK : RESIZE
* Increase the size of the capacity
*******************************************/
template <class T>
void stack <T> ::resize(int numCapacity)
{
	this->numCapacity = numCapacity;
}

}; // namespace custom

#endif // stack_H