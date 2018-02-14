#include <iostream>
#include <math.h>
#include "Lab2.h"
using namespace std;

Matrix::Matrix(int size)
{
	this->size = size;
	matrix = new int *[size];
	for(int i = 0; i < size; i++)
		matrix[i] = new int[size]();
}

Matrix::~Matrix(){
	cout << "\nHelp, I'm being destroyed!\n-matrix Bob" << endl;
	for(int i = 0; i < size; i++)
		delete [] matrix[i];
	delete [] matrix;
	matrix = NULL;
}

int Matrix::get(int row, int column){
	return matrix[row][column];
}

void Matrix::set(int row, int column, int value){
	matrix[row][column] = value;
}

void Matrix::print()
{
	for(int i=0; i<size; i++)
	{
		for(int j = 0; j < size; j++)
			cout << matrix[i][j] << " ";
		cout << "\n";
	}
}

int Matrix::sumHoriz(int row)
{
	int sum = 0;
	for(int i = 0; i < size; i++)
		sum += matrix[row][i];
	return sum;
}

int Matrix::sumVert(int column)
{
	int sum = 0;
	for(int i = 0; i < size; i++)
		sum += matrix[i][column];
	return sum;
}

int Matrix::sumDiag()
{
	int sum = 0;
	for(int i = 0; i < size; i++)
		sum += matrix[i][i];
	return sum;
}

int Matrix::sumDiag2()
{
	int sum = 0;
	for(int i = 0; i < size; i++)
		sum += matrix[size - 1 - i][i];
	return sum;

}

void Matrix::transposeDiag1(Matrix *m){
	for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++)
			matrix[i][j] = (*m).get(j,i);
}

void Matrix::transposeDiag2(Matrix *m){
	for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++)
			matrix[i][j] = (*m).get(size - 1 - j,size - 1 - i);
}

void Matrix::mirrorBottomRight(Matrix *m){
	for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++)
			matrix[i][j] = (*m).get(size - 1 - i,size - 1 - j);
}

void Matrix::checkIt()
{
	if(this->isMagic())
		cout << "\nMAGIC" << endl;
	else
		cout << "\nNONMAGIC" << endl;

	cout << "\n" <<"Checking the sums of every row:      ";
	for(int i = 0; i < size; i++)
		cout << this->sumHoriz(i) << " ";
	cout << "\n" <<"Checking the sums of every column:   ";
	for(int i = 0; i < size; i++)
		cout << this->sumVert(i) << " ";
	cout << "\n" << "Checking the sums of every diagonal: " << this->sumDiag() << " " << this->sumDiag2() << "\n" <<endl;
}

bool Matrix::isMagic()
{
	int sum = size * (ceil(( pow(size,2) + 1 ) / 2));
	int verify = 0;
	for(int y = 0; y < size; y++)
		if((this->sumHoriz(y) == sum) && (this->sumVert(y) == sum) && (this->sumDiag() == sum) && (this->sumDiag2() == sum))
			verify++;
	if(verify == size)
		return true;
	return false;
}

void Matrix::fillWithMagic()
{
	int n = size;
	int numAtPos;
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			numAtPos = n * ((int)((i + 1) + (j + 1) - 1 + floor(n / 2)) % n)  // Formula that creates a number for each position in a magic square of size n
					     + (((i + 1) + (2 * (j + 1)) - 2) % n) + 1;

			matrix[i][j] = numAtPos;
		}
	}
}

int main() {
	bool completed = false;
	while(!completed)
	{
		int size = 0;
		cout << "Enter an odd number size 3 - 15 as the size of the matrix (n X n) : ";
		cin >> size;
		if((size % 2 == 1) && (size > 1) && (size < 16))
		{
			Matrix *m = new Matrix(size);
			Matrix *m2 = new Matrix(size);

			cout << endl;
			m->fillWithMagic(); // 1
			m->print();
			m->checkIt();

			m2->transposeDiag1(m); // 2
			m2->print();
			m2->checkIt();

			m2->transposeDiag2(m);  // 3
			m2->print();
			m2->checkIt();

			m2->mirrorBottomRight(m); // 4
			m2->print();
			m2->checkIt();


			delete m;
			m = NULL;

			delete m2;
			m2 = NULL;


			completed = true;
		}
		else
		{
			cout << "Error! ";
			size = 0;
		}
	}
	return 0;
}











/*void swap(int* ints, int i1, int i2)
{
	int temp = ints[i1];
	ints[i1] = ints[i2];
	ints[i2] = temp;
}*/
/*public Fraction* Fraction::add(Fraction &f)
 * {
 * 	int num = numerator * f.denominator;
 * 	num += f.numerator * denominatior;
 * 	int dnm = f.denominator * denominator;
 * 	return new Fraction(num, dnm);
 * }
 */
//to delete
/*for(int k = 0; k<size; k++)
{
	delete [] a[k];
}

delete [] a;*/

