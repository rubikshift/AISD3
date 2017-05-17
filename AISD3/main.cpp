#include <iostream>
#include "Queue.h"
#define CHOSEN_BIKES_COUNT 0
#define NONE -1

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
		for (int i = 1; i < Participants[p][CHOSEN_BIKES_COUNT] + 1; i++)
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
	for (int i = 1; i < Participants[p][CHOSEN_BIKES_COUNT] + 1; i++)
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
	int x = (w > r) ? w : r;
	for (int i = 0; i < x; i++)
	{
		if (i < w)
			PairP[i] = NONE;
		if (i < r)
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
	int w, r, tmp, i = 0;
	
	std::ios_base::sync_with_stdio(0);
	std::cin >> w >> r;
	auto Q = new Queue(&w);
	int match = w;
	auto PairP = new int[w];
	auto PairB = new int[r];
	auto Dist = new int[w];
	auto Visited = new bool[w];
	auto Patricipants = new int*[w];
	while (!std::cin.eof())
	{
		std::cin >> tmp;
		Patricipants[i] = new int[tmp + 1];
		Patricipants[i][CHOSEN_BIKES_COUNT] = tmp;
		for (int q = 1; q < tmp + 1; q++)
		{
			std::cin >> Patricipants[i][q];
			Patricipants[i][q]--;
		}
		i++;
	}
	HopcroftKarp(Patricipants, PairP, PairB, Dist, Visited, w, r, Q);
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
		delete[] Patricipants[i];
	return 0;
}