#include<iostream>
#include<climits>
using namespace std;
typedef int Vertextype;
typedef int Edgetype;
#define Max_size  100
#define Max_edge 200
#define M INT_MAX
class Graph
{
public:Edgetype arc[Max_size][Max_size];
	Vertextype Vertex[Max_size];
	int vertex_num;
	int edge_num;
};
void createGraph(Graph* G)
{
	G->vertex_num = 9;
	G->edge_num = 16;
	for (int i = 0; i < G->vertex_num; i++)
	{
		G->Vertex[i] = i;
	}
	for (int i = 0; i < G->vertex_num; i++)
	{
		for (int j = 0; j < G->vertex_num; j++)
		{
			if (i == j)
			{
				G->arc[i][j] = 0;
			}
			else
			{
				G->arc[i][j] = M;
			}
		}
		
		
	}G->arc[0][1] = 1;
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
		G->arc[7][8] = 4;for (int i = 0; i < G->vertex_num; i++)
		{
			for (int j = i; j < G->vertex_num; j++)
			{
				G->arc[j][i] = G->arc[i][j];
			}
		}
	
}
int choose(int distance[], int found[], int vertex_num)
{
	int min = M;
	int minpos = -1;
	for (int i = 0; i < vertex_num; i++)
	{
		if (distance[i] < min && found[i] == 0)
		{
			min = distance[i];
			minpos = i;
		}
	}
	return minpos;
}

void Dijkstra(Graph*G,int begin)
{
	int found[Max_size];//顶点是否走过
		int path[Max_size];//路径
		int distance[Max_size];//begin到每一个顶点的最短距离
		for (int i = 0; i < G->vertex_num; i++)
		{
			found[i] = 0;
			path[i] = -1;//同时也给path[begin]赋值-1了代表没有路径
			distance[i] = G->arc[begin][i];
		}
		found[begin] = 1;
		distance[begin] = 0;
		int next;
		for (int i = 1; i < G->vertex_num; i++)
		{
			next = choose(distance, found, G->vertex_num);//被choose选中的next才会置1
				found[next] = 1;
				for (int j = 0; j < G->vertex_num; j++)
				{
					if (found[j] == 0)
					{
						if (distance[next] != M && G->arc[next][j] != M)
						if (distance[next] + G->arc[next][j] < distance[j])
						{
							distance[j] = distance[next] + G->arc[next][j];
							path[j] = next;
						}
					}
			 }
	 	}
		for (int i = begin+1; i < G->vertex_num; i++)
		{
			cout << "v" << begin << "->" << "v" << i << ":" << distance[i] << endl;;
			int j = i;
			while (path[j] != -1)
			{
				cout << "v" << j << "<-";
				j = path[j];
			}
			cout << "v" << begin << endl;
		}
}
int main()
{
	Graph* G = new Graph;
	createGraph(G);
	Dijkstra(G, 1);
	return 0;
}