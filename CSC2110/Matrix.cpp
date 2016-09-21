#include "Matrix.h"
using CSC2110::Matrix;

#include <fstream>
#include <iostream>
using namespace std;

int Matrix::getNumRows()
{
   return rows;
}

int Matrix::getNumCols()
{
   return cols;
}

//the indices are 1-based!!
Matrix::Matrix(int r, int c)
{
   rows = r;
   cols = c;

   if (r < 1)
   {
      rows = 1;
   }

   if (c < 1)
   {
      cols = 1;
   }

   int num_elements = rows*cols;
   mat = new double[rows*cols];

   //initialize the matrix to contain all zeroes (might not be square in general)
   int count = 0;
   for (int i = 1; i <= rows; i++)
   {
      for (int j = 1; j <= cols; j++)
      {
         mat[count] = 0.0;
         count++;
      }
   }
}

Matrix::~Matrix()
{
   delete[] mat;
}

void Matrix::setElement(int row, int col, double val)
{
   int index = (row - 1) * cols + col - 1;
   mat[index] = val;
}

double Matrix::getElement(int row, int col)
{
   int index = (row - 1) * cols + col - 1;
   return mat[index];
}

void Matrix::displayMatrix()
{
   for (int i = 1; i <= rows; i++)
   {
      for (int j = 1; j <= cols; j++)
      {
         cout << this->getElement(i, j) << "   ";
      }
      cout << endl;
   }
   cout << endl;
}

Matrix* Matrix::add(Matrix* other)
{
   int rows1 = rows;
   int cols1 = cols;

   int rows2 = other->rows;  //getNumRows()
   int cols2 = other->cols;  //getNumCols()

   if (cols1 != rows1 || cols2 != rows2)
   {
      cout << "Cannot add matrices." << endl;
      return NULL;
   }

   Matrix* result = new Matrix(rows1, cols1);

   int rows = rows1;
   int cols = cols1;

   //loop over all elements of resulting matrix
   for (int i = 1; i <= rows; i++)
   {
      for (int j = 1; j <= cols; j++)
      {
         double x = this->getElement(i, j) + other->getElement(i, j);
         result->setElement(i, j, x);
      }
   }

   return result;
}

Matrix* Matrix::multiply(Matrix* other)
{
   int rows1 = rows;
   int cols1 = cols;

   int rows2 = other->rows;
   int cols2 = other->cols;

   if (cols1 != rows2)
   {
      cout << "Cannot multiply matrices." << endl;
      return NULL;
   }

   Matrix* result = new Matrix(rows1, cols2);

   int rows = rows1;
   int cols = cols2;

   double x;

   //loop over all elements of resulting matrix
   for (int i = 1; i <= rows; i++)
   {
      for (int j = 1; j <= cols; j++)
      {
         x = 0;
         //sum up multiplying matrices to obtain value placed in new matrix
         for (int k = 1; k <= cols1; k++)
         {
            x = x + this->getElement(i, k) * other->getElement(k, j);
         }
         result->setElement(i, j, x);
      }
   }

   return result;
}

//assumes a specific format for the file
Matrix* Matrix::readMatrix(const char* file_name)
{
   ifstream matrix_file;
   matrix_file.open(file_name);

   int rows = 1;
   int cols = 1;

   matrix_file >> rows >> cols;

   if (rows < 1)
   {
      rows = 1;
   }

   if (cols < 1)
   {
      cols = 1;
   }

   Matrix* matrix = new Matrix(rows, cols);

   for (int i = 1; i <= rows; i++)
   {
      for (int j = 1; j <= cols; j++)
      {
         double val = 0.0;
         matrix_file >> val;
         matrix->setElement(i, j, val);
      }
   }

   matrix_file.close();

   return matrix;
}

//assumes a specific format for the file
void Matrix::writeMatrix(const char* file_name)
{
   ofstream matrix_file;
   matrix_file.open(file_name);

   matrix_file << rows << " " << cols << endl;

   for (int i = 1; i <= rows; i++)
   {
      for (int j = 1; j <= cols; j++)
      {
         matrix_file << this->getElement(i, j) << " ";
      }
      matrix_file << endl;
   }

   matrix_file.close();
}
