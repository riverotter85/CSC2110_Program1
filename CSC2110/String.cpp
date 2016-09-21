#include "Text.h"
using CSC2110::String;

#include <stdlib.h>  //needed for atoi and atof
#include <cstring>   //needed for strlen and strcmp
#include <sstream>
#include <iostream>
using namespace std;

String::String(const char* char_array)
{
   sz = strlen(char_array);
   char* text = new char[sz+1];
   for (int i = 0; i < sz; i++)
   {
      text[i] = char_array[i];
   }
   text[sz] = 0;  //null terminator
   this->text = text;
}

String::~String()
{
   delete[] text;
}

//zero-based
char String::charAt(int index)
{
   if (index < 0 || index >= sz) return -1;
   return text[index];
}

const char* String::getText()
{
   return text;
}

int String::length()
{
   return sz;
}

int String::compare(String* other)
{
   return strcmp(text, other->text);
}

void String::displayString()
{
   cout << text;
}

int String::find(char delimiter, int start)
{
   if (start >= sz || start < 0) return -1;

   int loc = sz;
   for (int i = start; i < sz; i++)
   {
      if (text[i] == delimiter)
      {
         loc = i;
         break;
      }
   }

   return loc;  //delimiter not found
}

//the substring will use the characters from start to end inclusive
String* String::substr(int start, int end)
{
   if (start > end || start < 0) return NULL;
   if (start > sz || end > sz) return NULL;

   int sub_len = end - start + 1;
   char* sub_text = new char[sub_len + 1];

   int count = 0;
   for (int i = start; i <= end; i++)
   {
      sub_text[count] = text[i];
      count++;
   }
   sub_text[count] = 0;

   String* sub = new String((const char*) sub_text);
   return sub;
}

int String::a_to_i()
{
   return atoi(text);
}

float String::a_to_f()
{
   return atof(text);
}

String* String::i_to_a(int number)
{
   stringstream out;
   out << number;
   const char* text = out.str().c_str();
   return new String(text);
}

String* String::f_to_a(float number)
{
   stringstream out;
   out << number;
   const char* text = out.str().c_str();
   return new String(text);
}

