/**
 * @file deque.cpp
 * Implementation of the Deque class.
 *
 */

//deque structure: allows insertion at the right end, and removal at both ends.
//data is stored in a vector, and the 'valid' (not removed) data is between indices n1 and n2
//n2: index of one past the last valid data (which is where to insert the next data)
//n1: index of the first valid data (which is where to remove data from)

/* No argument constructor */
template <class T>
Deque<T>::Deque():n1(0),n2(0){}


/**
 * Adds the parameter object to the right of the Deque.
 *
 * @param newItem object to be added to the Deque.
 */
template <class T>
void Deque<T>::pushR(T newItem)
{
    if(!data.empty()){
        n2++; //empty --> n2 = 0
    }
    data.push_back(newItem);
}

/**
 * Removes the object at the left of the Deque, and returns it to the
 * caller.
 *
 * See .h file for implementation notes. 
 *
 * @return The item that used to be at the left of the Deque.
 */
template <class T>
T Deque<T>::popL()
{
    T item = data[n1]; //remove from left
    n1++;
    int num = n2 - n1 + 1; //calculate the REMAINING number of elements (after removal)
    if(num <= n1){
        //if the block of data will "fit" in the first n1 positions of the vector, resize down by copying the data to a new vector
        vector<T> newData;
        for(int i=n1; i<=n2; i++){
            newData.push_back(data[i]);
        }
        data.clear();
        data = newData;
        n2 = n2 - n1;
        n1 = 0;
    }
    if(n2 < 0) n2 = 0; //if we removed the last element, set it to 0 (no elements --> n2 = 0) {because if we removed the last element, n2 will become -1, we don't want that!}
    return item;
}


/**
 * Removes the object at the right of the Deque, and returns it to the
 * caller.
 *
 * @return The item that used to be at the right of the Deque.
 */
template <class T>
T Deque<T>::popR()
{
    T item = data[n2];
    data.pop_back(); //you need to do this to keep the size of the vector correct for the test cases!!!!
    n2--;
    int num = n2 - n1 + 1;
    if(num <= n1){
        //resize
        vector<T> newData;
        for(int i=n1; i<=n2; i++){
            newData.push_back(data[i]);
        }
        data.clear();
        data = newData;
        n2 = n2 - n1;
        n1 = 0;
    }
    if(n2 < 0) n2 = 0; //if we removed the last element, set it to 0 (no elements --> n2 = 0)
    return item;
}

/**
 * Finds the object at the left of the Deque, and returns it to the
 * caller. Unlike popL(), this operation does not alter the deque.
 *
 * @return The item at the front of the deque.
 */
template <class T>
T Deque<T>::peekL()
{
    T item = data[n1];
    return item;
}



/**
 * Finds the object at the right of the Deque, and returns it to the
 * caller. Unlike popR(), this operation does not alter the deque.
 *
 * @return the value of The item at the right of the deque.
 */
template <class T>
T Deque<T>::peekR()
{
    T item = data[n2];
    return item;
}



/**
 * Determines if the Deque is empty.
 *
 * @return bool which is true if the Deque is empty, false otherwise.
 */
template <class T>
bool Deque<T>::isEmpty() const
{
    return data.size() == 0;
}