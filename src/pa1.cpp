#include "pa1.h"
#include <iostream>
#include <math.h>
using namespace std;

Matrix::Matrix(int size)
{
	this->size = size;
	matrix = new int *[size];
	for(int i = 0; i < size; i++)		// This creates the matrix on the heap (using pointers), initialized with
		matrix[i] = new int[size]();	// 0s in every position, thanks to the "matrix[i] = new int[size]();"
}										// built in initializer.

Matrix::~Matrix(){
	for(int i = 0; i < size; i++)		// Default destructor, allows the delete keyword to be used in the correct way in main;
		delete [] matrix[i];			// deletes all the child matrices before deleting the parent that holds all matrices
	delete [] matrix;					// to avoid memory leak.
	matrix = NULL;
}

bool Matrix::isMagic()
{
	int sum = size * (ceil(( pow(size,2) + 1 ) / 2)); // Sum formula for a magic square based on its size.
	int verify = 0;  								  // Arbitrary integer made to check if every row and column satisfies.

	for(int y = 0; y < size; y++)
		if((this->sumRow(y) == sum) && (this->sumColumn(y) == sum) &&
		   (this->sumDiag1() == sum) && (this->sumDiag2() == sum))    // Checks all sums for each position, if they are all correct, add 1 to the integer.
			verify++;

	if(verify == size)
		return true;   						  // If the integer is equal to size, all are satisfied. Therefore, the matrix is magic.
	return false;
}

int Matrix::get(int row, int column){
	return matrix[row][column];			// Simple function just gets the value at a position.
}

void Matrix::print()  // Prints the matrix, using printf(), accounts for spacing of numbers with different digits.
{
	for(int i=0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			if(size < 11)
			{
				if(matrix[i][j] < 10)
					printf("  %d ", matrix[i][j]);  // Seriously, it looks convoluted, but it's just to make the format nice.
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

int Matrix::sumRow(int row)  // Calculates the sum of a row.
{
	int sum = 0;
	for(int i = 0; i < size; i++)
		sum += matrix[row][i];
	return sum;
}

int Matrix::sumColumn(int column)  // Calculates the sum of a column.
{
	int sum = 0;
	for(int i = 0; i < size; i++)
		sum += matrix[i][column];
	return sum;
}

int Matrix::sumDiag1()	// Calculates the sum of the main diagonal;
{						// Diag1 is the main diagonal of the matrix (decreases vertically from left to right).
	int sum = 0;
	for(int i = 0; i < size; i++)
		sum += matrix[i][i];
	return sum;
}

int Matrix::sumDiag2()  // Calculates the sum of the second diagonal;
{						// Diag2 is the diagonal that advances vertically from left to right.
	int sum = 0;
	for(int i = 0; i < size; i++)
		sum += matrix[size - 1 - i][i];
	return sum;
}

void Matrix::transposeDiag1(Matrix *m)		// Simple transposition of a matrix: Takes in a matrix pointer,
{											// dereferences it, and sets the resultant matrix's row and column
	for(int i = 0; i < size; i++)			// equal to the first matrix's column and row; and it correctly swaps over the diagonal.
		for(int j = 0; j < size; j++)
			matrix[i][j] = (*m).get(j,i);
}

void Matrix::transposeDiag2(Matrix *m)
{
	int rightEdge = size - 1;				// Same as above, but sets the resultant matrix's row and column
	for(int i = 0; i < size; i++)			// equal to to the first matrix's column and row relative to the
		for(int j = 0; j < size; j++)		// end of the square, not the beginning. (matrix[rightEdge][rightEdge] is the bottom right).
			matrix[i][j] = (*m).get(rightEdge - j, rightEdge - i);   // So, it swaps over the second diagonal.
}

void Matrix::mirrorBottomRight(Matrix *m)
{
	int rightEdge = size - 1;				// This is similar to the transposeDiag2(), however, doesn't swap the values (i,j) to (j,i),
	for(int i = 0; i < size; i++)			// it only sets them to the values "flipped" over the bottom right.
		for(int j = 0; j < size; j++)
			matrix[i][j] = (*m).get(rightEdge - i, rightEdge - j);
}

void Matrix::flipOverMiddleCol(Matrix *m)
{
	int halfPoint = ceil(size/2);			// This function sets each column equal to the other matrix's column swapped
	for(int i = 0; i < size; i++)			// relative to the the middle column. The distance, or "difference" from the middle
		for(int j = 0; j < size; j++)		// of the matrix to the column is then used to set the opposite column's values.
		{									// The (halfPoint + diff) will always be the column opposite relative to the middle.
			int diff = halfPoint - j;
			matrix[i][j] = (*m).get(i, halfPoint + diff);
		}
}

void Matrix::flipOverMiddleRow(Matrix *m)
{
	int halfPoint = ceil(size/2);			// Exact same function as flipOverMiddleCol(), just written in terms of i,
	for(int i = 0; i < size; i++)			// or rows, so that the flipping will occur over the middle row.
		for(int j = 0; j < size; j++)
		{
			int diff = halfPoint - i;
			matrix[i][j] = (*m).get(halfPoint + diff, j);
		}
}

void Matrix::flipOneColOverMiddle(Matrix *m)
{
	int halfPoint = ceil(size/2);
	for(int i = 0; i < size; i++)			// This is the flipOverMiddleCol() function rewritten so that
		for(int j = 0; j < size; j++)		// only the 2 columns closest to the middle columns will be swapped.
		{									// Everything else will remain constant.
			int diff = halfPoint - j;
			if(j < halfPoint - 1 || j > halfPoint + 1)
				matrix[i][j] = (*m).get(i,j);
			else
				matrix[i][j] = (*m).get(i,halfPoint + diff);
		}
}

void Matrix::check()	// Prints the checking of every row, column, and diagonal. Loops required only for the rows and columns.
{
	cout << "\n" << "OUTPUT>> Checking the sums of every row:      ";
	for(int i = 0; i < size; i++)
		cout << this->sumRow(i) << " ";

	cout << "\n" << "OUTPUT>> Checking the sums of every column:   ";
	for(int i = 0; i < size; i++)
		cout << this->sumColumn(i) << " ";

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

			matrix[i][j] = magicNum;  // I know it's long, but it works! I set the value here equal to every position.
		}
}

void Matrix::printNum(int num)    // Simplifies the printing of the number of the square.
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

		if(((int)size % 2 == 1) && (size > 1) && (size < 16)) // If the number is odd and 3-15.
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
						m2->transposeDiag1(m);     // The second will be the transposition of the first matrix over the first(main) diagonal.
						break;
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
					case 9:
						m3->flipOneColOverMiddle(m); // The ninth will use the logic that, For size > 3, we can flip the columns
						break;						 // just before and just after the middle keeping everything else constant.
					case 10:
						m2->transposeDiag1(m);		  // Doing the same as for the ninth, the tenth will just be transposed
						m3->flipOneColOverMiddle(m2); // before flipping.
						break;
					}

				m->printNum(i);

				if(i == 1)
				{
					m->print();
					m->check();
				}
				else if(i < 8 && i > 1)
				{
					m2->print();				// This if block was created to simplify the code for the creation
					m2->check();				// of the squares, I only needed 3 different matrixes for
				}								// the translations: The first printed is m,
				else					      	// then one translation each until the 6th, and then for the
				{								// 7th and 8th I needed 2 different translations, so a 3rd
					m3->print();				// matrix was required.
					m3->check();
				}

				if(size == 3 && i == 8)      // A magic square of size 3 only has 8 possible unique permutations,
					break;					 // so if the size given is higher, then we finish the last 2 to have a total of 10.
			}

			delete m; delete m2; delete m3;	// Deletes all of the matrices created,
			m = NULL; m2 = NULL; m3 = NULL; // sets them to NULL to reallocate the memory.

			completed = true; // Ends the loop, terminating the program.
		}
		else
		{
			cout << "OUTPUT>> Error! Enter an odd number size 3 - 15!" << endl; // Simple error given if the number is wrong.
		}
	}
	return 0;
}
