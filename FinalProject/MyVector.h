#ifndef MYVECTOR_H
#define MYVECTOR_H

#include "AddEntry.h"

template <typename T>
class MyVector
{
    private:

        int size;

        int capacity;

        T* vectorpointer;

    public:

        MyVector(unsigned int capacity = 6);

        //Big Three:

        MyVector(const MyVector &vectorpointer); //Copy constructor

        MyVector& operator=(const MyVector &other); //Assignment operator

        ~MyVector();                                //Destructor

        //Member Access Functions:

        const T operator [](int index) const;   //Returns element at location

        T& operator [](int index);

        T& at(int index);        //Return reference to item at position index

        const T at(int index) const;  //Return a const item at position index

        T& front() const;             //Return item at position 0

        T& back() const;              //Return item at the last position


        //Push and Pop functions:

        MyVector& operator +=(const T& item); //Pushback

        void pushback(const T& item);      //Addentry logic, doubles if
                                           //end is reached

        T popback();                       //Remove last item and return it

        //Insert and Erase:

        void insert(int insert_here, const T& insert_this); //Insert at an
                                                            //position

        void erase(int erase_index);

            //erase item at position
            //- shift left at erase index

        int indexof(const T& item);

           //search for item. retur index.
           // - find item pointer
           // - use counter to count how many items in front of it

        //size and capacity:

        void setsize(int size, const T& value = T());

           //enlarge the vector to this size
           // - assign size
           // - if new size is smaller, shift left, otherwise shift right

        void setcapacity(int capacity);    //allocate this space
           // - assign capacity

        int returnsize() const;


        int returncapacity() const;               //return _capacity
           // - return capacity;

        bool empty() const;                 //return true if vector is empty
            //- return size == 0;

        //OUTPUT:

        template <class U>
        friend ostream& operator <<(ostream& outs,
                                    const MyVector <U> & testobject);

};

template <typename T>
MyVector <T> :: MyVector(unsigned int newcapacity)
{
    capacity = newcapacity;

    size = 0;

    vectorpointer = allocate <T> (capacity);

    initialize <T> (vectorpointer, capacity, T());
}

template <typename T>
MyVector <T> :: MyVector(const MyVector &objectobecopied)
{
    capacity = objectobecopied.capacity;

    size = objectobecopied.size;

    vectorpointer = allocate <T> (capacity);

    copyarray <T> (vectorpointer, objectobecopied.vectorpointer,
                   objectobecopied.size);
}

template <typename T>
MyVector <T> &MyVector <T> :: operator =(const MyVector &objecttobecopied)
{
    if(this == &objecttobecopied)
    {
        return *this;
    }

// NOTE: alternate method of above code bit. Prefer above because it
// is general and applies to other classes as well.

//    if(vectorpointer == firstvectorpointer.vectorpointer)
//    {
//        return *this;
//    }


    //delete unused list

    deallocate <T> (vectorpointer);

    //changes all variables to new one

    capacity = objecttobecopied.capacity;

    size = objecttobecopied.size;

    //allocates new array

    vectorpointer = allocate <T> (capacity);

    //copies contents from old to new

    copyarray <T> (vectorpointer, objecttobecopied.vectorpointer,
                   objecttobecopied.size);

    return *this;
}

template <typename T>
MyVector <T> ::~MyVector()
{
    deallocate <T> (vectorpointer);
}

template <typename T>
const T MyVector <T> :: operator [](int index) const
{
    if(index < 0 || index >= size)
    {
        return T();
    }
    else
    {
        return at(index);
    }
}

template <typename T>
T& MyVector <T> :: operator [](int index)
{
    if(index < 0 || index >= size)
    {
         cout << "\nERROR" << endl;

        return vectorpointer[0];
    }
    else
    {
        return at(index);
    }
}

template <typename T>
T& MyVector <T> :: at(int index)
{
    return vectorpointer[index];
}

template <typename T>
const T MyVector <T> :: at(int index) const
{
    return vectorpointer[index];
}

template <typename T>
T& MyVector <T> :: front() const
{
    return vectorpointer[0];
}

template <typename T>
T& MyVector <T> :: back() const
{
    return vectorpointer[size - 1];
}

template <typename T>
MyVector <T> &MyVector <T> :: operator +=(const T& value)
{
    vectorpointer = addentry <T> (vectorpointer, value, size, capacity);

    return *this;
}

template <typename T>
void MyVector <T> :: pushback(const T& value)
{
    vectorpointer = addentry <T> (vectorpointer, value, size, capacity);
}

template <typename T>
T MyVector <T> :: popback()
{
    T copy = back();

    size--;         //removes last element and returns

    return copy;
}

template <typename T>
void MyVector <T> :: insert(int keylocation, const T& key)
{
    shiftright <T> (vectorpointer, vectorpointer + keylocation, size);

    vectorpointer[keylocation] = key;   //shift right to accomadate for
}                                       //new element

template <typename T>
void MyVector <T> :: erase(int value)
{
    removeentry(vectorpointer, vectorpointer[value], size, capacity);
}

template <typename T>
int MyVector <T> :: indexof(const T& value)
{
    T* result;

    result = find(vectorpointer, value, size);

    T* walker = &vectorpointer[0];

    int counter = 0;

    while(walker != result)
    {
        counter++;

        walker++;
    }

    return counter;
}

//size and capacity:

template <typename T>
void MyVector <T> :: setsize(int asize, const T& value) //allows you to reset
{                                                       //size
    while((asize + size) > capacity)
    {
        //cout << "\n\nDoubling dynamic array size: " << endl;

        capacity *= 2;

        vectorpointer = reallocate(vectorpointer, size, capacity);
    }

    initialize(vectorpointer + size, asize, value);

    size = asize;
}
template <typename T>
void MyVector <T> :: setcapacity(int acapacity)  //sets logic
{
    capacity = acapacity;
}


template <typename T>
int MyVector <T> :: returncapacity() const     //returns / gets
{
    return capacity;
}

template <typename T>
int MyVector <T> ::  returnsize() const
{
    return size;
}


template <typename T>
bool MyVector <T> :: empty() const         //return true if vector is empty
{
    if(size == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <class U>
ostream& operator <<(ostream& outs, const MyVector <U> & testobject)
{
    print(testobject.vectorpointer, testobject.size, outs);

    return outs;
}




#endif // MYVECTOR_H
