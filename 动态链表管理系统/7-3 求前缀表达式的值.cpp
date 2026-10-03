#include <iostream>
#include <string>
using namespace std;

typedef int Status;
#define OK 1
#define ERROR 0
#define MaxSize 30

template <class T>
class SqStack
{
public:
	T* base;
	T* top;
	int stacksize;
public:
	SqStack()
	{
		base = new T[MaxSize];
		top = base;
		stacksize = MaxSize;
	}

	~SqStack()
	{
		delete[]base;
	}

	Status Push(T e)
	{
		if (top - base >= stacksize)
			return ERROR;
		*top++ = e;
		return OK;
	}

	Status Pop(T& e)
	{
		if (top == base)
			return ERROR;
		e = *--top;
		return OK;
	}

};

bool In(string s)
{
	return s == "+" || s == "-" || s == "*" || s == "/";
}

double Cal(double a,char op,double b)
{
	switch (op)
	{
	case'+':return a + b;
	case'-':return a - b;
	case'*':return a * b;
	case'/':return a / b;
	}

	return 0;
}

double EvalExpr_PN(string *s, int n, double& result)
{
	SqStack<double>OPND;
	double e;
	double a, b;

	

	for (int i = n - 1; i >= 0; i--)
	{
		if (!In(s[i]))
		{
			e = stod(s[i]);//字符串转换成double
			OPND.Push(e);
		}
		else
		{
			if (OPND.Pop(a) == ERROR)
				return ERROR;

			if (OPND.Pop(b) == ERROR)
				return ERROR;

			if (s[i] == "/" && b == 0)
				return ERROR;

			OPND.Push(Cal(a, s[i][0], b));//s[i][0] 取字符串数组中第 i 个字符串的第一个字符。
		}
	}
	if (OPND.Pop(result) == ERROR)
		return ERROR;

	return OK;
}


int main()
{
	string s[30];
	int n = 0;
	while (n<30 && cin >> s[n])
	{
		n++;
	}
	//得到输入的前缀表达式
	//从右往左读 读到数字入栈 读到运算符就抽两个数字出来进行运算

	double result;

	if (EvalExpr_PN(s, n, result) == OK)
		printf("%.1f\n", result);
	else
		cout << "ERROR\n";//要排除输出0.0的情况

	return 0;
}