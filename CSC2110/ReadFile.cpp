#include "ReadFile.h"
#include <iostream>
#include <string>
using namespace CSC2110;

ReadFile::ReadFile(const char* file_name)
{
   input_file = new ifstream();
   input_file->open(file_name);
   closed = false;
   _eof = false;
}

ReadFile::~ReadFile()
{
   close();
   delete input_file;
}

bool ReadFile::eof()
{
   return _eof;
}

void ReadFile::close()
{
   if (!closed)
   {
      input_file->close();
      closed = true;
   }
}

String* ReadFile::readLine()
{
   if (closed) return NULL;
   if (_eof) return NULL;

   string text;
   _eof = !(getline(*input_file, text));

   String* str = new String((const char*) text.c_str());
   return str;
}
