// matrix.cpp : Defines the entry point for the console application.
//

//Douglas loughmiller
//Matrix source code

//for input formatting
#include <iomanip>
//for console acsess
#include <iostream>
#include <string>

using namespace std;

//matrixes of constant size
const int width = 2, height = 2;

//matrix data struct
struct matrix {
	float num[height][width]; //2d array to store numbers
	string Title;    //name of matrix
};
 
//Matrix operations
void calc_sum(matrix &a);
void calc_diff(matrix &a);
void calc_mult(matrix &a);
void calc_prod(matrix &a);
void calc_inv(matrix &a);

//User inputs
void get_matrix(matrix &a);
void get_scalar(float &a);

//console outputs
void print_matrix(matrix &a, int n);
inline void print_scalar(float &k);

//misc functions
inline void border(float maxlength);

int main() {

	matrix a;
	char matrix_Menue;
	bool running = true;	

	//get first matrix
	get_matrix(a);

	//set title to matrix a
	a.Title = "Matrix A";

	do{
		//display unser input and output
		print_matrix(a, width * height);

		//set title back to a after displaying output
		a.Title = "Matrix A";

		//display menue			
		cout << "------------ Matrix math -------------------" << endl << endl;

		cout << "what would you like to do to this matrix?" << endl << endl
				<< " each sucsessive operation" << endl
				<< " will act on the previous" << endl
				<< " output, untill a new matrix is entered" << endl << endl

				<< "- matrix-Operations ------------------------" << endl
				<< "   Type 3 for matrix addition" << endl
				<< "   Type 4 for matrix subtraction" << endl
				<< "   Type 5 for scalar multiplacation" << endl
				<< "   Type 6 for matrix multiplacation" << endl
				<< "   Type 7 to invert a matrix" << endl
			    << "   Type 8 to enter a new matrix" << endl
				<< "   Type 9 to quit (quits program)" << endl << endl
				//prompt
				<< "> ";

		//get menue selection
		cin >> matrix_Menue;

		//choose what function to call or quit
		switch (matrix_Menue) {

		case '3': calc_sum(a); break;
		case '4': calc_diff(a); break;
		case '5': calc_mult(a); break;
		case '6': calc_prod(a); break;
		case '7': calc_inv(a); break;
		case '8': get_matrix(a); break;
		case '9': running = false;
		default: cout << "invalid input" << endl;
		}
						
	} while (running);

	//end program
	return 0;		
}

void calc_sum(matrix &a) {
	matrix b;

	//get second matrix
	b.Title = "Matrix B";
	get_matrix(b);

	//display input matrix
	print_matrix(a, width * height);

	//display unser input
	print_matrix(b, width * height);

	//do addition operation
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			a.num[i][j] += b.num[i][j];
		}
	}
	//set title for output
	a.Title = "Sum of A and B";
}

void calc_diff(matrix &a) {
	matrix b;

	//get second matrix
	b.Title = "Matrix B";
	get_matrix(b);

	//display input matrix
	print_matrix(a, width * height);

	//display unser input
	print_matrix(b, width * height);

	//do subtraction operation
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			a.num[i][j] -= b.num[i][j];
		}
	}
	a.Title = "Difference of A";	
}

	
void calc_mult(matrix &a) {
	float k;

	//get scaler
	get_scalar(k);
	print_scalar(k);

	//display input matrix
	print_matrix(a, width * height);

	//preform scaler multiplication
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			a.num[i][j] *= k;
		}
	}
	a.Title = "Scalar product of Matrix A";
}
  
void calc_prod(matrix &a) {
	matrix b, Temp;
	float sum;

	//get second matrix
	b.Title = "Matrix B";
	get_matrix(b);

	//display input matrix
	print_matrix(a, width * height);

	//display unser input
	print_matrix(b, width * height);

	//reform mattrix dot product
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			//get sum for each multiplacation operation in each row
			sum = 0;
			for (int k = 0; k < width; k++) {
				sum += a.num[i][k] * b.num[k][j];
			}
			//this is a destructive process so save in seperate matrix
			Temp.num[i][j] = sum;
		}
	}
	//apply sum to matrix A
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			a.num[i][j] = Temp.num[i][j];
		}
	}
	a.Title = "Dot product of Matrix A and B";
}

void calc_inv(matrix &a) {
	float determinate;

	//display input matrix
	print_matrix(a, width * height);

	//calculate determinate
	determinate = (a.num[0][0] * a.num[1][1]) - (a.num[0][1] * a.num[1][0]);

	//swap top left and bottom right corners
	swap(a.num[0][0], a.num[1][1]);

	//preform scaler multiplication with the invese of the determinate and Matrix A
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			//just before operation
			//invert top right and bottom left corners
			if (i != j) {
				a.num[i][j] = -a.num[i][j];
			}
			a.num[i][j] *= 1 / determinate;
		}
	}

	//display output
	a.Title = "Inverse of A";
}

void get_matrix(matrix &a) {
	int count = 0;
	
	//display name
	cout << a.Title << endl;

	//clears random data
	memset(a.num, 0, sizeof(a.num));

	//foor loops to get each position
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			cout << "enter number that goes here, marked by x." << endl;
			print_matrix(a, count);
			count++;
			//prompt
			cout << "> ";
			cin >> a.num[i][j];
		}
	}

}

void get_scalar(float &k) {
	cout << "enter a scaler value " << endl << endl
		 //prompt
		 << "> ";
	cin >> k;
	print_scalar(k);
}

inline void print_scalar(float &k) {
	cout << "scalar value  = " << k;
}

inline void border(float maxlength) {
	//Display border for the top and bottom part of the brackets
	cout << " -";
	for (int j = 0; j < (width - 2) * maxlength; j++) //amount of space for end numbers
		cout << " ";
	for (int j = 0; j < 2 * (maxlength - 1); j++) //amount of space for middle numbers
		cout << " ";
	cout << "- " << endl;
}

void print_matrix(matrix &a, int n) {
	
	int maxlength = 1, count = 0;

	//calculate amount to space to dedicate for each number	then add one for readability
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			//for each number divide its value by 10 untill it reaches 0 givving length
			int  length = 0, Temp = a.num[i][j];		
			string sNum = to_string(a.num[i][j]);
			//remove trailing anomalous decimals from intigers from string
			sNum.erase(sNum.find_last_not_of('0') + 1, string::npos);
			sNum.erase(sNum.find_last_not_of('1') + 1, string::npos);
			sNum.erase(sNum.find_last_not_of('2') + 1, string::npos);
			sNum.erase(sNum.find_last_not_of('3') + 1, string::npos);
			sNum.erase(sNum.find_last_not_of('4') + 1, string::npos);
			sNum.erase(sNum.find_last_not_of('5') + 1, string::npos);
			sNum.erase(sNum.find_last_not_of('6') + 1, string::npos);
			sNum.erase(sNum.find_last_not_of('7') + 1, string::npos);
			sNum.erase(sNum.find_last_not_of('8') + 1, string::npos);
			sNum.erase(sNum.find_last_not_of('9') + 1, string::npos);
			length = sNum.length();
			length++; // add an extra space
			//save the highest value
			if (length > maxlength) maxlength = length;
		}
	}

	//dont display title every time user unputs number
	if (n == width * height) {
		//display title
		cout << a.Title << endl;
		for (int i = 0; i < a.Title.length(); i++) {
			cout << "-";
		}
		cout << endl;
	}

	//top border
	border(maxlength);

	//inside 
	for (int i = 0; i < height; i++) {
		cout << "|";
		for (int j = 0; j < width; j++) {
			//if filled
			if (count < n) {
				cout << setw(maxlength) << a.num[i][j];
			}
			//if spot being filled
			else if (count == n) {
				cout << setw(maxlength) << "X";
			}
			//if nothing there
			else
				cout << setw(maxlength) << " ";
			count++;
		}
		cout << "|" << endl;
	}
	//bottom border
	border(maxlength);
}
