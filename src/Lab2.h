#ifndef LAB2_H_
#define LAB2_H_

class Matrix{
	private:
		int size;
		int ** matrix;  //array that contains references to other arrays
	public:

		Matrix(int size);
		~Matrix();
		bool isMagic();
		int get(int row, int column);
		void set(int row, int column, int value);
		void print();
		void transposeDiag1(Matrix *m);
		void transposeDiag2(Matrix *m);
		void mirrorBottomRight(Matrix *m);
		void fillWithMagic();
		void checkIt();
		int sumHoriz(int row);
		int sumVert(int column);
		int sumDiag();
		int sumDiag2();
	};

#endif /* LAB2_H_ */
