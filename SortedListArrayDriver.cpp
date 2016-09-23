/*
	Filename: SortedListArrayDriver.cpp
	Modified By: Logan Davis
	Last Date Modified: 9/23/2016
*/

#include "SortedListArray.h"
#include "CD.h"
using CSC2110::CD;
#include "ListArray.h"
using CSC2110::ListArray;
#include "ListArrayIterator.h"
using CSC2110::ListArrayIterator;

#include <iostream>
using namespace std;

// My own custom function in order to make testing slightly easier
void addCDs(SortedListArray<CD>* sorted_list, ListArray<CD>* list)
{
	ListArrayIterator<CD>* iter = list->iterator();
	
	while (iter->hasNext())
	{
		sorted_list->add(iter->next());
	}
}

void deleteCDs(ListArray<CD>* list)
{
   ListArrayIterator<CD>* iter = list->iterator();

   while(iter->hasNext())
   {
      CD* cd = iter->next();
      delete cd;
   }
   delete iter;
}

int main()
{
   ListArray<CD>* cds = CD::readCDs("cds.txt");

   //thoroughly test your sorted list here
   SortedListArray<CD>* sorted_cds = new SortedListArray<CD>(&CD::compare_items, &CD::compare_keys);

   // Check for the initial size of sorted_cds, and also if the list is empty
   cout << "The current sorted list size is: " << sorted_cds->size() << endl;
   if (sorted_cds->isEmpty())
   {
	   cout << "The sorted list is empty." << endl;
   }
   
   addCDs(sorted_cds, cds);
   cout << "CDs added to sorted list." << endl;
   
   // Now show the current size after adding the CDs, and verify that the list
   // is not empty
   cout << "\nThe new sorted list size is: " << sorted_cds->size() << endl;
   if (!sorted_cds->isEmpty())
   {
	   cout << "The sorted list is no longer empty.\n" << endl;
   }
   
   ListArrayIterator<CD>* iter = sorted_cds->iterator();
   
   // Display the full contents of sorted_cds
   while (iter->hasNext())
   {
	   CD* cd = iter->next();
	   cd->displayCD();
   }
   delete iter;
   iter = NULL;
   
   cout << "\nReview the basic structure of the CDs listed above." << endl;
   cout << "We're going to be doing some removing." << endl;
   cin.get();
   
   String* song_artist = new String("3 Inches of Blood");
   sorted_cds->remove(song_artist);
   cout << "\nSong from artist " << song_artist << " was removed." << endl;
   delete song_artist;
   song_artist = NULL;
   
   // Now display the modified contents of sorted_cds
   iter = sorted_cds->iterator();
   while (iter->hasNext())
   {
	   CD* cd = iter->next();
	   cd->displayCD();
   }
   cout << "New list size is: " << sorted_cds->size() << "\n\n" << endl;
   delete iter;
   iter = NULL;
   
   // Test for the get method
   song_artist = new String("The Absence");
   CD* item = sorted_cds->get(song_artist);
   delete song_artist;
   song_artist = NULL;
   
   item->displayCD();
   
   song_artist = new String("Toto");
   String* song_title = new String("Africa");
   CD* new_item = new CD(song_artist, song_title, 1982, 10, 1);
   
   // Test adding a new item aside from the CDs beforehand, and see if
   // get works in the same manner
   sorted_cds->add(new_item);
   item = sorted_cds->get(song_artist);
   
   if (item != NULL)
   {
	   cout << "\nItem found in sorted list!" << endl;
	   item->displayCD();
   }
   cout << "Final list size is: " << sorted_cds->size() << endl;
   delete song_title;
   
   sorted_cds->remove(song_artist);
   item = sorted_cds->get(song_artist); // Try and get the removed item in order to test error checking
   delete song_artist;
   song_artist = NULL;
   
   if (item == NULL)
   {
	   cout << "\nToto's Africa is no longer in sorted list. :\(" << endl; // Error checking succeeded!
   }
   else
   {
	   delete new_item;
   }
   
   delete sorted_cds;
   deleteCDs(cds);
   delete cds;
   
   return 0;
}
