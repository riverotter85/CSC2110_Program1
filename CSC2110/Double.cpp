#include "Double.h"
using CSC2110::Double;

Double::Double(double val)
{
   value = val;
}

Double::~Double()
{
}

double Double::getValue()
{
   return value;
}
