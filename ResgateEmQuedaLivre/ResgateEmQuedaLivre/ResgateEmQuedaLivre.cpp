#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

typedef pair<double, pair<int, int>> par_arestas;
vector<par_arestas> lista_arestas;

typedef pair<double, double> par_ordenado;
vector<par_ordenado> coordenadas;

vector<int>seta_pessoas;

	
struct minimum_spanning_tree
{
	static void inicializaGrafo(int qtd_pessoas)
	{
		//atribui o valor 0 a qtd de pessoas ex: 3 pessoas com o valor zero
		seta_pessoas.assign(qtd_pessoas, 0);
		for (auto i = 0; i < qtd_pessoas; i++) seta_pessoas[i] = i;
	}

	static int findSet(int i)
	{
		return (seta_pessoas[i] == i) ? i : (seta_pessoas[i] = findSet(seta_pessoas[i]));
	}

	static void ligaSet(int i, int j)
	{
		seta_pessoas[findSet(i)] = findSet(j);
	}
	
	static bool mesmoSet(int i, int j)
	{
		return findSet(i) == findSet(j);
	}

	static void limpaTudo()
	{
		lista_arestas.clear();
		coordenadas.clear();
		seta_pessoas.clear();
	}
	
	static void printResultados(double distancia_minima)
	{
		cout << setprecision(2) << fixed;
		cout << distancia_minima<< endl << endl;
	}

	static void prim(int qtd_teste)
	{
		auto qtd_pessoas = 0;
		do
		{
			double distancia_minima = 0;
			cin >> qtd_pessoas;

			//inserindo as coordenadas das pessoas no vetor
			for(auto i = 0; i < qtd_pessoas; i++)
			{
				double x, y;
				cin >> x >> y;

				coordenadas.emplace_back(x, y);				
			}

			for(auto i = 0; i < qtd_pessoas; i++)
			{
				const pair<int, int> pessoa_a = coordenadas[i];
				for(auto j = 0; j < qtd_pessoas; j++)
				{
					if(j != i)
					{
						const pair<int, int> pessoa_b = coordenadas[j];
						const auto result_x = ((pessoa_b.first - pessoa_a.first) * (pessoa_b.first - pessoa_a.first));
						const auto result_y = ((pessoa_b.second - pessoa_a.second) * (pessoa_b.second - pessoa_a.second));

						//calculo distancia
						const auto distancia = sqrt(result_x + result_y);
						//insere na lista de arestas a distancia e o valor das arestas i, j;
						lista_arestas.emplace_back(distancia / 100.0, pair<int, int>( i, j));
					}
				}
			}
			sort(lista_arestas.begin(), lista_arestas.end());
			inicializaGrafo(qtd_pessoas);
			for (int i = 0; i < static_cast<int>(lista_arestas.size()); i++)
			{
				pair<double, pair<int, int> > topo = lista_arestas[i];

				if (!mesmoSet(topo.second.first, topo.second.second))
				{
					ligaSet(topo.second.first, topo.second.second);
					distancia_minima += topo.first;
				}
			}
			printResultados(distancia_minima);
			qtd_teste--;
			limpaTudo();
		} while (qtd_teste > 0);
	}
}typedef MinimumSpanningTree;

int main()
{
	int qtd_teste;
	cin >> qtd_teste;
	MinimumSpanningTree::prim(qtd_teste);
	MinimumSpanningTree::limpaTudo();
	
	return 0;
}