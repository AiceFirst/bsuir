#include "main.h"


int main(int argc, char *argv[])
{
	//����� ����
	Queue <int> q;
	int *a = new int;
	*a = 123;
	q.Push(a);
	a = new int;
	*a = 456;
	q.Push(a);
	//������������� ��������
	cout << "Queue int:" << endl;
	q.View();
	cout << endl;
	a = q.Pop();
	//�������� ���� � �������� �� ��� ������
	cout << "Pop " << *a << endl;
	//������������� ��������
	cout << endl << "Queue int:" << endl;
	q.View();
	cout << endl << endl;

	Queue <double> d;
	double *dd = new double;
	*dd = 4.5;
	d.Push(dd);
	dd = new double;
	*dd = 6.234;
	d.Push(dd);
	//������������� ��������
	cout << "Queue double:" << endl;
	d.View();
	cout << endl;
	dd = d.Pop();
	//�������� ���� � �������� �� ��� ������
	cout << "Pop " << *dd << endl;
	//������������� ��������
	cout << endl << "Queue double:" << endl;
	d.View();

	system("pause");

	return 0;
}


template <typename T>
Queue<T>::Queue()
{

}

template <typename T>
Queue<T>::~Queue()
{
	if (queue->data != NULL)
	{
		while (queue->next != NULL)
		{
			DeleteItem();
		}
	}
	delete queue;
}

template <typename T>
T* Queue<T>::Pop()
{
	T* tmp;
	
	if (queue->data == NULL)
	{
		return NULL;
	}
	tmp = queue->data;

	DeleteItem();

	return tmp;
}

template <typename T>
void Queue<T>::View()
{
	ViewQueue(queue);
}

template <typename T>
void Queue<T>::Push(T* data)
{
	AddItem(queue, data);
}

template <typename T>
void Queue<T>::AddItem(QueueItem<T>* st, T* data)
{
	if (st->data == NULL)
	{
		st->data = data;
	}
	else
	{
		if (st->next == NULL)
		{
			st->next = new QueueItem<T>;
		}
		AddItem(st->next, data);
	}
}

template <typename T>
void Queue<T>::ViewQueue(QueueItem<T>* st)
{
	if (st->data != NULL)
	{
		cout << *st->data << endl;
	}
	if (st->next != NULL)
	{
		ViewQueue(st->next);
	}
}

template <typename T>
void Queue<T>::DeleteItem()
{
	if (queue->data != NULL)
	{
		if (queue->next != NULL)
		{
			QueueItem<T> *tmp;
			tmp = queue->next;
			delete queue;
			queue = tmp;
		}
		else
		{
			queue->data = NULL;
		}
	}
}