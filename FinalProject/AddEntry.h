#ifndef ADDENTRY_H
#define ADDENTRY_H

#include <iostream>

using namespace std;

template <typename T>
T *allocate(int capacity)
{
    const bool debug = false;

    if (debug)
    {
        cout << "allocate: capacity: " << capacity << endl;
    }
    return new T[capacity];
}

template <typename T>
void copyarray(T *destination, T *source, int size)
{
    for (T *end = source + size; source < end; source++, destination++)
    {
        *destination = *source;
    }
}

template <typename T>
void deallocate(T *array)
{
    delete[] array;
}

template <typename T>
T &get(T *array, int column)
{
    return array[column];
}

template <typename T>
void write(T *array, T value, int column)
{
    for (int j = 0; j < column; j++)
    {
        array++;
    }

    *array = value;
}

template <typename T>
T read(T *array, int column)
{
    for (int j = 0; j < column; j++)
    {
        array++;
    }
    return *array;
}

template <typename T>
ostream &print(T *currentrow, int rowsize, ostream &outs = cout)
{
    for (int columnindex = 0; columnindex < rowsize; columnindex++)
    {
        outs << currentrow[columnindex] << ' ';
    }
    return outs;
}

template <typename T>
void initialize(T *array, int size, T value)
{
    for (int i = 0; i < size; i++)
    {
        write <T> (array, value, i);
    }
    //print(array, size);
}

template <typename T>
T *find(T *walkerposition, T key, int size)
{
    for (int i = 0; i < size; i++)
        // caps at max size of array.
    {
        if (*walkerposition == key)
            // if VALUE of walker is same as the VALUE of key
        {
            return walkerposition;
            // returns position of walker.
        }

        else
        {
            walkerposition++;
            // moves walker position forward
        }
    }
    return nullptr;
}

template <typename T>
T *reallocate(T *list, int size, int capacity)
{
  T *newdynamicarray;

  newdynamicarray = allocate <T> (capacity);

  copyarray(newdynamicarray, list, size);

  initialize <T> (newdynamicarray + size, capacity - size, T());

  delete[] list;

  //cout << "\nNEW ALLOCATED ARRAY: ";

  //print(newdynamicarray, capacity);

  return newdynamicarray;
}

template <typename T>
T* addentry(T* list, const T& newentry, int& size, int& capacity)
{
    if(size == capacity)
    {
        //cout << "\n\nDoubling dynamic array size: " << endl;

        capacity *= 2;

        list = reallocate(list, size, capacity);
    }

    T* walker;

    walker = list;

    walker += size;

    // walker created to point at list, then end of list

    *walker = newentry;

    size++;

        //print(list, size);

    return list;
}

template <typename T>
void shiftleft(T* walkerposition, T* keyposition, int& size)
{
    T* end = &walkerposition[size - 1];

    T* copyposition = keyposition;

    while(keyposition < end)
    {
        copyposition += 1;

        *keyposition = *copyposition;

        keyposition++;
    }
    size--;
}

template <typename T>
void shiftright(T* walkerposition, T* keyposition, int& size)
{
    T* end = &walkerposition[size]; //set to end + 1

    T* copyposition = &walkerposition[size - 1];    //sets copy to end of
                                                    //last interesting element
    while(copyposition >= keyposition)
    {                                               //while copy isn't at
        *end = *copyposition;                       //key, shifts everything
                                                    //to the right by one
        copyposition--;
                                                    //decrease by 1
        end--;
    }
    size++;
}

template <typename T>
T* removeentry(T* list, const T& deleteme, int& size, int& capacity)
{

    double compare = 1/4.0;

    double check = 0;

    check = (size + 0.0)/capacity;

    T* result;

    T* key;

    key = list;

    //key pointer created, pointed at array to store the delete me variable

    if(compare >= check)
    {
        //cout << "\nShrinking dynamic array by half: " << endl;

        capacity /= 2;

        list = reallocate(list, size, capacity);
    }

    result = find <T> (list, deleteme, size);

    shiftleft(list, result, size);

    return list;
}

#endif // ADDENTRY_H
