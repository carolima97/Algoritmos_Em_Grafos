#include <stdio.h>
#include <limits.h>
#include <math.h>

#define bool      short
#define true      1
#define false     0

int minDistance(int dist[], int tam, bool sptSet[]) // Metodo que retorna o vertice com a menor distancia
{
	int min = INT_MAX, min_index;

	for (int v = 0; v < tam; v++)
		if (sptSet[v] == false &&
			dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}

int printPath(int** graph, int parent[], int j) // Metodo para obter a menor distancia ate o vertice "j"
{
	int soma = 0;
	if (parent[j] == -1)
		return 0;

	soma += graph[parent[j]][j];
	graph[parent[j]][j] = 0;

	soma += printPath(graph, parent, parent[j]); // Uso da recursividade para percorrer o caminho

	return soma;
}

void dijkstra(int** graph, int tam, int dist[], int parent[], int src, int dest) // Metodo de djikstra
{
	bool sptSet[tam];

	// Zera as distancias e vetor de parentesco
	for (int i = 0; i < tam; i++)
	{
		parent[0] = -1;
		dist[i] = INT_MAX;
		sptSet[i] = false;
	}

	dist[src] = 0;

	for (int count = 0; count < tam - 1; count++)
	{
		int u = minDistance(dist, tam, sptSet); // Obtem vertice com a menor distancia

		sptSet[u] = true;

		for (int v = 0; v < tam; v++)
			// Caso a distancia seja menor e o vertice nao tenha sido visitado ele puxa o proximo vertice e atualiza a distancia
			if (!sptSet[v] && graph[u][v] &&
				dist[u] + graph[u][v] < dist[v])
			{
				parent[v] = u;
				dist[v] = dist[u] + graph[u][v];
			}
	}
}

int main()
{
	int vertices = 0, arestas = 0, instancias = 0;

	//Executa enquanto existir entrada
	while (scanf("%d", &vertices) != EOF) {
		scanf("%d", &arestas);

		//Cria ponteiro para matriz do grafo, e vetores de distancia e parentesco
		int** graph;
		int dist[vertices];
		int parent[vertices];
		int somaTotal = 0;
		bool impossivel = false;

		graph = new int* [vertices];

		//Inicializa a matriz
		for (int i = 0; i < vertices; i++)
			graph[i] = new int[vertices];

		//Zera a matriz
		for (int i = 0; i < vertices; i++)
			for (int j = 0; j < vertices; j++)
				graph[i][j] = 0;

		//Le os parametros do voo
		for (int i = 0; i < arestas; i++) {
			int a = 0, b = 0, c = 0;
			scanf("%d", &a);
			scanf("%d", &b);
			scanf("%d", &c);
			graph[(a - 1)][(b - 1)] = c;
		}

		//Le os parametros de pessoas e vagas
		int pessoas = 0, vagas = 0, voo = 0, pessoasVoo = 0;
		scanf("%d", &pessoas);
		scanf("%d", &vagas);

		//Obtem quantidade de voos a serem realizados
		voo = ceil(pessoas / vagas);

		if (voo == 0)
			voo = 1;

		for (int i = 0; i < voo && !impossivel; i++) {
			//Calcula o numero de pessoas por voo
			pessoasVoo = (vagas > pessoas) ? pessoas : vagas;
			pessoas -= pessoasVoo;

			//Executa o metodo de djikstra para obter menor distancia
			dijkstra(graph, vertices, dist, parent, 0, 3);

			//Obtem menor distancia e caso ela seja 0 o caminho e impossivel
			int distancia = printPath(graph, parent, 3);
			impossivel = (distancia == 0);
			somaTotal += distancia * pessoasVoo;
		}

		instancias++;

		printf("Instancia %d\n\n", instancias);

		if (!impossivel)
			printf("%d\n\n\n\n", somaTotal);
		else
			printf("impossivel\n\n\n\n");
	}

	return 0;
}
