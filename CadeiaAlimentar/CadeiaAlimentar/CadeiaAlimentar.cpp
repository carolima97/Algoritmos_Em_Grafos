#include <iostream>
using namespace std;

#define BOOL true
#define TRUE 1
#define FALSE 0

struct grafos
{
	static void printResultado(bool bolada)
	{
		if (bolada) cout << "Bolada";
		else cout << "Não Bolada";
	}

	static void processa(int qtd_especies, int n_relacoes)
	{
		auto bolada = false;
		bool matriz_cadeia[qtd_especies][qtd_especies];

		//inicializa matriz
		for (auto i = 0; i < qtd_especies; i++)
		{
			for (auto j = 0; j < qtd_especies; j++)
			{
				matriz_cadeia[i][j] = false;
			}
		}

		//leitura das relacoes
		for (auto i = 0; i < n_relacoes; i++)
		{
			int u, v;
			cin >> u >> v;
			matriz_cadeia[(u - 1)][v - 1] = true;
		}

		//verifica requisitos para bolada e nao bolada
		for (auto i = 0; i < qtd_especies; i++)
		{
			for (auto j = 0; j < qtd_especies; j++)
			{
				if ((!bolada) && (matriz_cadeia[i][j]) && (matriz_cadeia[i][j] == matriz_cadeia[j][i]))
					bolada = true;
			}
		}
		printResultado(bolada);
	}
}typedef grafos;

int main()
{
	int qtd_especies, n_relacoes;
	cin >> qtd_especies >> n_relacoes;
	grafos::processa(qtd_especies, n_relacoes);
	return 0;
}
