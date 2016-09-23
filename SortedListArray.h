/*
	Filename: SortedListArray.h
	Written and Modified By: Logan Davis
	Last Date Modified: 9/23/2016
*/

#if !defined _SORTEDLISTARRAY_H
#define _SORTEDLISTARRAY_H

#include "Text.h"
#include "ListArrayIterator.h"
using CSC2110::String;
using CSC2110::ListArrayIterator;

template < class T >
class SortedListArray
{
	private:
		T** array;
		int sz;
		int max;
		
		// Pointers to static methods of type T
		int (*compare_items) (T* item_1, T* item_2);
		int (*compare_keys) (String* search_key, T* item);
		
		// Private methods
		int findAdd(T* item);
		int findRemove(String* search_key);
		void resize();
	
	public:
		SortedListArray(int (*comp_items) (T* item_1, T* item_2),
						int (*comp_keys) (String* search_key, T* item));
		~SortedListArray();
		
		//pre: N/A.
		//post: If the sorted list is empty, returns TRUE. Returns FALSE otherwise.
		bool isEmpty();
		
		//pre: N/A.
		//post: Returns the current number of items stored in the sorted list.
		int size();
		
		//pre: search_key has to be a song artist that is already stored within the sorted list.
		//	   The list must not be empty.
		//post: Retrieves an item of the artist specified by search_key or NULL if the item was not found.
		T* get(String* search_key);
		
		//pre: item has a non-NULL value. Otherwise, add exits early.
		//	   If the sorted list is currently full, then it is resized to make room for the item.
		//post: The item is sorted and placed within the index alphabetically by artist.
		void add(T* item);
		
		//pre: search_key has to be a song artist that is already stored within the sorted list.
		//	   If the list is empty or the artist isn't found, remove exits early.
		//post: The item found by search_key is removed from the sorted list. (Data is not deleted!)
		void remove(String* search_key);
		
		//pre: N/A.
		//post: Creates and returns an iterator derived from the sorted list in its current state.
		ListArrayIterator<T>* iterator();
};

template < class T >
SortedListArray<T>::SortedListArray(int (*comp_items) (T* item_1, T* item_2),
									int (*comp_keys) (String* search_key, T* item))
{
	sz = 0;
	max = 2;
	
	// Initialize function pointers
	compare_items = comp_items;
	compare_keys = comp_keys;
	
	array = new T*[max];
	for (int i = 0; i < max; i++)
	{
		array[i] = NULL;
	}
}

template < class T >
SortedListArray<T>::~SortedListArray()
{
	delete[] array;
}

template < class T >
bool SortedListArray<T>::isEmpty()
{
	return (sz == 0);
}

template < class T >
int SortedListArray<T>::size()
{
	return sz;
}

template < class T >
T* SortedListArray<T>::get(String* search_key)
{
	if (search_key == NULL)
	{
		return NULL; // Nothing to search
	}
	
	T* item = NULL;
	int index = findRemove(search_key); // Find the index for the item to be returned
	
	if (index != -1)
	{
		item = array[index]; // Item was found!
	}
	
	return item;
}

template < class T >
void SortedListArray<T>::add(T* item)
{
	if (item == NULL)
	{
		return; // Nothing to add
	}
	
	if (sz == max)
	{
		resize(); // Add space for new item
	}
	
	// Find the index to where the item will be added
	int add_index = findAdd(item);
	
	// Shift every item >= add_index forward one place,
	// and add the item in the empty index
	for (int i = sz; i > add_index; i--)
	{
		array[i] = array[i - 1];
	}
	array[add_index] = item;
	
	sz++;
}

template < class T >
void SortedListArray<T>::remove(String* search_key)
{
	if (search_key == NULL)
	{
		return; // Nothing to search
	}
	
	if (isEmpty())
	{
		return; // Nothing to remove
	}
	
	// Find the index for the item to remove
	int remove_index = findRemove(search_key);
	
	if (remove_index == -1)
	{
		return; // Item was not found in list
	}
	
	// move every item > remove_index back one, and set the item at
	// the current size back to its default value of NULL
	for (int i = remove_index; i < (sz - 1); i++)
	{
		array[i] = array[i + 1];
	}
	array[sz - 1] = NULL;
	
	sz--;
}

template < class T >
ListArrayIterator<T>* SortedListArray<T>::iterator()
{
	ListArrayIterator<T>* iter = new ListArrayIterator<T>(array, sz);
	return iter;
}

template < class T >
int SortedListArray<T>::findAdd(T* item)
{
	int lo = 0;
	int hi = sz - 1;
	int mid = lo + (hi - lo) / 2;
	
	while (lo <= hi)
	{		
		int compare = (*compare_items) (item, array[mid]);
		
		if (compare < 0)
		{
			hi = mid - 1;
		}
		else if (compare > 0)
		{
			lo = mid + 1;
		}
		else
		{
			return mid; // If the same item was found in the list, return that index
		}
		
		mid = lo + (hi - lo) / 2;
	}
	
	return mid; // Otherwise, return the closest index to the desired value
}

template < class T >
int SortedListArray<T>::findRemove(String* search_key)
{
	int lo = 0;
	int hi = sz - 1;
	int mid = lo + (hi - lo) / 2;
	
	while (lo <= hi)
	{		
		int compare = (*compare_keys) (search_key, array[mid]);
		
		if (compare < 0)
		{
			hi = mid - 1;
		}
		else if (compare > 0)
		{
			lo = mid + 1;
		}
		else
		{
			return mid; // Item was found, return index
		}
		
		mid = lo + (hi - lo) / 2;
	}
	
	return -1; // Item was not found
}

template < class T >
void SortedListArray<T>::resize()
{
	int new_max = max * 2;
	T** new_array = new T*[new_max];
	
	for (int i = 0; i < new_max; i++)
	{
		new_array[i] = NULL;
	}
	
	// Copy the current sorted list contents into the resized array
	for (int i = 0; i < sz; i++)
	{
		new_array[i] = array[i];
	}
	
	delete[] array;
	array = new_array;
	max = new_max;
}

#endif