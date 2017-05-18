#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include "Queue.h"
#define CHOSEN_BIKES_COUNT 0
#define NONE -1
#define ARRAY_SIZE 20000

void BFS_STAGE(int** Participants, int* PairP, int* PairB, int* Dist, int w, int r, Queue* Q)
{
	for (int i = 0; i < w; i++)
	{
		Dist[i] = NONE;
		if (PairP[i] == NONE)
		{
			Dist[i] = 0;
			Q->Enqueue(&i);
		}
	}
	int p;
	while (!Q->IsEmpty())
	{
		p = Q->Dequeue();
		for (int i = 1; i <= Participants[p][CHOSEN_BIKES_COUNT]; i++)
		{
			if (PairB[Participants[p][i]] != NONE
				&& Dist[PairB[Participants[p][i]]] == NONE)
			{
				Dist[PairB[Participants[p][i]]] = Dist[p] + 1;
				Q->Enqueue(&PairB[Participants[p][i]]);
			}
		}
	}
}

bool DFS(int p, int** Participants, int* PairP, int* PairB, int* Dist, bool* Visited)
{
	Visited[p] = true;
	for (int i = 1; i <= Participants[p][CHOSEN_BIKES_COUNT]; i++)
	{
		if (PairB[Participants[p][i]] == NONE)
		{
			PairB[Participants[p][i]] = p;
			PairP[p] = Participants[p][i];
			return true;
		}
		if (Visited[PairB[Participants[p][i]]] == false
			&& Dist[PairB[Participants[p][i]]] == Dist[p] + 1)
		{
			if (DFS(PairB[Participants[p][i]], Participants, PairP, PairB, Dist, Visited))
			{
				PairB[Participants[p][i]] = p;
				PairP[p] = Participants[p][i];
				return true;
			}
		}
	}
	return false;
}

bool DFS_STAGE(int** Participants, int* PairP, int* PairB, int* Dist, bool* Visited, int w)
{
	bool a = false, b = false;
	for (int i = 0; i < w; i++)
		Visited[i] = false;
	for (int i = 0; i < w; i++)
	{
		if (PairP[i] == NONE)
		{
			a = DFS(i, Participants, PairP, PairB, Dist, Visited);
			if (!b && a)
				b = a;
		}
	}
	return b;
}
void HopcroftKarp(int** Participants, int* PairP, int* PairB, int* Dist, bool* Visited, int w, int r, Queue* Q)
{
	int x = (w > r+1) ? w : r+1;
	for (int i = 0; i < x; i++)
	{
		if (i < w)
			PairP[i] = NONE;
		if (i <= r)
			PairB[i] = NONE;
	}
	bool ok = true;
	while (ok)
	{
		BFS_STAGE(Participants, PairP, PairB, Dist, w, r, Q);
		ok = DFS_STAGE(Participants, PairP, PairB, Dist, Visited, w);
	}
}

int main()
{
	int w, r, tmp;

	char Data[ARRAY_SIZE], *Number;

	fgets(Data, ARRAY_SIZE, stdin);
	Number = strtok(Data, " ");
	w = atoi(Number);
	Number = strtok(NULL, " ");
	r = atoi(Number);

	auto Participants = new int*[w];
	auto Q = new Queue(&w);
	auto PairP = new int[w];
	auto PairB = new int[r + 1];
	auto Dist = new int[w];
	auto Visited = new bool[w];
	int j = 0, i = 0;
	while(fgets(Data, ARRAY_SIZE, stdin) != NULL)
	{
		Number = strtok(Data, " ");
		tmp = atoi(Number);
		Participants[i] = new int[tmp + 1];
		Participants[i][CHOSEN_BIKES_COUNT] = tmp;
		Number = strtok(NULL, " ");
		j = 1;
		while (Number != NULL)
		{
			Participants[i][j++] = atoi(Number);
			Number = strtok(NULL, " ");
		}
		i++;
	}

	int match = w;
	HopcroftKarp(Participants, PairP, PairB, Dist, Visited, w, r, Q);
	for (int i = 0; i < w; i++)
		if (PairP[i] == NONE)
			match--;

	std::cout << match;

	delete Q;
	delete[] PairP;
	delete[] PairB;
	delete[] Dist;
	delete[] Visited;
	for (int i = 0; i < w; i++)
		delete[] Participants[i];
	delete[] Participants;
	return 0;
}