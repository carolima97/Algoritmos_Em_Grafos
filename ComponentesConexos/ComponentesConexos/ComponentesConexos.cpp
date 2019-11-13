#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void conexos(int** grafo, int vertices) {
	vector <int> elem;
	int esta_na_pilha[vertices];
	int qtd = -1;
	int ini = 0;
	int pilha[vertices];
	int topo = -1;
	int cont = 0;
	char a;

	// inicializa status
	for (int i = 0; i < vertices; ++i)
		esta_na_pilha[i] = 0;


	for (int j = 0; j < vertices; ++j) {
		if (esta_na_pilha[j] == 0) {
			esta_na_pilha[j] = 1;
			pilha[++topo] = j;

			while (topo != -1) {
				ini = pilha[topo--];
				elem.push_back(ini);
				for (int i = 0; i < vertices; ++i) {
					if (grafo[ini][i] && esta_na_pilha[i] == 0) {
						pilha[++topo] = i;
						esta_na_pilha[i] = 1;
					}
				}
			}

			sort(elem.begin(), elem.end());

			for (int i = 0; i < elem.size(); ++i) {
				a = elem[i] + 97;
				cout << a << ",";
			}
			cout << endl;
			elem.clear();
			cont++;
		}
	}

	cout << cont << " connected components" << endl;


}

int main() {

	char c1, c2;
	int n, v, e, x, y;

	cin >> n;

	for (int i = 1; i <= n; ++i) {
		cin >> v >> e;

		// inicializa grafo
		int** grafo = new int* [v];
		for (int j = 0; j < v; ++j) {
			grafo[j] = new int[v];
			for (int k = 0; k < v; ++k)
				grafo[j][k] = 0;
		}

		// leitura de valores
		for (int j = 0; j < e; ++j) {
			cin >> c1 >> c2;
			x = c1 - 97;
			y = c2 - 97;
			grafo[x][y] = 1;
			grafo[y][x] = 1;
		}
		cout << "Case #" << i << ":" << endl;
		conexos(grafo, v);
		cout << endl;

	}
}
