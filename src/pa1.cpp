#include "pa1.h"

#include <iostream>
#include <math.h>
using namespace std;

Matrix::Matrix(int size)
{
	this->size = size;
	matrix = new int *[size];
	for(int i = 0; i < size; i++)
		matrix[i] = new int[size]();
}

Matrix::~Matrix(){
	for(int i = 0; i < size; i++)
		delete [] matrix[i];
	delete [] matrix;
	matrix = NULL;
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

int Matrix::get(int row, int column){
	return matrix[row][column];
}

void Matrix::print()  //Prints the matrix, using printf(), accounts for spacing of numbers with different digits.
{
	for(int i=0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			if(size < 11)
			{
				if(matrix[i][j] < 10)
					printf("  %d ", matrix[i][j]);  //Seriously, it looks convoluted, but it's just to make the format nice.
				else
					printf("  %d", matrix[i][j]);
			}
			else
			{
				if(matrix[i][j] < 10)
					printf("  %d  ", matrix[i][j]);
				else if(matrix[i][j] < 100)
					printf("  %d ", matrix[i][j]);
				else
					printf("  %d", matrix[i][j]);
			}
		}
		cout << "\n";
	}
}

int Matrix::sumHoriz(int row)  //Calculates the sum of a row.
{
	int sum = 0;
	for(int i = 0; i < size; i++)
		sum += matrix[row][i];
	return sum;
}

int Matrix::sumVert(int column)  //Calculates the sum of a column.
{
	int sum = 0;
	for(int i = 0; i < size; i++)
		sum += matrix[i][column];
	return sum;
}

int Matrix::sumDiag1()	//Calculates the sum of the main diagonal;
{						//Diag1 is the main diagonal of the matrix (decreases vertically from left to right).
	int sum = 0;
	for(int i = 0; i < size; i++)
		sum += matrix[i][i];
	return sum;
}

int Matrix::sumDiag2()  //Calculates the sum of the second diagonal;
{						//Diag2 is the diagonal that advances vertically from left to right.
	int sum = 0;
	for(int i = 0; i < size; i++)
		sum += matrix[size - 1 - i][i];
	return sum;
}

void Matrix::transposeDiag1(Matrix *m)								//
{
	for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++)
			matrix[i][j] = (*m).get(j,i);
}																	//Diag1 is the main diagonal of the matrix (decreases vertically from left to right)

void Matrix::transposeDiag2(Matrix *m)
{
	for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++)
			matrix[i][j] = (*m).get(size - 1 - j, size - 1 - i);
}

void Matrix::mirrorBottomRight(Matrix *m)
{
	for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++)
			matrix[i][j] = (*m).get(size - 1 - i, size - 1 - j);
}

void Matrix::flipOverMiddleCol(Matrix *m)
{
	int halfPoint = ceil(size/2);
	for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++)
		{
			int diff = halfPoint - j;
			matrix[i][j] = (*m).get(i, halfPoint + diff);
		}
}

void Matrix::flipOverMiddleRow(Matrix *m)
{
	int halfPoint = ceil(size/2);
	for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++)
		{
			int diff = halfPoint - i;
			matrix[i][j] = (*m).get(halfPoint + diff, j);
		}
}

void Matrix::flipOneColOverMiddle(Matrix *m)
{
	int halfPoint = ceil(size/2);
	for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++)
		{
			int diff = halfPoint - j;
			if(j < halfPoint - 1 || j > halfPoint + 1)
				matrix[i][j] = (*m).get(i,j);
			else
				matrix[i][j] = (*m).get(i,halfPoint + diff);
		}
}

void Matrix::check()
{
	cout << "\n" <<"OUTPUT>> Checking the sums of every row:      ";
	for(int i = 0; i < size; i++)
		cout << this->sumHoriz(i) << " ";

	cout << "\n" <<"OUTPUT>> Checking the sums of every column:   ";
	for(int i = 0; i < size; i++)
		cout << this->sumVert(i) << " ";

	cout << "\n" << "OUTPUT>> Checking the sums of every diagonal: " << this->sumDiag1() << " " << this->sumDiag2() << "\n" << endl;
}

void Matrix::fillWithMagic()
{
	int n = size; int magicNum;

	for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++)
		{
			magicNum = (n * ((int)((i + 1) + (j + 1) - 1 + floor(n / 2)) % n)  // Formula that creates a number for each position in a magic square of size n
					     	 + ( ( (i + 1) + (2 * (j + 1) ) - 2) % n) + 1);    // courtesy of/interpreted from :: https://en.wikipedia.org/wiki/Magic_square

			matrix[i][j] = magicNum;
		}
}

void Matrix::printNum(int num)
{
	cout << "OUTPUT>> Magic Square #" << num << " is: \n" << endl;
}

int main()
{
	bool completed = false;

	while(!completed)
	{
		double size = 0; 									  // Created as a double so that extremely large input won't crash or cause an infinite loop,
		cout << "INPUT>> Enter the size of a magic square: "; // however size is still used as an integer.
		cin >> size;

		if(((int)size % 2 == 1) && (size > 1) && (size < 16)) //If the number is odd and 3-15.
		{
			Matrix *m = new Matrix(size);
			Matrix *m2 = new Matrix(size);		  // Here I create 3 matrices initialized with 0's.
			Matrix *m3 = new Matrix(size);

			cout << endl;

			for(int i = 1; i <= 10; i++)           // Where "i" is the number of the magic square.
			{
				switch(i)
				{
					case 1:
						m->fillWithMagic();        // Create the first magic square, always starts with a 1 at the middle column in the first row
						break;				       // filled using the Siamese Method (See function for more info).
					case 2:
						m2->transposeDiag1(m);     // The second will be the transposition of the first matrix over the first(main) diagonal
						break;					   // NOTE :: I explain the meaning of the first and second diagonal near the function itself.
					case 3:
						m2->transposeDiag2(m);     // The third will be the transposition of the first matrix over the second diagonal.
						break;
					case 4:
						m2->mirrorBottomRight(m);  // The fourth will be the first square mirrored over it's bottom right corner.
						break;
					case 5:
						m2->flipOverMiddleRow(m);  // The fifth will be the first square with positions relative to the middle row swapped.
						break;
					case 6:
						m2->flipOverMiddleCol(m);  // The sixth will be the first square with positions relative to the middle column swapped.
						break;
					case 7:
						m2->transposeDiag1(m);     // The seventh with be the first square transposed over the first(main) diagonal, and then
						m3->flipOverMiddleRow(m2); // the resulting square's positions relative to the middle column will be swapped.
						break;
					case 8:
						m2->transposeDiag2(m);     // The eighth with be the first square transposed over the second diagonal, and then
						m3->flipOverMiddleRow(m2); // the resulting square's positions relative to the middle column will be swapped.
						break;
					case 9:			         	       // A magic square of size 3 only has 8 possible unique permutations,
						m3->flipOneColOverMiddle(m);  // so if the size given is higher, then we finish the last 2 to have a total of 10.
						break;
					case 10:
						m2->transposeDiag1(m);
						m3->flipOneColOverMiddle(m2);
						break;
					}

				m->printNum(i);

				if(i == 1)
				{
					m->print();
					m->check();
				}
				else if(i < 8  && i > 1)
				{
					m2->print();				//This was created to simplify the code for the creation
					m2->check();				//of the squares, I only needed 3 different matrixes for
				}								//the translations: The first printed is m,
				else					      	//then one translation each until the 6th, and then for the
				{								//7th and 8th I needed 2 different translations, so a 3rd
					m3->print();				//matrix was required.
					m3->check();
				}

				if(size == 3 && i == 8)
					break;
			}

			delete m; delete m2; delete m3;
			m = NULL; m2 = NULL; m3 = NULL;

			completed = true;
		}
		else
		{
			cout << "OUTPUT>> Error! Enter an odd number size 3 - 15!" << endl;
			size = 0;
		}
	}
	return 0;
}
