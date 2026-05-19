#include<iostream>
#include<climits>
using namespace std;

#define  Max_size 100
#define M INT_MAX

typedef  int vertextype;
typedef int edgetype;

class Graph
{
public:
	vertextype vertex[Max_size];
	edgetype arc[Max_size][Max_size];
	int vertex_num;
	int edge_num;
};

void createGraph(Graph* G)
{
	G->vertex_num = 9;
	G->edge_num = 16;

	for (int i = 0; i < G->vertex_num; i++)
	{
		G->vertex[i] = i;
	}

	for (int i = 0; i < G->vertex_num; i++)
	{
		for (int j = 0; j < G->vertex_num; j++)
		{
			if (i == j)
				G->arc[i][j] = 0;
			else
				G->arc[i][j] = M;
		}
	}

	// 边赋值
	G->arc[0][1] = 1;
	G->arc[0][2] = 5;
	G->arc[1][2] = 3;
	G->arc[1][3] = 7;
	G->arc[1][4] = 5;
	G->arc[2][4] = 1;
	G->arc[2][5] = 7;
	G->arc[3][4] = 2;
	G->arc[3][6] = 3;
	G->arc[4][5] = 3;
	G->arc[4][6] = 6;
	G->arc[4][7] = 9;
	G->arc[5][7] = 5;
	G->arc[6][7] = 2;
	G->arc[6][8] = 7;
	G->arc[7][8] = 4;

	// 无向图对称
	for (int i = 0; i < G->vertex_num; i++)
	{
		for (int j = i; j < G->vertex_num; j++)
		{
			G->arc[j][i] = G->arc[i][j];
		}
	}
}

void Floyd(Graph* G)
{
	int path[Max_size][Max_size];
	int distance[Max_size][Max_size];

	// 初始化（只需要一次）
	for (int i = 0; i < G->vertex_num; i++)
	{
		for (int j = 0; j < G->vertex_num; j++)
		{
			distance[i][j] = G->arc[i][j];
			path[i][j] = j;
		}
	}

	// ? 正确 Floyd 三层循环：k → i → j
	for (int k = 0; k < G->vertex_num; k++)
	{
		for (int i = 0; i < G->vertex_num; i++)
		{
			for (int j = 0; j < G->vertex_num; j++)
			{
				// ? 防止溢出 + 正确公式
				if (distance[i][k] != M && distance[k][j] != M && distance[i][j] > distance[i][k] + distance[k][j])
				{
					distance[i][j] = distance[i][k] + distance[k][j];
					path[i][j] = path[i][k];
				}
			}
		}
	}

	// 输出路径
	int k;
	for (int i = 0; i < G->vertex_num; i++)
	{
		for (int j = i + 1; j < G->vertex_num; j++)
		{
			cout << "v" << i << "->" << "v" << j << ":" << distance[i][j] << "  path:v" << i;
			k = path[i][j];
			while (k != j)
			{
				cout << "->v" << k;
				k = path[k][j];
			}
			cout << "->v" << j << endl;
		}
		cout << endl;
	}
}

int main()
{
	Graph* G = new Graph;
	createGraph(G);
	Floyd(G);
	delete G;
	return 0;
}