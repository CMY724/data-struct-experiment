#include <iostream>
using namespace std;

typedef int Status;
#define OK 1
#define ERROR 0

template<class T>
struct Node
{
	T data;
	Node<T>* next;
};

class PolyData
{
public:
	int coef;
	int expn;

public:
	PolyData(int c = 0, int e = 0)
	{
		coef = c;
		expn = e;
	}
};

class Polynomial
{
public:
	Node<PolyData>* head;
public:
	Polynomial()
	{
		head = new Node<PolyData>;
		head->next = NULL;
	}

	~Polynomial()
	{
		Node<PolyData>* p = head;
		if (head)
		{
			p = head;
			head = head->next;
			delete p;
		}
	}

	//插入多项式的项
	Status Insert(PolyData e)
	{
		Node<PolyData>* pre, * p, * s;

		pre = this->head;
		p = pre->next;

		if (p && p->data.expn > e.expn)
		{
			pre = p;
			p = p->next;
		}

		if (p && p->data.expn == e.expn)
		{
			int a = p->data.coef + e.coef;
			if (a)
				p->data.coef = a;
			else
			{
				pre->next = p->next;
				delete p;
			}
		}
		else
		{
			s = new Node<PolyData>;
			s->data = e;
			s->next = p;
			pre->next = s;
		}

		return OK;
	}

	void Create()
	{
		PolyData e;

		while (cin >> e.coef >> e.expn) //直到输入结束
		{
			if (e.coef != 0)
			{
				this->Insert(e);
			}
		}
	}

	void Derive(Polynomial& La)
	{
		Node<PolyData>* p;
		p = La.head->next;

		while (p)
		{
			if (p->data.expn != 0)
			{
				PolyData e = PolyData(p->data.coef * p->data.expn,
					p->data.expn - 1);
				this->Insert(e);
			}

			p = p->next;
		}
	}

	void Output()
	{
		Node<PolyData>* p;
		p = this->head->next;

		if (!p) cout << "0 0";

		while (p)
		{
			if (p != head->next)
			{
				cout << " ";
			}
			cout << p->data.coef << " " << p->data.expn;
			p = p->next;
		}

		cout << "\n";
	}
};

int main()
{

	Polynomial La,Lb;
	La.Create();
	Lb.Derive(La);
	Lb.Output();

	return 0;
}