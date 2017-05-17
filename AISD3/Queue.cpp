#include "Queue.h"

Queue::Queue(const int * Size) : Size(*Size), First(-1), Last(-1)
{
	Q = new int[this->Size];
}

Queue::~Queue()
{
	delete[] Q;
}

void Queue::Enqueue(const int * Value)
{
	if (First == -1)
	{
		First = Last = 0;
		Q[First] = *Value;
		return;
	}
	Last++;
	if (Last == Size)
		Last = 0;
	Q[Last] = *Value;
}

int Queue::Dequeue()
{
	int R = Q[First];
	if (First == Last)
		First = -1;
	else
	{
		First++;
		if (First == Size)
			First = 0;
	}
	return R;
}

bool Queue::IsEmpty()
{
	return First == -1;
}
