/**
 * referencias principais:
 * https://www.youtube.com/watch?v=I5cl39jdnow&ab_channel=LinguagemCPrograma%C3%A7%C3%A3oDescomplicada
 * https://www.youtube.com/watch?v=Au-6c55J90c&list=PL8iN9FQ7_jt6_lLU6bAlq0gCB3FwvDvee&index=1&ab_channel=LinguagemCPrograma%C3%A7%C3%A3oDescomplicada
 * https://www.youtube.com/watch?v=3zmjQlJhBLM&ab_channel=RodrigoGuerra
 * https://www.microsoft.com/pt-br/microsoft-365/visio/flowchart-software
 * https://www.youtube.com/watch?v=1HkWqH7L2rU&ab_channel=LinguagemCPrograma%C3%A7%C3%A3oDescomplicada
 * 
 */




#include <iostream> //manipula��o de fluxo de dados padr�o - entrada e saida
#include <stdlib.h> //manupula��o de fun��es envolvendo aloca��o de mem�ria, controle de processos, convers�es etc.
#include <locale.h> //acentua��o
using namespace std; //para definir um "espa�o de Nomes", evitar duplicidade

//n�: conteudo (informa��o), ponteiro para a esquerda e direita e variavel para a altura.
//cria�ao do n�
struct Node
{
	int informacao;
	Node *esquerda;
	Node *direita;
	int altura;
};
//defini��o da arvore, inicializa��o da raiz como null
struct Arv
{
	Arv() //Construtor
	{
		root = NULL;
	}
//libera��o do valor da raiz
	~Arv() //destrutor
	{
		root = libera(root);
	}

	Node *root;

	Node *Inserir(Node *aux, int valor); //Inserir valor na arvore

	Node *Remover(Node *aux, int valor); //Remover valor na arvore
	Node *Pesquisar (Node *aux); //Pesquisar na subarvore a direita o menor valor

	bool Pesquisar2(Node *aux, int valor);

	int Altura(Node *aux); //mostrar a altura do n�
	int bigger_alt(int alt_esquerda, int alt_direita); //Conferir se a altura a direita ou esquerda do n� definir o maior
	int fatorBalanceamento(Node *aux); //Fator de Balanceamento
	Node *RotacaoDE(Node *aux); //rota��o (-2) -> (1).
	Node *rotEE(Node *aux); //rota��o (2) -> (1).
	Node *rotDD(Node *aux); //rota��o (-2) -> (-1).
	Node *RotacaoED(Node *aux); //rota��o (2) -> (-1).

	void ImprimirPreOrdem(Node *aux); // foi escolhido pre-ordem pois imprime os valores na ordem que pegamos da atividade anterior
	void *search(Node *aux, int valor);  //pesquisar

	Node *libera(Node *root); //liberar
};

Node *Arv ::Inserir(Node *aux, int valor)
{

	//percorre a arvore at� encontrar um n� vazio para inserir um valor
	if (aux == NULL) // se null
	{
		aux = new Node; //inicializa o n�
		aux->direita = NULL; // seta direita como null
		aux->esquerda = NULL; //seta esquerda como Null
		aux->informacao = valor; // recebe o valor
		aux->altura = 0; //recebe a altura como 0
		if (root == NULL) //se o n� for Null
			root = aux; // recebe o valor guardado no auxiliar
	}
	else if (valor < aux->informacao) //se o valor para inserir for menor que o valor do n�
	{
		aux->esquerda = Inserir(aux->esquerda, valor); //ele insere a esquerda
	}
	else if (valor > aux->informacao) //se nao ele insere a direita
	{
		aux->direita = Inserir(aux->direita, valor);
	}
	//atualiza a altura dos n�s
	aux->altura = bigger_alt(Altura(aux->esquerda), Altura(aux->direita)) + 1;

	//Confere se a arvore est� balanceada, se nao, faz a rota��o
	if (fatorBalanceamento(aux) == 2) // se o fator de balanceamento for igual a 2
	{
		if (fatorBalanceamento(aux->esquerda) == 1) // se o fator de balanceamento for igual a 1 quando o auxiliar aponta para a esquerda
		{
			aux = rotEE(aux); // rota��o direita direita
		}
		else
		{
			aux = RotacaoED(aux); //rota��o esquerda direita
		}
	}
	else if (fatorBalanceamento(aux) == -2) //se o fator de balanceamento for igual -2 (para cofonferir os valores a esquerda)
	{
		if (fatorBalanceamento(aux->direita) == -1) //se o fator de balanceamento for igual a -1 quando o auxiliar aponta para a direita
		{
			aux = rotDD(aux); //rota��o esquerda esquerda
		}
		else
		{
			aux = RotacaoDE(aux); //rota��o direita esquerda
		}
	}
	return aux;
}

//fun��o de remover
Node *Arv ::Remover(Node *aux, int valor)
{

	if (aux == NULL) //se auxiliar for igual a null
	{
		return NULL; //retorna null
	}

	//caminha na arvore at� encontrar o valor ser� removido
	if (valor == aux->informacao)
	{
		//Se o n� a ser removido possuir 1 ou zero filhos
		if (aux->direita == NULL || aux->esquerda == NULL)
		{
			//n� recebe auxiliar
			Node *Node = aux;
			if (aux->esquerda != NULL) //se auxiliar apontando para a esquerda for diferente de null
			{
				aux = aux->esquerda; // o auxiliar recebe o valor da esquerda

			}
			else
			{
				aux = aux->direita; //se nao ele recebe o valor da direita
			}

			free (Node); //libera��o do no
		}
		//Se o n� a ser removido possuir dois filhos
		else
		{
			Node *No; //inicializa��o
			No = Pesquisar(aux->direita);  //no recebe a pesquisa a direita
			aux->informacao = No->informacao; //informa��o vai receber a nova informa��o do no
			aux->direita = Remover(aux->direita, aux->informacao); //remove a informa��o a direita

		}
	}
	else if (valor < aux->informacao) //se valor for menor que a informa��o apontada pelo aux
	{
		aux->esquerda = Remover(aux->esquerda, valor); //� removido o valor a esqueda
	}
	else if (valor > aux->informacao) //se o valor for maior que a informa��o
	{
		aux->direita = Remover(aux->direita, valor); //� removido o valor da direita
	}


	//Confere se a Arv est� balanceada, se n�o, faz a rota��o
	if (fatorBalanceamento(aux) == 2) //se o fator de balanceamento for igual a 2
	{
		if (fatorBalanceamento(aux->esquerda) == 1) //analisa a esquerda, se � igual a 1
		{
			aux = rotEE(aux); //faz a rota��o direita direita
		}
		else
		{
			aux = RotacaoED(aux); //se nao, faz a rota��o esquerda direita
		}
	}
	else if (fatorBalanceamento(aux) == -2) //se o fator de balanceamento for igual a -1 (para conferir o lado esquerdo)
	{
		if (fatorBalanceamento(aux->direita) == -1) //analisa a direita. se � igual a -1
		{
			aux = rotDD(aux); //faz a rota��o a esquerda esquerda
		}
		else
		{
			aux = RotacaoDE(aux); //se nao. faz a rota��o direita esquerda;
		}
	}


	return aux; //retorna o valor aux
}

Node * Arv :: Pesquisar (Node *aux) //pesquisar
{
	Node *Node1 = aux; //node 1 vai receber o valor auxiliar
	Node *Node2 = aux->esquerda; // node 2 vai apontar o auxiliar a esquerda

	while (Node2 != NULL) //se o node2 for diferente de null
	{
		Node1 = Node2; //node 1 vai receber o node2
		Node2 = Node2->esquerda; //e o node2 vai apontar para a esquerda
	}

	return Node1; //vai retornar o node1
}


int Arv ::bigger_alt(int alt_esquerda, int alt_direita) //maior altura
{
	if (alt_esquerda > alt_direita) //se a altura da esquerda for maior que a altura da direita
	{
		return alt_esquerda; //retorna a altura da esquerda
	}
	else
	{
		return alt_direita; //se n�o, retorna a altura da direita
	}
}

int Arv ::Altura(Node *aux) //altura
{

	if (aux == NULL) //se auxiliar for vazio
		return -1; //retorna -1
	else
	{
		return aux->altura; //se nao, retorna a altura
	}
}

//Fator de Balanceamento
int Arv ::fatorBalanceamento(Node *aux)
{
	if (aux == NULL) //se aux estiver vazio
		return 0; //retorna zero
	return (Altura(aux->esquerda) - Altura(aux->direita)); //faz o calculo da esquerda menos a direita
}


Node *Arv ::rotEE(Node *aux) //Rota��o Esquerda Esquerda
{
	Node *Node; //inicializa��o

	Node = aux->esquerda; // ponteiro node recebe o aux que aponta para esquerda
	aux->esquerda = Node->direita; //a esquerda do no aux aponta o no a direita do node
	Node->direita = aux; //a direita do node aponta para aux

	//Atualiza a altura dos n�s
	aux->altura = bigger_alt(Altura(aux->esquerda), Altura(aux->direita)) + 1;
	Node->altura = bigger_alt(Altura(Node->esquerda), aux->altura) + 1;

	//Se houve mudan�a do n� raiz
	if (aux == root)
	{
		root = Node;
	}

	//Se houve mudan�a apenas Nodes filhos
	aux = Node;

	return aux;
}

Node *Arv ::rotDD(Node *aux) //rota��o direita direita
{
	Node *Node; //inicializa��o

	Node = aux->direita; //ponteiro node recebe aux que aponta para a direita
	aux->direita = Node->esquerda; // direita do no aux aponta o no a esquerda do node
	Node->esquerda = aux; //a esquerda do node aponta para aux
	aux->altura = bigger_alt(Altura(aux->esquerda), Altura(aux->direita)) + 1;
	Node->altura = bigger_alt(aux->altura, Altura(Node->direita)) + 1;

	//Mesma coisa do de cima
	if (aux == root)
	{
		root = Node;
	}
	aux = Node;

	return aux;
}

Node *Arv ::RotacaoED(Node *aux) //rota��o esquerda direita
{
	aux->esquerda = rotDD(aux->esquerda); //rota��o dupla
	aux = rotEE(aux); //recebe o valor

	return aux;//retorna o valor da rota��o
}

Node *Arv ::RotacaoDE(Node *aux) //rota��o Direita Esquerda
{
	aux->direita = rotEE(aux->direita); //rota��o dupla
	aux = rotDD(aux);

	return aux;
}

void *Arv ::search(Node *aux, int valor) //pesquisar
{
	if (aux != NULL)  //se aux for direfente de null
	{
		if (valor < aux->informacao) //se o valor for menor que a informa�ao apontada por aux
		{
			return search(aux->esquerda, valor); //retorna a pesquisa a esquerda
		}
		else if (valor > aux->informacao) //se o valor for maior que a informa��o apontada por aux
		{
			return search(aux->direita, valor); //retorna a pesquisa a direita
		}
		else if (valor == aux->informacao) //se o valor for igual a informa��o apontada por aux
		{
			cout << "Valor encontrado" << endl;
		}
		return aux;
	}
	else if (root == NULL) //se o n� for igual a null
	{
		cout << "Lista Vazia" << endl;
	}

	cout << "Nao encontrado" << endl; //retorna a mensagem caso n�o encontre o n�
	return 0;
}

bool Arv::Pesquisar2(Node* aux, int valor)  //pesquisar 2
{

	if(aux == NULL) //se auxiliar for igual a null
	{

		return false; //retorna falso
	}

	else if(aux->informacao == valor) //se auxiliar apontando para a informa��o for igual ao valor
	{
		return true; //retorna verdadeiro
	}

	else
	{
		if(valor < aux->informacao) //se o valor for menor que a iforma��o apontada por aux
		{
			Pesquisar2(aux->esquerda, valor); //pesquisa a esquerda
		}
		else
		{
			Pesquisar2(aux->direita, valor); //se nao, pesquisa a direita
		}

		return 0;
	}
}



void Arv ::ImprimirPreOrdem(Node *aux) //imprimir os valores inciais na ordem que foram pegos do exemplo
{
	if (aux != NULL)
	{
		cout << "O elemento visitado foi: " << aux->informacao //conferir o elemento visitado
			 << " - Altura: " << aux->altura //retornar a altura
			 << " - Balanceamento: " << fatorBalanceamento(aux) << endl; //retornar o balanceamento
		ImprimirPreOrdem(aux->esquerda);
		ImprimirPreOrdem(aux->direita);
	}
}
//liberar
Node *Arv::libera(Node *root)
{
	if(root != NULL) //se o n� for diferente de null
	{
		//libera o n�
		libera(root->esquerda);
		libera(root->direita);
		delete root; //deleta o n�
	}
	return NULL;
}

int main()
{
	setlocale(LC_ALL, "Portuguese"); //para a leitura acentuada das palavras
	Arv avl; //variavel do tipo da struct

	int op, valor_inserir, valor_pesquisar, valor_excluir;

	int Nodes_iniciais[] = {30, 40, 24, 58, 48, 26, 11, 13, 14, 20}; //valores pegos do exemplo da avl de uma atv passada
	cout << "Valores iniciais da AVL:" << endl; //imprimir os valores do vetor s� pra facilitar o entendimento
	for(int i = 0; i < 10; i++) //percorrer todo o vetor
	{
		avl.root = //inserir os valores na arvore
			avl.Inserir(avl.root, Nodes_iniciais[i]);
		cout << Nodes_iniciais[i] << ",";
	}



	while (op != 5) //loop
	{
//menu
		cout << "\n\nSeja bem-vindo ao Menu �rvore AVL\nDigite a op��o desejada:" << endl;

		cout << "\n1 - Inserir valor na �rvore"
			 << "\n2 - Imprimir Pr�-Ordem"
			 << "\n3 - Remover n�"
			 << "\n4 - Pesquisar n�"
			 << "\n5 - Sair" << endl;

		cout << "Op��o: ";
		cin >> op;

		switch (op) //conferencia das op��es
		{
		case 1: //inserir
			cout << "\nDigite valor que deseja inserir na �rvore: ";
			cin >> valor_inserir;
			avl.root =
				avl.Inserir(avl.root, valor_inserir);
			cout << "Valor inserido" << endl;
			system("cls");
			break;
		case 2: //imprimir pr�-ordem
			avl.ImprimirPreOrdem(avl.root);
			system("pause");
			system("cls");
			break;
		case 3: // remover
			cout << "\nDigite valor que deseja remover: ";
			cin >> valor_excluir;
			if(avl.Pesquisar2(avl.root, valor_excluir) == true)
			{
				avl.root = avl.Remover(avl.root, valor_excluir);
				cout << "Elemento removido" << endl; //se o valor existir
			}
			else
			{
				cout << "Elemento n�o encontrado na �rvore" << endl; //se nao, o valor nao existe
			}
			system("pause");
			system("cls");
			break;
		case 4: //pesquisar
			cout << "\nDigite valor que deseja pesquisar �rvore: ";
			cin >> valor_pesquisar;
			if(avl.Pesquisar2(avl.root, valor_pesquisar) == true)
			{
				cout << "valor encontrado" << endl; //se existir
			}
			else
			{
				cout << "valor nao encontrado" << endl; //se nao existir
			}
			system("pause");
			system("cls");
			break;
		default:
			break;
		}
	}
	avl.root = avl.libera(avl.root); //libera��o

	return 0;
}
