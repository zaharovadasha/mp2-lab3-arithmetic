#include "arithmetic.h"
#include <iostream>
using namespace std;



 void main()
  {
 /*	setlocale(LC_ALL, "Russian");
 -
  	string input;
 -	cout << "Введите выражение" << endl;
 -	cin >> input;
 -	Arithmetic A(input);
 -	A.DivideToTerms();
 -	//if ()
 -	//cout << A.Result() << endl;*/
	  string input;
 int p = 1;
 	while (p)
 	{   
 		cout << "Enter the expression" << endl;
 		cin >> input;
 		Arithmetic A(input);
 		A.DivideToinputLexems();
 		if (A.CheckBrackets() && A.CheckSymbol() && A.CheckOperators())
 				{
 					double x;
 					A.Change();
 					A.ConvertToPolish();
 				x = A.Calculate();
 					cout << " = " << x << endl;
 					cout << endl;
 				}
 		cout << "Enter 1 to calculate again" << endl;
 		cout << "Enter 0 to exit" << endl;
 		cin >> p;
 		cout << endl;	
 	}
 	cout << "END" << endl;
 }
 /*{
		cout <<"Your arithmetic expression:\n"; 
		getline(cin, s);
		Arithmetic Exp(s);
		//f = Exp.IsCorrect();
		f = 1;
		if (f)
		{
			double res = Exp.Result();
			cout << res << endl;
			cout << "continue? " << endl;
			cin >> f;
			f = !f;
		}
	} while (f==0);
	return 0;*/

	//double x = Arithmetic::Calc("1+1");
// реализация пользовательского приложения

