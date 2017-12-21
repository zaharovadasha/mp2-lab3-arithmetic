// ���������� ������� � ������� ��� ���������� �������������� ���������
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
	Lexem(const Lexem&p);//����������� �����������		
	Lexem& operator=(const Lexem&p);
	int prioritet();//������� ��������� ��������
	void inputVar();
	

};
class Arithmetic
{
	string inputStr;
	Lexem* inputLexems;
	int nLex; //���������� ������ �� ������� ������
	Lexem* polishLexems; //������ ������ (�������� ������)
	int nPolish; //���������� ������ � �������� ������

public:
	string StringConversion(const string& str);
	Arithmetic(const string& str);	
	~Arithmetic() {delete[] inputLexems; delete [] polishLexems; }
	void DivideToinputLexems(); //���������  ������� ������ �� ������ ������(��������� ����������).
	void ConvertToPolish();//�������������� ������ � �������� ������
	void Change() ; //������ ����������
	double Calculate();//���������� �� �������� ������
	double GetValueLexem(const int i) {return inputLexems[i].value;}	
	double GetValuePolishLexems(const int i) { return polishLexems[i].value; }
	int CheckOperators();	
	int CheckBrackets();
	int CheckSymbol();
	int CheckPoints(const string& str);	
};

 