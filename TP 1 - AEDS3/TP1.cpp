#include <iostream>
#include <locale.h>
#include<windows.h>
using namespace std;

//nó: conteudo(informacao)  ponteiro para a esquerda e direita
class No
{
private:
	No *esquerda, *direita;
	int informacao;
//o conteudo pode receber esquerda ou direita e ambos são inicializados vazios
public:
	No(int informacao)
	{
		this->informacao = informacao;
		esquerda = NULL;
		direita = NULL;
	}
//para conseguir retornar o conteudo da informacao
	int getinformacao()
	{
		return informacao;
	}

	// funções getters e setters

	No* getesquerda()
	{
		return esquerda;
	}

	No* getdireita()
	{
		return direita;
	}

	void setesquerda(No *noAtual)
	{
		esquerda = noAtual;
	}

	void setdireita(No *noAtual)
	{
		direita = noAtual;
	}
};
//definição da arvore
class Arvore
{
private:
	No *raiz;
//inicialização da raiz da arvore como null
public:
	Arvore()
	{
		raiz = NULL;
	}
//funções de inserção
	void inserir(int informacao)
	{
		if(raiz == NULL) // verifica se a árvore está vazia
			raiz = new No(informacao); // cria um novo nó
		else// se nao ele vai para o proximo
			inserirAux(raiz, informacao);
	}
//essa função vai preencher nos casos em que a arvore em questão não estiver vazia, entao vai comparar os valores e inserir direita ou esquerda
	void inserirAux(No *noAtual, int informacao)
	{
		// se for menor, então insere à esquerda
		if(informacao < noAtual->getinformacao())
		{
			// verifica se a esquerda é null
			if(noAtual->getesquerda() == NULL)
			{
				No *novo_no = new No(informacao);
				noAtual->setesquerda(novo_no); // seta o novo_no à esquerda
			}
			else
			{
				// senão, continua percorrendo recursivamente
				inserirAux(noAtual->getesquerda(), informacao);
			}
		}
		// se for maior, então insere à direita
		else if(informacao > noAtual->getinformacao())
		{
			// verifica se a direitaeita é null
			if(noAtual->getdireita() == NULL)
			{
				No *novo_no = new No(informacao);
				noAtual->setdireita(novo_no); // seta o novo_no à direita
			}
			else
			{
				// senão, continua percorrendo recursivamente
				inserirAux(noAtual->getdireita(), informacao);
			}
		}
		// se for igual, não vai inserir
		// não pode existir 2 informacaos iguais, quis definir assim pra facilitar.
	}

	No* getRaiz()
	{
		return raiz;
	}
//função em ordem
	void emOrdem(No* no_atual)
	{
		if(no_atual != NULL) //verifica se o nó atual existe
		{
			emOrdem(no_atual->getesquerda()); //passa para o filho da esquerda
			cout << no_atual->getinformacao() << " ";//apresenta o valor visitado
			emOrdem(no_atual->getdireita());//passa para o filho a direita
		}
	}
//função pré-ordem
	void exibirPreOrdem(No* no_atual)
	{
		if(no_atual != NULL) //mesmo teste anterior
		{
			cout << no_atual->getinformacao() << " "; //apresenta o valor do elemento visitado
			exibirPreOrdem(no_atual->getesquerda());//passa para o filho a esquerda
			exibirPreOrdem(no_atual->getdireita());//passa para o filho a direita

		}
	}
//função pós-ordem
	void exibirPosOrdem(No* no_atual)
	{
		if(no_atual != NULL)//mesmo teste anterior
		{
			exibirPosOrdem(no_atual->getesquerda());//passa para o filho da esquerda
			exibirPosOrdem(no_atual->getdireita());//passa para o filho a direita
			cout << no_atual->getinformacao() << " ";// passa por toda a árvore, e só depois vir fazendo a apresentação dos elementos visitados
		}
	}

};

int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "Portuguese"); //para a leitura acentuada das palavras
	Arvore arv;


// insere as informações: não consegui pegar do teclado :(
	arv.inserir(10);
	arv.inserir(3);
	arv.inserir(5);
	arv.inserir(2);
	arv.inserir(13);
	arv.inserir(11);
	arv.inserir(23);
	arv.inserir(31);
	arv.inserir(19);
	arv.inserir(17);
	arv.inserir(8);
	

	// percorre em ordem iniciando da raiz
	cout << "Olá Ana! vou inserir os valores para você\n" << endl;

	cout << "Em ordem:\n";
	arv.emOrdem(arv.getRaiz());
	cout << "\n\n";
	Sleep(500); //para deixar mais lento, a arvore tem um poder muito grande e para printar na tela mais lentamente eu coloquei essa função
	cout << "Pré-ordem:\n";
	arv.exibirPreOrdem(arv.getRaiz());
	cout << "\n\n";
	Sleep(500);
	cout << "Pós-ordem:\n";
	arv.exibirPosOrdem(arv.getRaiz());

	return 0;
}
