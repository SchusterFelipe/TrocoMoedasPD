#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> moedas = {4, 3, 1};
    cout << "=== Algoritmo de Troco Otimo ===\n";
    cout << "Moedas disponiveis (centavos): ";
    for (size_t i = 0; i < moedas.size(); i++) {
        cout << moedas[i];
        if (i < moedas.size() - 1) cout << ", ";
    }
    cout << "\n\n";

    int valor;
    cout << "Digite o valor do troco em centavos (0 para sair): ";
    while (cin >> valor) {
        if (valor == 0) break;

        vector<int> minMoedas(valor + 1, -1);
        minMoedas[0] = 0;

        // Calcula quantidade mínima de moedas para cada valor até o desejado
        for (int v = 1; v <= valor; v++) {
            int melhor = -1;
            for (int m : moedas) {
                if (v - m >= 0 && minMoedas[v - m] != -1) {
                    int tentativa = minMoedas[v - m] + 1;
                    if (melhor == -1 || tentativa < melhor)
                        melhor = tentativa;
                }
            }
            minMoedas[v] = melhor;
        }

        cout << "\nTroco para " << valor << " centavos:\n";

        // Vetor para contar quantas moedas de cada tipo foram usadas
        vector<int> contagem(moedas.size(), 0);

        // Reconstrução da solução
        int restante = valor;
        while (restante > 0) {
            for (size_t i = 0; i < moedas.size(); i++) {
                int m = moedas[i];
                if (restante - m >= 0 &&
                    minMoedas[restante - m] == minMoedas[restante] - 1) {

                    contagem[i]++;   // soma 1 moeda desse tipo
                    restante -= m;
                    break;
                }
            }
        }

        // Exibe a contagem organizada
        int totalMoedas = 0;
        for (size_t i = 0; i < moedas.size(); i++) {
            if (contagem[i] > 0) {
                cout << moedas[i] << " centavos: "
                     << contagem[i] << " moeda(s)\n";
                totalMoedas += contagem[i];
            }
        }

        cout << "Total de moedas usadas: " << totalMoedas << "\n";
        cout << "\nDigite outro valor (ou 0 para sair): ";
    }

    cout << "Programa finalizado.\n";
    return 0;
}
