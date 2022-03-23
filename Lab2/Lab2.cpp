/*
 *Author: Ngawang Rinchen
 *
 *
 *
 * Problem: Create a calculator of a struct type along with operators of an enum type, which should, at the very least, include operators of addition, subtraction, multiplication, and division.  Additionally, the operands should not be limited to integers.  Obtain a mathematical expression as input directly from the user or from an input file. 
 *
 * Solution:
 *
 * 	The main difficulity lies in attempting to parse a mathematical expression whose method must take in consideration PEMDAS.  It seems best to set the values of the enumeration operators to their ascii values and read the mathematical expression as string of characters to attempt to identify the operators within the input string.  The Calculator structure will use a for-loop and a switch block to identify every operator within the expression, starting from parenthesis and working my way down.  The corresponding methods of the operators must return a reduced version of the string fed to keep track of current progress.  
 *
 * 	struct Calculator {}
 * 		
 * 	enum Operator {}
 *
 */



#include <iostream>
#include <string>
#include <math.h>
using namespace std;

enum Operator {
	exponent = 94,
	multiplication = 42,
	division = 47,
	addition = 43,
	subtraction = 45,
};

struct Calculator {


	void instruction(){
		cout << "Welcome to calculator.\nInput a mathematical expression with the following operators (addition: +) (subtraction: -) (division: /) (multiplication: *) (exponent: ^)\nPlease avoid unncessary spaces.\n";	
	}

	int findLeftBound(string mathExp, int index){
		int curIndex = index - 1;
		int flag = mathExp.at(curIndex);

		while((flag < 58 && flag > 47 || flag == 46) && curIndex>0){
			flag = mathExp.at(--curIndex);
		}
		return curIndex;
	}

	int findRightBound(string mathExp, int index){
		int curIndex = index + 1;
		int flag = mathExp.at(curIndex);

		while((flag < 58 && flag > 47 || flag == 46) && curIndex < mathExp.length()-1 ){
			flag = mathExp.at(++curIndex);
		}

		return curIndex;
	}

	void power(string &mathExp, int index){
		int leftBound = findLeftBound(mathExp, index);	
		int rightBound = findRightBound(mathExp, index);

		float operandOne = std::stof( mathExp.substr(leftBound, index - leftBound));
		float operandTwo = std::stof( mathExp.substr(index+1, rightBound - (index)));

		float result = pow(operandOne, operandTwo);
		mathExp = mathExp.replace(leftBound, rightBound, std::to_string(result));	
	}	

	void multiply(string &mathExp, int index){
		int leftBound = findLeftBound(mathExp, index);	
		int rightBound = findRightBound(mathExp, index);

		float operandOne = std::stof( mathExp.substr(leftBound, index - leftBound));
		float operandTwo = std::stof( mathExp.substr(index+1, rightBound - (index)));

		float result = operandOne * operandTwo;
		mathExp = mathExp.replace(leftBound, rightBound, std::to_string(result));	
	}	

	void divide(string &mathExp, int index){
		int leftBound = findLeftBound(mathExp, index);	
		int rightBound = findRightBound(mathExp, index);

		float operandOne = std::stof( mathExp.substr(leftBound, index - leftBound));
		float operandTwo = std::stof( mathExp.substr(index+1, rightBound - (index)));

		float result = operandOne / operandTwo; 
		string resultString = 
			mathExp = mathExp.replace(leftBound, rightBound, std::to_string(result));
	}


	void add(string &mathExp, int index){

		int leftBound = findLeftBound(mathExp, index);	
		int rightBound = findRightBound(mathExp, index);

		float operandOne = std::stof( mathExp.substr(leftBound, index - leftBound));
		float operandTwo = std::stof( mathExp.substr(index+1, rightBound - (index)));

		float result = operandOne + operandTwo;
		mathExp = mathExp.replace(leftBound, rightBound, std::to_string(result));	
	}



	void subtract(string &mathExp, int index){
		int leftBound = findLeftBound(mathExp, index);	
		int rightBound = findRightBound(mathExp, index);

		float operandOne = std::stof( mathExp.substr(leftBound, index - leftBound));
		float operandTwo = std::stof( mathExp.substr(index+1, rightBound - (index)));

		float result = operandOne - operandTwo;
		mathExp = mathExp.replace(leftBound, rightBound, std::to_string(result));	
	}

	void calculate(string &mathExp){

		Operator op[] {exponent, multiplication, division, addition, subtraction};


		for(int i = 0; i < 6; i++){
			int currentOp = op[i];

			for (int j = 0; j < mathExp.length(); j++){
				if(mathExp.at(j)==currentOp){
					
					switch(currentOp){

						case exponent:
							power(mathExp,j);
							j=0;
							break;
						case multiplication:
							multiply(mathExp,j);
							j=0;
							break;
						case division:
							divide(mathExp,j);
					
							j=0;
							break;
						case addition:
							add(mathExp, j);
							j = 0;
							break;
						case subtraction:
							subtract(mathExp, j);
							j=0;
							break;
					}
				}
			}	


		}

		printf("%.2f", std::stof(mathExp));
	}

};






int main(){
	string mathExp;
	Calculator calculator;

	calculator.instruction();
	cin >> mathExp;

	calculator.calculate(mathExp);
	cout << "\n\n";		
	return 0;
}

