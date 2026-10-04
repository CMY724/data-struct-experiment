#include <iostream>
using namespace std;

typedef int Status;
#define OK 1
#define FULL 0
#define EMPTY 0

template<class T>
class CircularQueue
{
public:
	T* base;
	int front;
	int rear;

public:
	CircularQueue(int n)
	{
		base = new T[n+1];
		front = rear = 0;
	}

	~CircularQueue()
	{
		delete[]base;
	}

	Status EnQueue(int n,T e)
	{
		if ((rear + 1) % (n+1) == front)
		{
			return FULL;
		}
		base[rear] = e;
		rear = (rear + 1) % (n+1);

		return OK;
	}

	Status DeQueue(int n, T& e)
	{
		if (front == rear)
		{
			return EMPTY;
		}
		e = base[front];
		front = (front + 1) % (n + 1);

		return OK;
	}

	Status IsEmpty()
	{
		return front == rear;
	}

};

struct Person
{
	int password;
	int number;
};

int main()
{
	int T;
	cin >> T;

	//CircularQueue<Person> q=CircularQueue<Person>(1);


	for (int i = 0; i < T; i++)
	{
		int n;
		cin >> n;
		CircularQueue<Person> q(n);
		Person p;

		for (int j = 0; j < n; j++)
		{
			cin >> p.password;
			p.number = j + 1;
			q.EnQueue(n,p);
		}

		int m = 6;
		
		while (!q.IsEmpty())
		{
			//报到1到m-1的人要先出队再入队 因为队列出队永远是队头的人 这样实现循环
			for (int j = 1; j < m; j++)
			{
				q.DeQueue(n, p);
				q.EnQueue(n, p);
			}

			//报到m
			q.DeQueue(n, p);

			m = p.password;

			cout << p.number;
			if (!q.IsEmpty())
			{
				cout << " ";
			}
		

		}

		cout << endl;







	}


	return 0;
}