#include <iostream>
using namespace std;

//总结
//一元多项式相加 乘积
//先构造出Node PolyData Polynomial 再进行实现 主要是代码细节要注意

typedef int Status;
#define OK 1
#define ERROR 0


//单链表节点
template <class T>
struct Node
{
	T data;
	Node* next;
};


//多项式的项
class PolyData
{
public:
	int coef;
	int expn;
public:
	PolyData(int c = 0,int e = 0)
	{
		coef = c;
		expn = e;
	}
};



class Polynomial
{
public:
	Node<PolyData> * head;

public:
	Polynomial()
	{
		head = new Node<PolyData>;
		head->next = NULL;
	}
	~Polynomial()
	{
		Node<PolyData>* p;
		while (head)
		{
			p = head;
			head = head->next;
			delete p;
		}
	}

	//构造多项式的插入
	Status Insert(PolyData e)
	{
		Node<PolyData>* p, * pre, * s;
		pre = this->head;
		p = pre->next;

		while (p && p->data.expn > e.expn)//找插入位置
		{
			pre = p;
			p = p->next;
		}

		if (p && p->data.expn == e.expn)
		{
			int a = p->data.coef + e.coef;

			if (a)
			{
				p->data.coef = a;
			}
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

	//构造了一个多项式
	void Create()
	{
		int n;
		PolyData e;

		cin >> n;
		for (int i = 1; i <= n; i++)
		{
			cin >> e.coef >> e.expn;
			Insert(e);
		}
	}

	void Add(Polynomial& La, Polynomial& Lb)
	{
		Node<PolyData>* pa, * pb;

		pa = La.head->next;
		pb = Lb.head->next;

		while (pa && pb)
		{
			if (pa->data.expn > pb->data.expn)
			{
				this->Insert(pa->data);
				pa = pa->next;
			}

			else if (pa->data.expn < pb->data.expn)
			{
				this->Insert(pb->data);
				pb = pb->next;
			}

			else
			{
				int a = pa->data.coef + pb->data.coef;

				if (a)
					this->Insert(PolyData(a, pa->data.expn));
				pa = pa->next;
				pb = pb->next;

			}
		}

		while (pa)
		{
			this->Insert(pa->data);
			pa = pa->next;
		}

		while (pb)
		{
			this->Insert(pb->data);
			pb = pb->next;
		}
	}

	void Mul(Polynomial& La, Polynomial& Lb)
	{
		Node<PolyData>* pa, * pb;

		for (pa = La.head->next; pa; pa = pa->next)
		{
			for (pb = Lb.head->next; pb; pb = pb->next)
			{
				PolyData e=PolyData(pa->data.coef * pb->data.coef,
					pa->data.expn + pb->data.expn);
				this->Insert(e);
			}
		}
	}

	void Output()
	{
		Node<PolyData>* p = this->head->next;

		if (!p) cout << "0 0";


		while (p)
		{
			if (p != head->next) cout << " ";
			cout << p->data.coef << " " << p->data.expn;
			p = p->next;
		}

		cout << "\n";
	}

};



int main()
{
	Polynomial La, Lb, Lc, Ld;

	La.Create();
	Lb.Create();

	Ld.Mul(La, Lb);
	Lc.Add(La, Lb);

	
	Ld.Output();
	Lc.Output();


	return 0;
}
