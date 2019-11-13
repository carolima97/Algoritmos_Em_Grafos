#include <iostream>

using namespace std;

#define BOOL      short
#define TRUE      1
#define FALSE     0

struct grafos
{
	static void processa(const int qtd_casos)
	{
		//para cada caso, faça
		for (auto i = 0; i < qtd_casos; i++) {
			auto qtd_vertices = 0,
				qtd_arestas_originais = 0,
				qtd_arestas_inseridas = 0,
				qtd_cores = 0;

			BOOL existe = TRUE;

			cin >> qtd_vertices;
			cin >> qtd_arestas_originais;
			cin >> qtd_arestas_inseridas;
			cin >> qtd_cores;

			int vet_cor[4];
			BOOL matriz_adjacencia[4][4];

			// inicializa vetor de cores
			for (auto j = 0; j < qtd_vertices; j++) {
				vet_cor[j] = 0;
			}

			// inicializa matriz de adjacencia
			for (auto j = 0; j < qtd_vertices; j++) {
				for (auto k = 0; k < qtd_vertices; k++) {
					matriz_adjacencia[j][k] = FALSE;
				}
			}

			// Le a cor de cada vertice
			for (auto i = 0; i < qtd_vertices; i++) {
				auto n_cor = 0;
				cin >> n_cor;
				vet_cor[i] = n_cor;
			}

			// Le a aresta e verifica cor dos vertices que ela liga
			for (auto j = 0; j < qtd_arestas_originais && existe; j++) {
				auto a = 0, b = 0;
				cin >> a;
				cin >> b;
				a -= 1;
				b -= 1;
				if (vet_cor[a] == vet_cor[b])
					existe = FALSE;
				else
					matriz_adjacencia[a][b] = matriz_adjacencia[b][a] = TRUE;
			}

			if (existe) {
				for (auto j = 0; j < qtd_vertices && existe; j++) {
					auto conexoes = 0;
					existe = FALSE;
					for (auto k = 0; k < qtd_vertices; k++) {
						if (vet_cor[j] != vet_cor[k] && matriz_adjacencia[j][k] == FALSE && qtd_arestas_inseridas > 0) { // Realiza as ligacoes restantes
							matriz_adjacencia[j][k] = matriz_adjacencia[k][j] = TRUE;
							qtd_arestas_inseridas--;
						}
						if (matriz_adjacencia[j][k]) // Identifica se o grafo é conexo
							conexoes++;
					}
					existe = (conexoes > 0);
				}

				if (qtd_arestas_inseridas == 0 && existe)
					cout << "Y\n\n";
				else
					cout << "N\n\n";
			}
			else
				cout << "N\n\n";
		}
	}
}typedef grafos;

int main()
{
	auto qtd_casos = 0;
	cin >> qtd_casos;
	grafos::processa(qtd_casos);
	return 0;
}
