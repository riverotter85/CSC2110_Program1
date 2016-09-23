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
		
		// NOTE: May need to change parameter names to function pointers
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
		
		bool isEmpty();
		int size();
		T* get(String* search_key);
		void add(T* item);
		void remove(String* search_key);
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
		return NULL;
	}
	
	T* item = NULL;
	int index = findRemove(search_key);
	
	if (index != -1)
	{
		item = array[index];
	}
	
	return item;
}

template < class T >
void SortedListArray<T>::add(T* item)
{
	if (item == NULL)
	{
		return;
	}
	
	if (sz == max)
	{
		resize();
	}
	
	int add_index = findAdd(item);
	
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
		return;
	}
	
	if (isEmpty())
	{
		return;
	}
	
	int remove_index = findRemove(search_key);
	delete array[remove_index];
	
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
		int compare = (*compare_items) (array[mid], item);
		
		if (compare > 0)
		{
			hi = mid - 1;
		}
		else if (compare < 0)
		{
			lo = mid + 1;
		}
		else
		{
			return mid;
		}
		
		mid = lo + (hi - lo) / 2;
	}
	
	return mid;
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
	
	for (int i = 0; i < sz; i++)
	{
		new_array[i] = array[i];
	}
	
	delete[] array;
	array = new_array;
	max = new_max;
}

#endif