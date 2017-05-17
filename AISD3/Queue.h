#pragma once

class Queue
{
public:
	Queue(const int* Size);
	~Queue();
	void Enqueue(const int* Value);
	int Dequeue();
	bool IsEmpty();
private:
	int Size;
	int First;
	int Last;
	int* Q;
};