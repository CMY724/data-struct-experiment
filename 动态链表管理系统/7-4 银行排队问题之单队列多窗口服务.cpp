#include <iostream>
using namespace std;


typedef int Status;
#define OK 1
#define FULL 0
#define EMPTY 0
#define MaxSize 1001

template<class T>
class CircularQueue
{
	T* base;
	int front;
	int rear;
public:
	CircularQueue()
	{
		base = new T[MaxSize];
		front = rear = 0;
	}

	~CircularQueue()
	{
		delete[]base;
	}

	Status EnQueue(T e)
	{
		if ((rear + 1) % MaxSize == front)
		{
			return FULL;
		}

		base[rear] = e;
		rear = (rear + 1) % MaxSize;
		return OK;
	}

	Status DeQueue(T& e)
	{
		if (front == rear)
		{
			return EMPTY;
		}
		e = base[front];
		front = (front + 1) % MaxSize;
		return OK;
	}

	Status IsEmpty()
	{
		return front == rear;
	}

};

struct Person
{
	int T;//到达时间
	int P;//处理时间
};



int main()
{
	int N, K;
	CircularQueue<Person> q;
	Person p;

	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> p.T >> p.P;
		if (p.P > 60)
		{
			p.P = 60;
		}
		q.EnQueue(p);
	}

	cin >> K;

	int finish[10] = { 0 };
	int count[10] = { 0 };
	int sumwait = 0;
	int maxwait = 0;
	int lastwait = 0;

	while (!q.IsEmpty())
	{
		q.DeQueue(p);

		int k = -1;
		
		//选择编号最小的空闲窗口
		for (int i = 0; i < K; i++)
		{
			if (finish[i] <= p.T)
			{
				k = i;
				break;//找编号最小的 找到了就要break
			}
		}

		//没有空闲的 则k=-1
		//找最早结束服务的
		if (k == -1)
		{
			k = 0;
			for (int i = 0; i < K; i++)
			{
				if (finish[i] < finish[k])
				{
					k = i;
				}
			}
		}

		int start = p.T;
		if (finish[k] > start)
		{
			start = finish[k];
		}


		int wait = start - p.T;
		sumwait += wait;

		if (wait > maxwait)
		{
			maxwait = wait;
		}

		finish[k] = start + p.P;
		count[k]++;

		if (finish[k] > lastwait)
		{
			lastwait = finish[k];
		}

	}

	double average = (double)sumwait / N;

	printf("%.1f %d %d\n", average, maxwait,lastwait);
	
	for (int i = 0; i < K; i++)
	{
		if (i > 0)
		{
			cout << " ";
		}
		cout << count[i];

	}

	cout << endl;

	return 0;
}