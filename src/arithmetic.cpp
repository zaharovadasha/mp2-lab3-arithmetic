// реализаци€ функций и классов дл€ вычислени€ арифметических выражений
#include "arithmetic.h"


Lexem::Lexem()
{
	type = VAR;
	//val = 0;
}

Lexem::Lexem(const string& str)
{
	value = stod(str);
	type = VAL;
	symbol = str;
}


Lexem::Lexem(const char a)
{ 
	if (isalpha (a))
	{ 
		type=VAR;
		value=a;
	}
	else
	{
		value=operators.find(a);
		switch (operators.find(a))
		{
		case 0:
			type=OP_BR;
			break;
		case 5:
			type=CL_BR;
			break;
		}
		if ((value>=0)&&(value<=5))
		{
			if ((value>0)&&(value<5))
			type=OP;
		}
		else
			type=UNKNOWN;
	}


	/*value =operators.find(a);

	if (value == operators.npos)
	type = UNKNOWN;
	else
	if (value < 4)
	type = OP;
	else if (value == 4)
	type = OP_BR;
	else type = CL_BR;
	symbol = a;*/
}


Lexem::Lexem(const Lexem &p)
{
	value = p.value;
	type = p.type;
}

Lexem& Lexem::operator=(const Lexem &p)
{
	value = p.value;
	type = p.type;
	return *this;
}
void Lexem::inputVar()
{
	char a=(char)value;
	cout<<"Input VARIABLE" <<a<<":";
	cin>>value;
	cout<<endl;
}


Arithmetic::Arithmetic(const string& str)
{
	string temp;
	temp=StringConversion(str);
	inputLexems = new Lexem[temp.length()];
	polishLexems = new Lexem[temp.length()];
	inputStr = temp;
	nLex = 0;
	nPolish=0;	
}

void Arithmetic::DivideToinputLexems()//разбиение  входной строки на массив лексем(определ€€ количество).
{
	int i = 0;
	int k=inputStr.length();
	for (i = 0; i < k ; i++)
	{
		char a = inputStr[i];


		if ((operators.find(a) != string::npos)||(isalpha(a)))// если оператор найден
		{	Lexem d(a);
		inputLexems[nLex] =d; 
		nLex++;

		}
		else 
			if (isdigit(a)) //цифра,начина€ с которой будет число
			{
				string x;
				int j = i;
				while ((j < k) && (isdigit(inputStr[j]) || inputStr[j] == '.'))
					j++;
				x = inputStr.substr(i, j - i);
				if (CheckPoints(x))
				{
					Lexem d(x);
					inputLexems[nLex] =d;
					nLex++;
				}
				else
				{
					inputLexems[nLex].type=UNKNOWN;
					nLex++;
				}
				i=j-1;
			}
			else
				if(a!=' ')
				{
					inputLexems[nLex].type=UNKNOWN;
					nLex++;
				}
	}

}

	/*if (i != inputStr.length()) 
	throw "Don'tDivideLexem";*/

void Arithmetic::Change() //возвращает позицию ошибки 
{
	for (int i = 0; i < nLex; i++)
	{
		if(inputLexems[i].type==VAR)
		{
			char a=(char)inputLexems[i].value;
			inputLexems[i].inputVar();
			inputLexems[i].type=VAL;
			for (int j=i+1;j<nLex; j++)
			{
				if((inputLexems[j].type==VAR)&&(a==(char)inputLexems[j].value))
					inputLexems[j]=inputLexems[i];
			}
		}
	}
}

int Lexem::prioritet()
  {
  	int s; 	
 	if (value == 0)
 		s = 0;
  	else
 
 	{
 		if ((value > 0) && (value <= 2))
			s = 1;
 		else
 			s = 2;
 	}
  	return s;
  }



void Arithmetic::ConvertToPolish()
{
Stack<Lexem> st;
Stack<int> s;
s.push(0);
for (int i = 0; i < nLex; i++)
{
	int g=st.getTop();
	switch (inputLexems[i].type)
	{
	case VAL:
		{
			polishLexems[nPolish] = inputLexems[i];
			nPolish++;
			break;
		}
	case OP_BR:
		{
			st.push(inputLexems[i]);
			s.push(st.getTop());
			break;
		}
	case OP:
		{
			if ((st.isempty())||(st.view().prioritet()<inputLexems[i].prioritet()))
				st.push(inputLexems[i]);
			else 
			{ 
				polishLexems[nPolish]=st.pop();
				nPolish++;					
				st.push(inputLexems[i]);

			}
			break;
		}
	case CL_BR:
		{
			for (int j = s.view(); j < g; j++)
			{
				polishLexems[nPolish] = st.pop();
				nPolish++;
			}
			st.pop();
			s.pop();
			break;
		}
	}
	}
if (!st.isempty())
{
	while (!st.isempty())
	{
		polishLexems[nPolish]=st.pop();
		nPolish++;
	}
}
}

double Arithmetic::Calculate()
{
	Stack<double> st;
	for (int i=0; i<nPolish; i++)
	{
		if (polishLexems[i].type == VAL)
			st.push(polishLexems[i].value);
		else
		{
			double a = st.pop(), b = st.pop();
			switch ((int)polishLexems[i].value)
			{
			case 1:
				st.push(b + a);
				break;
			case 2:
				st.push(b - a);
				break;
			case 3:
				st.push(b * a);
				break;
			case 4:
				st.push(b / a);
				break;
			}
		}
	}
	return st.pop();
}

string Arithmetic::StringConversion(const string & str)
 {
 	string temp = str;
 	while (temp[0] == ' ')
 		temp.erase(0, 1);
 	if (temp[0] == '-')
 			temp = "0" + temp;
 	for (int i = 0; i < temp.length() - 1; i++)
	{
 		if ((temp[i] == '(') && (temp[i + 1] == ' '))
			while (temp[i + 1] == ' ')
 				temp.erase(i + 1, 1);
 		if ((temp[i] == '(') && (temp[i + 1] == '-'))
 			temp.insert(i + 1, "0");
 	}
 	return temp;
 }
int Arithmetic::CheckPoints(const string& str)
  {
  	int l = str.length(), s = 0;
 	bool flag = true;
 
 	for (int i = 0; i < l; i++)
 		if (str[i] == '.')
 	s++;
 
 if ((str[0] == '.') || (str[l] == '.') || (s > 1))
 		flag = false;
 	return flag;
 }
 
 int Arithmetic::CheckBrackets()
 {
 	int Br = 0, s = 0;
 
 	bool flag = true;
 	for (int i = 0; i < nLex && Br >= 0; i++)
 	{
 		if (inputLexems[i].type == OP_BR)
 		{
 			Br++;
 			s = i;
 		}
 		if (inputLexems[i].type == CL_BR)
 		{
 		Br--;
 		s = i;
 		}
 	}
 	if (Br != 0)
 	{
 		cout << "Brackets ERROR: " << s + 1 << endl;
 		flag = false;
 	}
 	return flag;
 }
 
 int Arithmetic::CheckSymbol()
 {
 	bool flag = true;
 	for (int i = 0; i < nLex - 1; i++)
 		if (inputLexems[i].type == UNKNOWN)
 		{
 			cout << "Unknown symbol: " << i + 1 << endl;
 			flag = false;
 		}
 
 	return flag;
 }
 
 int Arithmetic::CheckOperators()
 {
 	bool flag = true;
 	if (!((inputLexems[0].type == OP_BR) || (inputLexems[0].type == VAL) || (inputLexems[0].type == VAR) || (inputLexems[0].value == 2)))
 	{
 		cout << "Mistake OPERATOR IN :" << 1 << endl;
 		flag = false;
 	}
 
 	for (int i = 0; i < nLex - 1; i++)
 		{
 			switch (inputLexems[i].type)
 			{
 			case OP_BR:
 				if (!((inputLexems[i+1].type == OP_BR) || (inputLexems[i+1].type == CL_BR) || (inputLexems[i+1].type == VAL) || (inputLexems[i+1].type == VAR) || (inputLexems[i+1].value == 2)))
 				{
 					cout << "Mistake OPERATOR IN :" << i + 1 << endl;
 					flag = false;
 				}
 				break;
 			case VAL:
 				if (!((inputLexems[i+1].type == OP) || (inputLexems[i+1].type == CL_BR)))
 				{
 					cout << "Mistake OPERATOR IN :" << i + 1 << endl;
 					flag = false;
 				}
 				break;
 			case VAR:
 				if (!((inputLexems[i+1].type == OP) || (inputLexems[i+1].type == CL_BR)))
 				{
 					cout << "Mistake OPERATOR IN :" << i + 1 << endl;
 					flag = false;
 				}
 				break;
 			case OP:
 				if (!((inputLexems[i+1].type == VAL) || (inputLexems[i+1].type == VAR) || (inputLexems[i+1].type == OP_BR)))
 				{
 					cout << "Mistake OPERATOR IN :" << i + 1 << endl;
 					flag = false;
 				}
 				break;
 			case CL_BR:
 			if (!((inputLexems[i+1].type == OP) || (inputLexems[i+1].type == VAR) || (inputLexems[i+1].type == CL_BR)))
 				{
 					cout << "Mistake OPERATOR IN :" << i + 1 << endl;
 					flag = false;
 				}
 				break;
 			}
 		}
 
 	if (!((inputLexems[nLex-1].type == CL_BR) || (inputLexems[nLex-1].type == VAL) || (inputLexems[nLex-1].type == VAR)))
 	{
 		cout << "Mistake OPERATOR IN :" << nLex << endl;
 		flag = false;
 	}
 	return flag;
 
  }




/*double Arithmetic::Calc(const string& s)
{
	double res = 0.0;
	Arithmetic a(s);
	a.Check();
	a.ConvertToPolish();
	res = a.Calculate();
	return res;
}*/
