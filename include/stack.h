// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
//при вставке в полный стек должна перевыделяться память


#include <iostream> 
using namespace std; 
const int MAX_STACK_SIZE=10000; 
template <class ValType> 
class Stack 
{ 
protected: 
ValType*pStack; 
int Size; 
int top; 
public: 
Stack(int s=10); 
Stack(const Stack &st); 
~Stack(); 
void push(const ValType &p); 
ValType pop(); 

ValType view() const 
{ 
if (top!=-1) 
return pStack[top]; 
else 
throw "Error"; 

} 
bool isempty() const 
{ 
if (top== -1) return 1; 
else return 0; 
} 
int getTop() const 
{ 
return (top+1); 
} 
int getSize() 
{ 
return Size; 
} 
void clear() 
{ 
top=-1; 
} 
}; 

template <class ValType> 
Stack <ValType>::Stack(int s) 
{ 
if ((s>=0)&&(s<=MAX_STACK_SIZE)) 
{ 
Size=s; 
top=-1; 
pStack=new ValType[Size]; 
} 
else 
throw "Error"; 
} 

template <class ValType> 
Stack <ValType>::Stack(const Stack &st) 
{ 
Size=st.Size; 
pStack=new ValType[Size]; 
for (int i=0; i<top+1; i++) 
pStack[i]=st.pStack[i]; 
} 

template <class ValType> 
Stack <ValType>::~Stack() 
{ 
delete[] pStack; 
} 

template <class ValType> 
void Stack<ValType>::push(const ValType &p)//вставка элемента 
{ 
if (top == (Size - 1))
{
Size *= 2;
ValType *pStack1 = new ValType[Size];
for (int i = 0; i < (top + 1); i++)
pStack1[i] = pStack[i];
delete[] pStack;
pStack = pStack1;
}
pStack[++top] = p; 

}


template <class ValType> 
ValType Stack<ValType>::pop()//извлечение элемента 
{ 
if (top!=-1) 
return pStack[top--]; 
else 
throw "Error"; 
}