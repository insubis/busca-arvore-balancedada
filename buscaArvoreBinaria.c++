#include <iostream>
#include <algorithm>

using namespace std;

// Estrutura para representar um nó na árvore AVL
struct NodoAVL {
    int valor;
    NodoAVL* esquerda;
    NodoAVL* direita;
    int altura;
};

// Funções para rotações
NodoAVL* rotacaoDireita(NodoAVL* nodo) {
    NodoAVL* novoRaiz = nodo->esquerda;
    nodo->esquerda = novoRaiz->direita;
    novoRaiz->direita = nodo;
    nodo->altura = 1 + max((nodo->esquerda ? nodo->esquerda->altura : 0), 
                           (nodo->direita ? nodo->direita->altura : 0));
    novoRaiz->altura = 1 + max((novoRaiz->esquerda ? novoRaiz->esquerda->altura : 0), 
                               nodo->altura);
    return novoRaiz;
}

NodoAVL* rotacaoEsquerda(NodoAVL* nodo) {
    NodoAVL* novoRaiz = nodo->direita;
    nodo->direita = novoRaiz->esquerda;
    novoRaiz->esquerda = nodo;
    nodo->altura = 1 + max((nodo->esquerda ? nodo->esquerda->altura : 0), 
                           (nodo->direita ? nodo->direita->altura : 0));
    novoRaiz->altura = 1 + max((novoRaiz->direita ? novoRaiz->direita->altura : 0), 
                               nodo->altura);
    return novoRaiz;
}

// Função para atualizar a altura de um nó
int altura(NodoAVL* nodo) {
    if (nodo == nullptr) return 0;
    return nodo->altura;
}

// Função para calcular o fator de balanceamento de um nó
int calcularBalanceamento(NodoAVL* nodo) {
    if (nodo == nullptr) return 0;
    return altura(nodo->esquerda) - altura(nodo->direita);
}

// Função para inserir um novo valor na árvore AVL
NodoAVL* inserir(NodoAVL* raiz, int valor) {
    if (raiz == nullptr) {
        NodoAVL* novoNodo = new NodoAVL();
        novoNodo->valor = valor;
        novoNodo->esquerda = nullptr;
        novoNodo->direita = nullptr;
        novoNodo->altura = 1;
        return novoNodo;
    }

    if (valor < raiz->valor) {
        raiz->esquerda = inserir(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
        raiz->direita = inserir(raiz->direita, valor);
    } else {
        // Valor já existe na árvore
        return raiz;
    }

    raiz->altura = 1 + max((raiz->esquerda ? raiz->esquerda->altura : 0), 
                           (raiz->direita ? raiz->direita->altura : 0));

    int balanceamento = calcularBalanceamento(raiz);

    // Caso 1: Rotação simples à direita
    if (balanceamento > 1 && valor < raiz->esquerda->valor) {
        return rotacaoDireita(raiz);
    }
    // Caso 2: Rotação simples à esquerda
    if (balanceamento < -1 && valor > raiz->direita->valor) {
        return rotacaoEsquerda(raiz);
    }
    // Caso 3: Rotação dupla à direita (esquerda-direita)
    if (balanceamento > 1 && valor > raiz->esquerda->valor) {
        raiz->esquerda = rotacaoEsquerda(raiz->esquerda);
        return rotacaoDireita(raiz);
    }
    // Caso 4: Rotação dupla à esquerda (direita-esquerda)
    if (balanceamento < -1 && valor < raiz->direita->valor) {
        raiz->direita = rotacaoDireita(raiz->direita);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}

// Função para percorrer a árvore em ordem (para teste)
void percorrerEmOrdem(NodoAVL* raiz) {
    if (raiz == nullptr) return;
    percorrerEmOrdem(raiz->esquerda);
    cout << raiz->valor << " ";
    percorrerEmOrdem(raiz->direita);
}

// Função principal
int main() {
    NodoAVL* raiz = nullptr;

    // Inserindo alguns valores 
    raiz = inserir(raiz, 10);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 30);
    raiz = inserir(raiz, 40);
    raiz = inserir(raiz, 50);
    raiz = inserir(raiz, 25);

    // Exibindo a árvore em ordem
    cout << "Árvore AVL em ordem: ";
    percorrerEmOrdem(raiz);
    cout << endl;

    return 0;
}
