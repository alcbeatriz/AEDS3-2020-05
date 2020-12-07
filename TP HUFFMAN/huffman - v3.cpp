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
	for (unsigned int i = 0; i < caracterList.size(); i++) /*unsigned int é um modificador para determinar que um tipo numérico
															inteiro é sem sinal. Ou seja, você só terá valores positivos nele.
		   	   	   	   	   	   	   	   	   	   	   	   	   	Um int vai de -2147483648 à 2147483647. Um unsigned int vai de 0 à 4294967295.*/
		if (no.caracter == caracterList.at(i).caracter) //at da o retorno da posição
		{
			caracterList.at(i).frequencia++;
			return false;
		}
	return true;
}

string textoCodificado(string text, vector<node> caracterList) //Para mostrar o texto codificado
{
	string data = " ";
	node aux;
	for (unsigned int i = 0; i < text.size(); i++) //percorre cada letra do texto
	{
		aux.caracter = tolower(text[i]); //Constroi um nó para cada letra do texto (tolower faz a conversão para minuscula
										// na hora de comparar as letras uma com as outras, assim A e a serão consideradas a mesma letra
		aux.frequencia = 0;
		aux.esquerda = NULL;
		aux.direita = NULL;
		for(unsigned int j = 0; j < caracterList.size(); j++)
		{
			if(aux.caracter == caracterList.at(j).caracter)
			{
				data += caracterList.at(j).code; //concatenação de String
			}
		}

	}
	return data; //retorna o texto
}

void mostraFrequencia(vector<node> caracterList) //mostra o vetor que contem as Letras e suas respectivas frequencias
{
	for (unsigned int i = 0; i < caracterList.size(); i++)
		cout << caracterList.at(i).caracter << ":" << caracterList.at(i).frequencia << "\t\n";
}

void mostrarCodigo(vector<node> caracterList) //mostra o vetor que contem as letras e seu codigo binario
{
	for (unsigned int i = 0; i < caracterList.size(); i++)
		cout << caracterList.at(i).caracter << ": " << caracterList.at(i).code << '\n';
}

void ordenaVetor(vector<node> &caracterList) //ordena o vetor, compara a quantidade de vezes que uma letra aparece e cria um hanking
{
	node aux;
	for (unsigned int i = 0; i < caracterList.size(); i++)
		for (unsigned int j = 0; j < caracterList.size(); j++)
			if (caracterList.at(i).frequencia > caracterList.at(j).frequencia)
			{ //fazer a troca dos valores armazenados para ordenar a frequencia, ex:3,2,1
				aux = caracterList.at(i);
				caracterList.at(i) = caracterList.at(j);
				caracterList.at(j) = aux;
			}
}

void countFrequencia(string txt, vector<node> &caracterList) //cria o vetor de frequencia
{
	node aux;

	for (unsigned int i = 0; i < txt.size(); i++) //percorre cada letra do texto
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

	for (unsigned int i = 0; i < caracterList.size(); i++) //Troca o caracter de espaçamento por algo visivel
															// para representar melhor o vazio
	{
		if (caracterList.at(i).caracter == " ")
			caracterList.at(i).caracter = "[]";
	}

	ordenaVetor(caracterList); //ordena o vetor
}

node *huffman(vector<node> caracterList) //arvore huffamn 
{
	node *no1, *no2;
	node *root;
	node aux1, aux2;

	while (caracterList.size() > 1) //faz a verifiicação pq o codigo reduz o tamanho do vetor
	{
		aux1 = caracterList.at(caracterList.size() - 1); //para receber os dois ultimos elementos do vetor
		aux2 = caracterList.at(caracterList.size() - 2);
		caracterList.pop_back(); //remove os dois ultimos elementos, pois ja estao alocados na arvore
		caracterList.pop_back();

		//criamos dois nós, no1 e no2 para aloca-los na arvore
		no1 = new node;
		no1->caracter = aux1.caracter;
		no1->frequencia = aux1.frequencia;
		no1->direita = aux1.direita;
		no1->esquerda = aux1.esquerda;

		no2 = new node;
		no2->caracter = aux2.caracter;
		no2->frequencia = aux2.frequencia;
		no2->direita = aux2.direita;
		no2->esquerda = aux2.esquerda;

		//cria o root, para ser formado pela juncao dos dois menores valores do vetor
		root = new node;
		root->caracter = no2->caracter + no1->caracter;
		root->frequencia = no2->frequencia + no1->frequencia;
		root->esquerda = no2;
		root->direita = no1;

		caracterList.push_back(*root); //adiciona o elemento apos a juncao dos menores
		ordenaVetor(caracterList);        //ordena
	}

	return root; //retorna a raiz
}

void setaValor(vector<node> &caracterList, node root) //coloca o valor do codigo de cada letra da arvore no vetor
{
	for (unsigned int i = 0; i < caracterList.size(); i++)
		if (caracterList.at(i).caracter == root.caracter)
			caracterList.at(i).code = root.code;
}

void coder(vector<node> &caracterList, node *root) //setar o valor 0 ou 1
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
	setlocale(LC_ALL, "Portuguese"); //ler acentuacao
	string text = "Algoritmo de Huffman"; //texto a ser verificado
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
	while (op > 0 && op < 4)
	{

		menu();
		cin >> op;
		switch (op)
		{
		case 1:
			system("cls");

			cout << "Texto a ser comprimido: " << endl << "\n" << text << "\n" << endl;
			cout << "Texto comprimido: " << endl << "\n" << data << "\n" << endl;

			cout << "Tamanho original do texto: " << normalsize << " bits" << endl;
			cout << "Tamanho comprimido: " << compressedsize  << " bits" << endl;
			cout << "O tamanho comprimido é " << percentual << "% menor que o tamanho original ";

			break;
		case 2:
			system("cls");
			mostraFrequencia(caracterList);
			break;

		case 3:
			system("cls");
			mostrarCodigo(caracterList);
			break;

		case 4:
			return 0;
			break;

		}
	}
}