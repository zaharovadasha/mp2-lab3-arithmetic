// объявление функций и классов для вычисления арифметических выражений
#pragma once 
#include <string>
#include "stack.h"
#include <iostream>

using namespace std;
enum LexType {OP,VAL,OP_BR,CL_BR,VAR, UNKNOWN};
const string operators= "(+-*/)";
struct Lexem
{
	LexType type;
	double value;
	string symbol;
	Lexem();
	~Lexem(){};		
	Lexem(const string& str);
	Lexem(const char a);		
	Lexem(const Lexem&p);//конктруктор копирования		
	Lexem& operator=(const Lexem&p);
	int prioritet();//выводит приоритет операции
	void inputVar();
	

};
class Arithmetic
{
	string inputStr;
	Lexem* inputLexems;
	int nLex; //количество лексем во входной строке
	Lexem* polishLexems; //массив лексем (польская запись)
	int nPolish; //количество лексем в польской записи

public:
	string StringConversion(const string& str);
	Arithmetic(const string& str);	
	~Arithmetic() {delete[] inputLexems; delete [] polishLexems; }
	void DivideToinputLexems(); //разбиение  входной строки на массив лексем(определяя количество).
	void ConvertToPolish();//преобразование строки в польскую запись
	void Change() ; //замена переменных
	double Calculate();//вычисление по польской записи
	double GetValueLexem(const int i) {return inputLexems[i].value;}	
	double GetValuePolishLexems(const int i) { return polishLexems[i].value; }
	int CheckOperators();	
	int CheckBrackets();
	int CheckSymbol();
	int CheckPoints(const string& str);	
};

 