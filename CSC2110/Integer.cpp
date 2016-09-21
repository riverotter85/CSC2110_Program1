#include "Integer.h"
using CSC2110::Integer;

Integer::Integer(int val)
{
   value = val;
}

Integer::~Integer()
{
}

int Integer::getValue()
{
   return value;
}
