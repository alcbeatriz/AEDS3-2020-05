#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
using namespace std;

class node
{
public:
	int frequencia;
	string caracter, code;
	node *esquerda, *direita;
};

bool verificaNo(node no, vector<node> &caracterList) //verifica se o nó recebido ja esta presente no vetor
{
	for (int i = 0; i < caracterList.size(); i++)
		if (no.caracter == caracterList.at(i).caracter)
		{
			caracterList.at(i).frequencia++;
			return false;
		}
	return true;
}

string textoCodificado(string text, vector<node> caracterList)
{
	string data = " ";
	node aux;
	for (int i = 0; i < text.size(); i++) //percorre cada letra do texto
	{
		aux.caracter = tolower(text[i]); //Constroi um nó para cada letra do texto
		aux.frequencia = 0;
		aux.esquerda = NULL;
		aux.direita = NULL;
		for(int j = 0; j < caracterList.size(); j++)
		{
			if(aux.caracter == caracterList.at(j).caracter)
			{
				data += caracterList.at(j).code;
			}
		}

	}
	return data;
}

void mostraFrequencia(vector<node> caracterList) //mostra o vetor que contem as Letras e suas respectivas frequencias
{
	for (int i = 0; i < caracterList.size(); i++)
		cout << caracterList.at(i).caracter << ":" << caracterList.at(i).frequencia << "\t\n";
}

void mostrarVetorAux(vector<node> caracterList) //mostra o vetor que contem as letras e seu codigo binario
{
	for (int i = 0; i < caracterList.size(); i++)
		cout << caracterList.at(i).caracter << ": " << caracterList.at(i).code << '\n';
}

void ordenaVetor(vector<node> &caracterList) //ordena o vetor
{
	node aux;
	for (int i = 0; i < caracterList.size(); i++)
		for (int j = 0; j < caracterList.size(); j++)
			if (caracterList.at(i).frequencia > caracterList.at(j).frequencia)
			{
				aux = caracterList.at(i);
				caracterList.at(i) = caracterList.at(j);
				caracterList.at(j) = aux;
			}
}

void countFrequencia(string txt, vector<node> &caracterList) //cria o vetor de frequencia
{
	node aux;

	for (int i = 0; i < txt.size(); i++) //percorre cada letra do texto
	{
		aux.caracter = tolower(txt[i]); //aux recebe cada letra
		aux.frequencia = 0;                 //condicoes iniciais
		aux.esquerda = NULL;              //condicoes iniciais
		aux.direita = NULL;             //condicoes iniciais

		if (verificaNo(aux, caracterList)) //se a letra nao extiste, ele a aloca no vetor
		{
			aux.frequencia++;
			caracterList.push_back(aux);
		}
	}

	for (int i = 0; i < caracterList.size(); i++) //Troca o caracter de espaçamento por algo visivel
	{
		if (caracterList.at(i).caracter == " ")
			caracterList.at(i).caracter = "[]";
	}

	ordenaVetor(caracterList); //ordena o vetor
}

node *huffman(vector<node> caracterList) //faz huffamn
{
	node *min1, *min2;
	node *root;
	node aux1, aux2;

	while (caracterList.size() > 1) //faz essa verificaÃ§Ã£o pq nosso codigo reduz o tamanho do vetor a cada laÃ§o
	{
		aux1 = caracterList.at(caracterList.size() - 1); //para receber os dois ultimos elementos do vetor
		aux2 = caracterList.at(caracterList.size() - 2);

		//criamos dois nÃ³s, min1 e min2 para aloca-los na arvore
		min1 = new node;
		min1->caracter = aux1.caracter;
		min1->frequencia = aux1.frequencia;
		min1->direita = aux1.direita;
		min1->esquerda = aux1.esquerda;

		min2 = new node;
		min2->caracter = aux2.caracter;
		min2->frequencia = aux2.frequencia;
		min2->direita = aux2.direita;
		min2->esquerda = aux2.esquerda;

		//cria o root, para ser formado pela junÃ§Ã£o dos dois menores valores do vetor
		root = new node;
		root->caracter = min2->caracter + min1->caracter;
		root->frequencia = min2->frequencia + min1->frequencia;
		root->esquerda = min2;
		root->direita = min1;

		caracterList.pop_back(); //remove os dois ultimos elementos, pois ja estao alocados na arvore
		caracterList.pop_back();

		caracterList.push_back(*root); //adiciona o elemento apos a juncao dos menores
		ordenaVetor(caracterList);        //ordena
	}

	return root;
}

void setaValor(vector<node> &caracterList, node root) //coloca o valor do codigo de cada letra da arvore no vetor
{
	for (int i = 0; i < caracterList.size(); i++)
		if (caracterList.at(i).caracter == root.caracter)
			caracterList.at(i).code = root.code;
}

void coder(vector<node> &caracterList, node *root)
{
	if (root->esquerda != NULL || root->direita != NULL) // nao no folha
	{
		root->direita->code = root->code + "1"; //se o node pra direita, codigo recebe 1
		root->esquerda->code = root->code + "0";  // se node pra esquerda codigo recebe 0

		coder(caracterList, root->esquerda);
		coder(caracterList, root->direita);
	}

	setaValor(caracterList, *root); //preenche o vetor
}

void menu()
{
	cout << "\n\nAlgoritmo de Huffman - Testes\n\n"
		 << "\t1) Executar Huffman\n"
		 << "\t2) Mostrar letras e frequência\n"
		 << "\t3) Mostrar letras e seus códigos\n"
		 << "\t4) Sair\n"
		 << "\nEscolha uma opcão: ";
}

int main()
{
	setlocale(LC_ALL, "Portuguese");
	string text = "algoritmo de huffman";
	vector<node> caracterList;
	node *root;
	int op = 1;


	countFrequencia(text, caracterList);
	root = huffman(caracterList);
	coder(caracterList, root);
	string data = textoCodificado(text, caracterList);
	int normalsize = text.size() * 8;
	int compressedsize = data.size();
	int percentual = 100.0 - (compressedsize * 100.0 / normalsize);
	while (op > 0 && op < 5)
	{

		menu();
		cin >> op;
		switch (op)
		{
		case 1:
			system("cls");

			cout << "Texto a ser comprimido: " << endl << "\n" << text << "\n" << endl;
			cout << "Texto comprimido: " << endl << "\n" << data << "\n" << endl;

			cout << "Tamanho original do texto: " << normalsize <<" bits"<< endl;
			cout << "Tamanho comprimido: " << compressedsize  <<" bits"<< endl;
			cout << "O tamanho comprimido é " << percentual << "% menor que o tamanho original ";

			break;
		case 2:
			system("cls");
			mostraFrequencia(caracterList);
			break;

		case 3:
			system("cls");
			mostrarVetorAux(caracterList);
			break;

		case 4:
			return 0;
			break;

		}
	}
}