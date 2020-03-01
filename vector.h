#ifndef VECTOR_H
#define VECTOR_H

#include <cassert>

namespace custom
{

/************************************************
 * VECTOR
 * A class for the vector container
 ***********************************************/
template <class T>
class vector
{
public:
   // Constructors
	 vector();  // Default Constructor
	 vector(int numElements)
		 throw (const char *); // Non-Default Constructor
	 vector(const vector & rhs)
		 throw (const char *);  // Copy Constructor
	 vector & operator = (const vector & rhs)
		 throw (const char *);  // Assignment Operator

   //Destructor
   ~vector() { delete[] data; } //Deconstructor
   
   // Vector Container Interfaces
   int  size() const { return numElements; } // Number of elements
   int  capacity() const { return numCapacity; } // Size of the vector
	 bool empty() const; // Boolean for if the vector is empty
	 void clear(); // Set number of elements to 0
	 void push_back(T t); // Add an element to the end of the vector

	// Vector Access
   T & operator [] (int index) 
		 throw (const char*) { return data[index];} // Read/Write
   T   operator [] (int index) 
     const throw (const char *) { return data[index];} // Read Only
   
  // Vector Iterators
   class iterator;
   iterator begin() { return iterator (data); }
	 iterator end()   { return iterator (data + numElements); }
   
private:
	//Private Methods
	 void resize(int numCapacity);	// resize the vector

	//Private Variables
	T * data = NULL; // pointer to T data type
	int numElements; // number of elements in the vector
	int numCapacity; // the current capacity of the vector
};

/**************************************************
 * VECTOR ITERATOR
 * A class for the vector iterator
 *************************************************/
template <class T>
class vector <T> :: iterator
{
public:
   // constructors, destructors, and assignment operator
   iterator()      : p(NULL)      {              }
   iterator(T * p) : p(p)         {              }
   iterator(const iterator & rhs) { *this = rhs; }
   iterator & operator = (const iterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // equals, not equals operator
   bool operator != (const iterator & rhs) const { return rhs.p != this->p; }
   bool operator == (const iterator & rhs) const { return rhs.p == this->p; }

   // dereference operator
         T & operator * ()       { return *p; }
   const T & operator * () const { return *p; }

   // prefix increment
   iterator & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   iterator operator ++ (int postfix)
   {
      iterator tmp(*this);
      p++;
      return tmp;
   }
   
private:
   T * p;
};

// Member Function Definitions

/********************************************
* VECTOR : DEFAULT CONSTRUCTOR
*******************************************/
template <class T>
vector <T> ::vector()
{
	numElements = 0;
	numCapacity = 0;
}

/**********************************************
 * VECTOR : NON-DEFAULT CONSTRUCTOR
 * Create a vector with "capacity"
 **********************************************/
template <class T>
vector <T> :: vector(int numElements) throw (const char*)
{
	assert(numElements >= 0);
	data = new T[numElements];
	for (int i = 0; i < numElements; i++)
		data[i] = 0;
	numCapacity = numElements;
	this->numElements = numElements;
}

/*******************************************
* VECTOR :: COPY CONSTRUCTOR
*******************************************/
template <class T>
vector <T> ::vector(const vector <T> & rhs) throw (const char *)
{
	assert(rhs.numElements >= 0);

	numElements = rhs.numElements;
	numCapacity = rhs.numCapacity;
	data = new T[numElements];

	for (int i = 0; i < numElements; i++)
		data[i] = rhs.data[i];
}

/*******************************************
* VECTOR :: ASSIGNMENT OPERATOR
*******************************************/
template <class T>
vector <T> & vector <T> :: operator = (const vector <T> & rhs)
throw (const char *)
{
	assert(rhs.numElements >= 0);
 
  numElements = rhs.numElements;
	numCapacity = rhs.numCapacity;
	T * newData = new T[rhs.numCapacity];
	for (int i = 0; i < numCapacity; i++)
		newData[i] = rhs.data[i];
	delete[] data;
	this->data = newData;
	this->numCapacity = rhs.numCapacity;
	this->numElements = rhs.numElements;
	return *this;

}

/********************************************
* VECTOR : EMPTY
* Return a boolean value for an empty vector
*******************************************/
template <class T>
bool vector <T> :: empty() const
{
	if (numElements == 0)
		return true;
	else
		return false;
}

/********************************************
* VECTOR : CLEAR
* Set the number of elements to 0
*******************************************/
template <class T>
void vector <T> :: clear()
{
	numElements = 0;
}

/********************************************
* VECTOR : PUSH_BACK
* Add another element to the vector
*******************************************/
template <class T>
void vector <T>::push_back(T t)
{
	assert(numElements >= 0);

	if (numCapacity == 0)
		numCapacity++;

	if (numElements == numCapacity)
		resize(capacity() * 2);

	T* newData = new T[numElements + 1];
	for (int i = 0; i < numElements; i++)
		newData[i] = data[i];
	newData[numElements] = t;
	delete[] data;
	data = newData;
	numElements += 1;

}

/********************************************
* VECTOR :: RESIZE
* Resize the vector to capacity specified
********************************************/
template <class T>
void vector <T> ::resize(int numCapacity)
{
	this->numCapacity = numCapacity;
}

}; // namespace custom

#endif // vector_H