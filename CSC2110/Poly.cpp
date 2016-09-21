#include "Poly.h"
#include "ReadFile.h"
#include "WriteFile.h"

#include <math.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

using namespace CSC2110;

Poly::Poly(int m_p)  
{
   max_power = 3;
   if (m_p >= 0)
   {
      max_power = m_p;
   }

   coeffs = new double[max_power + 1];  //array of doubles

   for (int i = 0; i <= max_power; i++)
   {
      coeffs[i] = 0.0;
   }

   degree = 0;
   max_power = max_power;
}

Poly::~Poly()
{
   delete[] coeffs; 
}

int Poly::getDegree()
{
   return degree;
}

double Poly::getCoeff(int power)
{
   if (power > max_power || power < 0) return 0;

   return coeffs[power];
}

void Poly::setCoeff(int power, double cf)
{
   if (power > max_power || power < 0) return;

   coeffs[power] = cf;

   if (power >= degree)
   {
      degree = power;
   }
}

double Poly::evaluate(double x)
{
   double result = getCoeff(degree);
   
   for (int i = degree - 1; i >= 0; i--)
   {
      result = result * x;
      result = result + getCoeff(i);
   }

   return result;
}

Poly* Poly::multiply(Poly* other)
{
   double TOL = .00001;

   int n = getDegree();
   int m = other->getDegree();

   Poly* temp = new Poly(n + m);

   for (int i = 0; i <= n; i++) //loop over coeffs
   {
      for (int j = 0; j <= m; j++)  //loop over second coeffs
      {
         double coeff_i = getCoeff(i);
         double coeff_j = other->getCoeff(j);
         if (fabs(coeff_i) > TOL && fabs(coeff_j) > TOL)
         {
            int power = i + j;
            double coeff = temp->getCoeff(power);
            temp->setCoeff(power, coeff + (coeff_i * coeff_j));
         }
      }
   }

   return temp;
}

void Poly::displayPoly()
{
   double TOL = .00001;
   int degree = getDegree();

   cout << getCoeff(degree) << "x^" << degree;
   for (int i = degree - 1; i >= 0; i--)
   {
      double coeff = getCoeff(i);
      if (fabs(coeff) > TOL)
      {
         cout << " + " << coeff << "x^" << i << " ";
      }
   }
   cout << endl;
}

//assumes a specific format for the file
//why is this method static in the header file?
Poly* Poly::readPoly(const char* file_name)
{
   ReadFile* rf = new ReadFile(file_name); //for reading
   String* degree_str = rf->readLine();
   int degree = degree_str->a_to_i();
   delete degree_str;

   Poly* poly = new Poly(degree);
   
   for (int i = 0; i <= degree; i++)
   {
      String* coeff_str = rf->readLine();
      float coeff = coeff_str->a_to_f();
      delete coeff_str;

      poly->setCoeff(i, (double) coeff);
   }

   delete rf;
   return poly;
}

//assumes a specific format for the file
void Poly::writePoly(const char* file_name)
{
   WriteFile wf(file_name); //for writing

   String* degree_str = String::f_to_a(degree);
   wf.writeLine(degree_str);
   delete degree_str;

   for (int i = 0; i <= degree; i++)
   {
      float coeff = (float) getCoeff(i);
      String* coeff_str = String::f_to_a(coeff);

      wf.writeLine(coeff_str);
      delete coeff_str;
   }
}
