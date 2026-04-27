#include<iostream>
#include<algorithm>
#include<climits>
using namespace std;
typedef char Vertextype;
typedef int Edgetype;
#define Max_size 100
#define M INT_MAX
class Graph
{
public:
	Vertextype vertex[Max_size];
	Edgetype arc[Max_size][Max_size];
	int vertex_num;
	int edge_num;
};
class Edge
{
public:int begin;
	int end;
	int weight;
};
void createGraph(Graph* G)
{
	G->edge_num = 15;
	G->vertex_num = 9;
	G->vertex[0] = 'A';
	G->vertex[1] = 'B';
	G->vertex[2] = 'C';
	G->vertex[3] = 'D';
	G->vertex[4] = 'E';
	G->vertex[5] = 'F';
	G->vertex[6] = 'G';
	G->vertex[7] = 'H';
	G->vertex[8] = 'I';
	for (int i = 0; i < G->vertex_num; i++)
	{
		for (int j = 0; j < G->vertex_num; j++)
		{
			G->arc[i][j] = M;
			if (i == j)
			{
				G->arc[i][j] = 0;
			}
		}
	}
	G->arc[0][1] = 10;
	G->arc[0][5] = 11;
	G->arc[1][2] = 18;
	G->arc[1][6] = 16;
	G->arc[1][8] = 12;
	G->arc[2][3] = 22;
	G->arc[2][8] = 8;
	G->arc[3][4] = 20;
	G->arc[3][6] = 24;
	G->arc[3][7] = 16;
	G->arc[3][8] = 21;
	G->arc[4][5] = 26;
	G->arc[4][7] = 7;
	G->arc[5][6] = 17;
	G->arc[6][7] = 19;
	for (int i = 0; i < G->vertex_num; i++)
	{
		for (int j = 0; j < G->vertex_num; j++)
		{
			G->arc[j][i] = G->arc[i][j];
		}
	}
}
void swap(Edge* edges, int i, int j)
{
	int temp;
	temp = edges[i].begin;
	edges[i].begin = edges[j].begin;
	edges[j].begin = temp;
	temp = edges[i].end;
	edges[i].end = edges[j].end;
	edges[j].end=temp;
	temp = edges[i].weight;
	edges[i].weight = edges[j].weight;
	edges[j].weight = temp;
}
void sortEdges(Edge edges[], int edge_num)
{
	for (int i = 0; i < edge_num; i++)
	{
		for (int j = i + 1; j < edge_num; j++)
		{
			if (edges[i].weight > edges[j].weight)
			{
				swap(edges, i, j);
			}
		}
	}
}
int parent[Max_size];
int find(int* parent, int index)
{
	while (parent[index] > 0)
	{
		index = parent[index];
	}
	return index;
}//找祖宗节点，防止闭环
void kruskal(Graph*G)
{
	Edge edges[Max_size];
	int k = 0;
	for (int i = 0; i < G->vertex_num; i++)
	{
		for (int j = i + 1; j < G->vertex_num; j++)//避免取到对角线
		{
			if (G->arc[i][j] < M)
			{
				edges[k].begin = i;
				edges[k].end = j;
				edges[k].weight = G->arc[i][j];
				k++;
			}
		}
	}
	sortEdges(edges, G->edge_num);
	for (int i = 0; i < G->vertex_num; i++)
	{
		parent[i] = 0;
	}
	int m = 0;
	int n = 0;
	for (int i = 0; i < G->edge_num; i++)
	{
		m = find(parent, edges[i].begin);
		n = find(parent, edges[i].end);
		if (n != m)//如果两个边不重合可以选这条边

		{
			parent[n] = m;//不同根就融合
			cout << "(" << G->vertex[edges[i].begin] << G->vertex[edges[i].end] <<")"<<edges[i].weight << endl;//输出结果
		}
	}
}
int main()
{
	Graph* G = new Graph;
	createGraph(G);
	kruskal(G);
	return 0;
}