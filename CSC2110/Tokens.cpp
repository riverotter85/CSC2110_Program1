#include "Tokens.h"

#if !defined NULL
   #define NULL 0
#endif

#include <iostream>
using namespace std;
using namespace CSC2110;

Tokens::Tokens(String* str, char delimiter)
{
   max_tokens = 1;
   sz = 0;

   tokens = new String*[max_tokens];
   for (int i = 0; i < max_tokens; i++)
   {
      tokens[i] = NULL;
   }

   int str_len = str->length();
   int current_loc = 0;

   int count = 0;
   while(current_loc < str_len)
   {
      int next_loc = str->find(delimiter, current_loc);

      if (next_loc > 0)  //a delimiter as the first character is a problem
      {
         String* token = str->substr(current_loc, next_loc - 1);
         addToken(token);
         count++;
      }
      current_loc = next_loc + 1;
   }
}

Tokens::~Tokens()
{
   delete[] tokens;
}

int Tokens::getNumTokens()
{
   return sz;
}

void Tokens::displayTokens()
{
   int num_tokens = sz;
   String** strings = tokens;

   for (int i = 0; i < num_tokens; i++)
   {
      String* str = strings[i];
      str->displayString();
      cout << endl;
   }
}

void Tokens::resize()
{
   String** resize_strings = new String*[2*max_tokens];
   for (int i = 0; i < sz; i++)
   {
      resize_strings[i] = tokens[i];
   }

   for (int i = sz; i < 2*sz; i++)
   {
      resize_strings[i] = NULL;
   }

   delete[] tokens;
   tokens = resize_strings;
   max_tokens = 2*max_tokens;
}

void Tokens::addToken(String* str)
{
   if (sz == max_tokens)
   {
      resize();
   }

   tokens[sz] = str;
   sz++;
}

String* Tokens::getToken(int index)
{
   if (index < 0 && index >= sz) return NULL;
   return tokens[index];
}
