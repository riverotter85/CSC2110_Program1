#include "Keyboard.h"
using CSC2110::Keyboard;
#include <iostream>

Keyboard::Keyboard()
{
}

Keyboard::~Keyboard()
{
}

Keyboard* Keyboard::getKeyboard()
{
   static Keyboard keyboard;  //initialized when method is called the first time
   return &keyboard;  //won't go out of scope as keyboard is static
}

int Keyboard::readInt(string prompt)
{
   cout << prompt;
   int val = 0;
   cin >> val;
   return val;
}

int Keyboard::getValidatedInt(string prompt, int min, int max)
{
   int validated = readInt(prompt);
   cout << validated << endl;

   while(validated < min || validated > max)
   {
      validated = readInt(prompt);
      cout << validated << endl;
   }

   return validated;
}

double Keyboard::readDouble(string prompt)
{
   cout << prompt;
   double val = 0;
   cin >> val;
   return val;
}

double Keyboard::getValidatedDouble(string prompt, double min, double max)
{
   double validated = readDouble(prompt);
   cout << validated << endl;

   while(validated < min || validated > max)
   {
      validated = readDouble(prompt);
      cout << validated << endl;
   }

   return validated;
}

String* Keyboard::readString(string prompt)
{
   cout << prompt;
   string text;
   getline(cin, text);

   String* str = new String(text.c_str());
   return str;
}
