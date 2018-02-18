#ifndef PA1_H_
#define PA1_H_

class Matrix{
	private:
		int size;
		int ** matrix;  //array that contains references to other arrays
	public:
		Matrix(int size);
		~Matrix();

		bool isMagic();

		void print();
		void transposeDiag1(Matrix *m);
		void transposeDiag2(Matrix *m);
		void mirrorBottomRight(Matrix *m);
		void flipOverMiddleCol(Matrix *m);
		void flipOneColOverMiddle(Matrix *m);
		void flipOverMiddleRow(Matrix *m);
		void fillWithMagic();
		void check();
		void printNum(int num);

		int get(int row, int column);
		int sumHoriz(int row);
		int sumVert(int column);
		int sumDiag1();
		int sumDiag2();
	};

#endif /* PA1_H_ */
