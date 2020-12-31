#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <queue>
#include <list>

using namespace std;

namespace graph {
	struct Graph {
		int vertexNum;
		int** edges;
	};

	void createGraph(struct Graph* G, int V) {
		G->vertexNum = V;
		G->edges = (int**)malloc(V * sizeof(int*));
		for (int i = 0; i < V; i++) {
			G->edges[i] = (int*)malloc(V * sizeof(int));
			for (int j = 0; j < V; j++) {
				G->edges[i][j] = INT_MAX;
			}
			G->edges[i][i] = 0;
		}
	}

	void addEdge(struct Graph* G, int src, int dst, int weight) {
		G->edges[src][dst] = weight;
	}

	void minDistance(int mdist[], int vset[], int V) {
		int minVal = INT_MAX, minInd;
		for (int i = 0; i < V; i++) {
			if (vset[i] == 0 && mdist[i] < minVal) {
				minVal = mdist[i];
				minInd = i;
			}
		}
	}
}

namespace mygraph {
	enum class Color
	{
		White,
		Black,
		Gray,
	};
	struct Vertex{
		struct Vertex* prev;
		int distance;
		Color color;
		int value;
	};
	struct Edges {
		list<Vertex> edge;
	};

	void testcase() {
		Color white = Color::White;
		Color gray = Color::Gray;
		Color black = Color::Black;
		cout << static_cast<int>(white) << endl;
		cout << static_cast<int>(black) << endl;
		cout << static_cast<int>(gray) << endl;
	}
}
