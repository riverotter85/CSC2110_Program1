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
   SortedListArray<CD>* sorted_cds = new SortedListArray<CD>(CD::compare_items, CD::compare_keys);

   cout << "The current sorted list size is: " << sorted_cds->size() << endl;
   if (sorted_cds->isEmpty())
   {
	   cout << "The sorted list is empty." << endl;
   }
   
   addCDs(sorted_cds, cds);
   
   cout << "The new sorted list size is: " << sorted_cds->size() << endl;
   if (!sorted_cds->isEmpty())
   {
	   cout << "The sorted list is no longer empty." << endl;
   }
   
   ListArrayIterator<CD>* iter = sorted_cds->iterator();
   
   while (iter->hasNext())
   {
	   CD* cd = iter->next();
	   cd->displayCD();
   }
   delete iter;
   
   /*
   String* song_title = new String("Riders of the Plague");
   CD* item = sorted_cds->get(song_title);
   delete song_title;
   
   item->displayCD();
   */
   
   delete sorted_cds;
   deleteCDs(cds);
   delete cds;

   return 0;
}
